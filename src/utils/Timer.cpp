#include "utils/Timer.h"

#include <raylib.h>
Timer::Timer() : m_startTime(0.0) {}

Timer::~Timer() {}

void Timer::reset() { m_startTime = GetTime(); }

double Timer::getSeconds() { return GetTime() - m_startTime; }