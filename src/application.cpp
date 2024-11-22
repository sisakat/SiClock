#include "application.h"

#include <chrono>
#include <filesystem>

#include "functions.h"
#include "raylib.h"
#include "rlgl.h"
#include "state.h"

const std::string STATE_FILENAME = "state.json";

float secondsSinceMidnight()
{
    auto now = std::chrono::system_clock::now();
    auto today = std::chrono::floor<std::chrono::days>(now);
    auto tod = std::chrono::duration_cast<std::chrono::seconds>(now - today).count();
    return static_cast<float>(tod);
}

Application::Application(const std::string& configFileName) : m_tod{secondsSinceMidnight()}
{
    m_config = config::readConfig(configFileName);
    scale = m_config.scale;

    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    SetConfigFlags(FLAG_VSYNC_HINT);
    SetWindowState(FLAG_WINDOW_UNDECORATED);
    SetTargetFPS(m_config.targetFPS);
    InitWindow(getScreenWidth(), getScreenHeight(), "Clock");
    rlSetBlendFactorsSeparate(
        RL_SRC_ALPHA, RL_ONE_MINUS_SRC_ALPHA, RL_ONE, RL_ONE, RL_FUNC_ADD, RL_MAX);

    m_mousePosition = {0};
    m_windowPosition = GetWindowPosition();
    m_panOffset = m_mousePosition;
    m_clock = initializeClock(m_config, m_clockIdx);
    restoreState(STATE_FILENAME);
}

void Application::run()
{
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        m_mousePosition = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !m_dragWindow)
        {
            if (CheckCollisionPointRec(
                    m_mousePosition,
                    {0.0f,
                     0.0f,
                     static_cast<float>(screenWidth),
                     static_cast<float>(screenHeight)}))
            {
                m_dragWindow = true;
                m_panOffset = m_mousePosition;
            }
        }
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            m_clock = initializeClock(m_config, (++m_clockIdx) % m_config.clocks.size());
        }

        scale += GetMouseWheelMove() * m_scrollSpeed;
        updateWindowSize();

        if (m_dragWindow)
        {
            m_windowPosition.x += (m_mousePosition.x - m_panOffset.x);
            m_windowPosition.y += (m_mousePosition.y - m_panOffset.y);

            SetWindowPosition((int)m_windowPosition.x, (int)m_windowPosition.y);

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                m_dragWindow = false;
            }
        }

        BeginDrawing();
        ClearBackground(BLANK);
        BeginBlendMode(RL_BLEND_CUSTOM_SEPARATE);
        float time = GetTime();
        for (const auto& hand : m_clock->layers)
        {
            drawClockLayer(hand, m_tod + time);
        }
        EndBlendMode();

        EndDrawing();
    }

    saveCurrentState(STATE_FILENAME);
    CloseWindow();
}

int Application::getScreenWidth() const
{
    return static_cast<int>(static_cast<float>(screenWidth) * scale);
}

int Application::getScreenHeight() const
{
    return static_cast<int>(static_cast<float>(screenHeight) * scale);
}

void Application::updateWindowSize() const
{
    SetWindowSize(getScreenWidth(), getScreenHeight());
}

void Application::drawClockLayer(const ClockLayer::Ptr& clockHand, float time) const
{
    auto texWidth = static_cast<float>(clockHand->texture.width);
    auto texHeight = static_cast<float>(clockHand->texture.height);

    Vector2 pos = Vector2Multiply(
        clockHand->pos,
        Vector2(static_cast<float>(screenWidth) * scale, static_cast<float>(screenHeight) * scale));
    float rot = 0.0f;
    if (clockHand->calcRotation)
    {
        rot = clockHand->calcRotation(time);
    }
    float width = texWidth * scale * clockHand->scale;
    float height = texHeight * scale * clockHand->scale;
    Vector2 texScale(width / texWidth, height / texHeight);
    Vector2 origin = Vector2Multiply(Vector2(clockHand->origin.x, clockHand->origin.y), texScale);
    DrawTexturePro(
        clockHand->texture,
        {0.0f, 0.0f, texWidth, texHeight},
        {pos.x, pos.y, texWidth * scale * clockHand->scale, texHeight * scale * clockHand->scale},
        origin,
        rot,
        WHITE);
}

void Application::saveCurrentState(const std::string& filename) const
{
    State state;
    state.clockIdx = m_clockIdx;
    state.windowPositionX = static_cast<int>(GetWindowPosition().x);
    state.windowPositionY = static_cast<int>(GetWindowPosition().y);
    state.scale = scale;
    writeState(state, filename);
}

void Application::restoreState(const std::string& filename)
{
    if (!std::filesystem::exists(filename))
    {
        return;
    }

    auto state = readState(filename);
    SetWindowPosition(state.windowPositionX, state.windowPositionY);
    scale = state.scale;

    if (state.clockIdx < m_config.clocks.size() && state.clockIdx >= 0)
    {
        m_clockIdx = state.clockIdx;
        m_clock = initializeClock(m_config, m_clockIdx);
    }
}

Clock::Ptr Application::initializeClock(const config::Config& config, int clockIdx)
{
    Clock::Ptr clock = std::make_shared<Clock>();

    for (const auto& part : config.clocks[clockIdx].layers)
    {
        auto clockHand = std::make_shared<ClockLayer>();
        auto image = LoadImage(part.image.c_str());
        clockHand->texture = LoadTextureFromImage(image);
        UnloadImage(image);
        clockHand->origin = part.origin;
        clockHand->pos = part.pos;
        clockHand->scale = part.scale;

        if (FunctionsMap.contains(part.function))
        {
            clockHand->calcRotation = FunctionsMap.at(part.function);
        }
        else
        {
            clockHand->calcRotation = FunctionsMap.at("second");
        }

        GenTextureMipmaps(&clockHand->texture);
        SetTextureFilter(clockHand->texture, TEXTURE_FILTER_TRILINEAR);

        clock->layers.push_back(clockHand);
    }

    screenWidth = clock->layers.front()->texture.width;
    screenHeight = clock->layers.front()->texture.height;
    updateWindowSize();

    return clock;
}
