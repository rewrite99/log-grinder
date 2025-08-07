#pragma once

#include <chrono>
#include <cstdint>
#include <string>

using Clock = std::chrono::steady_clock;
using TimePoint = Clock::time_point;
using std::chrono::milliseconds;
using std::chrono::duration_cast;

class Timer{
public:
    enum class TimerMode{ Stopwatch, Countdown };
    
    static Timer& MainTimer();

    Timer(TimerMode tm, int64_t sec = 0);
    void startTimer();
    void stopTimer();
    void toggle();
    void resetTimer();
    void setTimer(int64_t ms);
    std::string timeFormat(int64_t ms) const;
    int64_t timeMs();
    bool refresh();
    bool isTimerRunning() const;

private:
    TimerMode mode {TimerMode::Stopwatch};
    TimePoint tp_start {};
    TimePoint tp_end {};
    int64_t remaining_ms {};
    bool is_running {false};

    static constexpr int64_t TIME_LIMIT {3'600'000'000};
};