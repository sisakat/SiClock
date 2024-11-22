#include "config.h"

#include <fstream>
#include <nlohmann/json.hpp>

namespace config
{

void from_json(const nlohmann::json& j, ClockLayer& o)
{
    o.image = j.value<std::string>("image", "");
    o.function = j.value<std::string>("function", "none");
    o.scale = j.value<float>("scale", 1.0f);

    if (j.contains("pos"))
    {
        o.pos.x = j["pos"][0].get<float>();
        o.pos.y = j["pos"][1].get<float>();
    }
    if (j.contains("origin"))
    {
        o.origin.x = j["origin"][0].get<float>();
        o.origin.y = j["origin"][1].get<float>();
    }
}

void from_json(const nlohmann::json& j, Clock& o)
{
    o.name = j.value<std::string>("name", "Generic Clock");
    o.layers = j.value<std::vector<ClockLayer>>("layers", {});
    o.scale = j.value<float>("scale", 1.0f);
}

void from_json(const nlohmann::json& j, Config& o)
{
    o.clocks = j.value<std::vector<Clock>>("clocks", {});
    o.targetFPS = j.value<int>("target_fps", 30);
    o.scale = j.value<float>("scale", 1.0f);
}

Config readConfig(const std::string& filename)
{
    std::ifstream file(filename);
    return nlohmann::json::parse(file);
}

} // namespace config
