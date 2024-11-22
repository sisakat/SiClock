#ifndef CLOCK_FUNCTIONS_H
#define CLOCK_FUNCTIONS_H

#include <functional>
#include <string>
#include <unordered_map>

float easeInOutExpo(float x)
{
    if (x < 0.0f)
    {
        return 0;
    }
    else if (x > 1.0f)
    {
        return 1;
    }
    else
    {
        if (x < 0.5)
        {
            return std::pow(2.0f, 20.0f * x - 10.0f) / 2.0f;
        }
        else
        {
            return (2.0f - std::pow(2.0f, -20.0f * x + 10.0f)) / 2.0f;
        }
    }
}

float easeOutElastic(float x)
{
    const float c4 = (2 * PI) / 9.0f;

    if (x < 0.0f)
    {
        return 0;
    }
    else if (x > 1.0f)
    {
        return 1;
    }
    else
    {
        return std::pow(2.0f, -20.0f * x) * static_cast<float>(std::sin((x * 20.0f - 0.75) * c4)) +
               1.0f;
    }
}

float hourFunc(float time)
{
    return (time / 60.0f / 60.0f + 1.0f) * (360.0f / 12.0f);
}

float minuteDiscreteFunc(float time)
{
    return std::floor(time / 60.0f) * 60.0f * 360.0f / 60.0f / 60.0f;
}

float minuteFunc(float time)
{
    return time * 360.0f / 60.0f / 60.0f;
}

float secondDiscreteFunc(float time)
{
    return std::floor(time) * 360.0f / 60.0f;
}

float secondDiscreteSmoothFunc(float time)
{
    float fl = std::floor(time - .5);
    float d = time - .5 - fl;
    return (fl + easeOutElastic(d)) * 360.0f / 60.0f;
}

float secondFunc(float time)
{
    return time * 360.0f / 60.0f;
}

float millisecondFunc(float time)
{
    return time * 360.0f;
}

inline std::unordered_map<std::string, std::function<float(float)>> FunctionsMap{
    {"none", nullptr},
    {"hour", hourFunc},
    {"minute", minuteFunc},
    {"minute_discrete", minuteDiscreteFunc},
    {"second_discrete", secondDiscreteFunc},
    {"second_discrete_smooth", secondDiscreteSmoothFunc},
    {"second", secondFunc},
    {"millisecond", millisecondFunc}};

#endif // CLOCK_FUNCTIONS_H
