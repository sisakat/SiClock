#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include <raymath.h>
#include <string>
#include <vector>

namespace config
{

struct ClockLayer
{
    std::string image;
    std::string function;
    Vector2 pos;
    Vector2 origin;
    float scale;
};

struct Clock
{
    std::string name;
    std::vector<ClockLayer> layers;
    float scale;
};

struct Config
{
    std::vector<Clock> clocks;
    int targetFPS{60};
    float scale{1.0f};
};

Config readConfig(const std::string& filename);

} // namespace config

#endif // CLOCK_CONFIG_H
