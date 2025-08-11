#include "timer.hpp"

#include <chrono>
#include <cstdint>
#include <fmt/compile.h>
#include <fmt/core.h>
#include <string>

Timer& Timer::MainTimer(){
    static Timer t {TimerMode::Stopwatch};
    return t;
}

Timer& Timer::GorbTimer(){
    static Timer gorb {TimerMode::Countdown, 240};
    return gorb;
}

Timer::Timer(TimerMode tm, int64_t sec) : mode{tm}{
    int64_t ms {sec * 1000};
    setTimer(ms);
    if (tm == TimerMode::Countdown) startTimer();
}

void Timer::startTimer(){
    is_running = true;
    tp_start = Clock::now() - (tp_end - tp_start);
    update = true;
}

void Timer::stopTimer(){
    is_running = false;
    tp_end = Clock::now();
    update = true;
}

void Timer::toggle(){
    if (is_running) stopTimer();
    else startTimer();
}

void Timer::resetTimer(){
    is_running = false;
    tp_start = tp_end = {};
    update = true;
}

void Timer::restartTimer(){
    tp_start = tp_end = Clock::now();
    update = true;
}

void Timer::setTimer(int64_t ms){
    stopTimer();

    switch (mode){
        case TimerMode::Stopwatch:
            tp_end = tp_start + milliseconds(ms);
            break;
        case TimerMode::Countdown:
            tp_start = tp_end = Clock::now();
            remaining_ms = ms;
            break;
        default: break;
    }
}

std::string Timer::cdSeconds(int64_t ms) const{
    int64_t sec {ms / 1000};
    return fmt::format(FMT_COMPILE("{}s"), sec);
}

std::string Timer::timeFormat(int64_t ms) const{
    int64_t sec = ms / 1000;
    int64_t hr  = sec / 3600;
    int64_t min = (sec / 60) % 60;
    sec %= 60;

    bool blink {!is_running || (ms % 1000 < 500)};
    char sep {blink ? ':' : ' '};

    return fmt::format(FMT_COMPILE("{:3}{}{:02}{}{:02}"), hr, sep, min, sep, sec);
}

int64_t Timer::timeMs(){
    auto now {is_running ? Clock::now() : tp_end};
    int64_t duration {duration_cast<milliseconds>(now - tp_start).count()};
    
    switch (mode){
        case TimerMode::Stopwatch:
            if (duration > TIME_LIMIT){
                is_running = false;
                tp_end = tp_start + milliseconds(TIME_LIMIT);
                return TIME_LIMIT;
            }
            return duration;
        
        case TimerMode::Countdown:{         
            int64_t remaining {remaining_ms - duration};
            
            if (remaining <= 0){
                is_running = false;
                tp_end = now;
                return 0;
            }
            return remaining;
        }
        default: return 0;
    }
}

bool Timer::refresh(){
    int64_t now {(timeMs() / 500) * 500};
    bool should {mode == TimerMode::Stopwatch ? (is_running && now - p_ms >= 500) : (is_running && now - p_ms <= -500)};
    if (update || should){
        p_ms = now;
        update = false;
        return true;
    }
    return false;
}

bool Timer::isTimerRunning() const{ return is_running; }