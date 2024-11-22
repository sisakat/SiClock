#ifndef CLOCK_STATE_H
#define CLOCK_STATE_H

#include <string>

struct State
{
    int clockIdx;
    int windowPositionX;
    int windowPositionY;
    float scale;
};

State readState(const std::string& filename);
void writeState(const State& state, const std::string& filename);

#endif // CLOCK_STATE_H
