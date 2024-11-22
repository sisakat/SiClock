#include "state.h"

#include <fstream>
#include <nlohmann/json.hpp>

void from_json(const nlohmann::json& j, State& o)
{
    o.clockIdx = j.value<int>("clock_idx", 0);
    o.windowPositionX = j.value<int>("window_position_x", 0);
    o.windowPositionY = j.value<int>("window_position_y", 0);
    o.scale = j.value<float>("scale", 1.0f);
}

void to_json(nlohmann::json& j, const State& o)
{
    j["clock_idx"] = o.clockIdx;
    j["window_position_x"] = o.windowPositionX;
    j["window_position_y"] = o.windowPositionY;
    j["scale"] = o.scale;
}

State readState(const std::string& filename)
{
    std::ifstream file(filename);
    return nlohmann::json::parse(file);
}

void writeState(const State& state, const std::string& filename)
{
    std::ofstream file(filename);
    file << std::setw(4) << nlohmann::json(state);
}
