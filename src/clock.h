#ifndef CLOCK_CLOCK_H
#define CLOCK_CLOCK_H

#include "raylib.h"
#include "raymath.h"

#include <functional>
#include <memory>
#include <vector>

struct ClockLayer
{
    using Ptr = std::shared_ptr<ClockLayer>;

    ~ClockLayer();

    Texture2D texture;
    Vector2 origin{0.0f, 0.0f};
    Vector2 pos{0.0f, 0.0f};
    float scale{1.0f};
    std::function<float(float)> calcRotation;
};

struct Clock
{
    using Ptr = std::shared_ptr<Clock>;

    ~Clock();

    std::vector<ClockLayer::Ptr> layers;
    float scale{1.0f};
};

#endif // CLOCK_CLOCK_H
