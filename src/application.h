//
// Created by ia on 18.11.2024.
//

#ifndef CLOCK_APPLICATION_H
#define CLOCK_APPLICATION_H

#include "clock.h"
#include "config.h"

#include <string>

struct Application
{
public:
    // clang-format off
    int   screenWidth {1024};
    int   screenHeight{1024};
    float scale       {1.0f};
    // clang-format on

    explicit Application(const std::string& configFileName);

    void run();

    [[nodiscard]] int getScreenWidth() const;
    [[nodiscard]] int getScreenHeight() const;

private:
    // clang-format off
    config::Config m_config               ; // current configuration file
    float          m_tod                  ; // time of day (seconds since midnight)
    Clock::Ptr     m_clock                ; // current active clock
    int            m_clockIdx      {    0}; // active clock index in config
    Vector2        m_mousePosition {     }; // current mouse position
    Vector2        m_windowPosition{     }; // current window position
    Vector2        m_panOffset     {     }; // panning offset
    bool           m_dragWindow    {false}; // whether the window is dragged
    float          m_scrollSpeed   {0.01f}; // scroll speed for zooming
    // clang-format on

    void updateWindowSize() const;
    void drawClockFace(const Clock::Ptr& clock, float time) const;
    void drawClockLayer(const ClockLayer::Ptr& clockHand, float time) const;
    void saveCurrentState(const std::string& filename) const;
    void restoreState(const std::string& filename);
    Clock::Ptr initializeClock(const config::Config& config, int clockIdx);
};

#endif // CLOCK_APPLICATION_H
