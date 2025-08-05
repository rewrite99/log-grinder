#include "draw.hpp"
#include "monitor_log.hpp"
#include "timer.hpp"

#include <chrono>
#include <fmt/compile.h>
#include <fmt/core.h>
#include <thread>

namespace {
    MonitorLog mLog {};
    Timer g_mainTimer {TimerMode::Stopwatch};
}

MonitorLog& mainLog(){ return mLog; }

Timer& mainTimer(){ return g_mainTimer; }

void draw(){
    constexpr auto TEMPLATE {FMT_COMPILE(
        "\033[H"
        "Time\t{:>15}\n"
        "Gained\t{:>15}\n"
        "Total\t{:>15}\n"
        "{:>23}/hr\n"
        "{:>23}/min\n"
        )
    };

    g_mainTimer.startTimer();

    while (true){
        mLog.updateLog();
        fmt::print(TEMPLATE,
            g_mainTimer.timeFormat(g_mainTimer.getTimeMs()),
            mLog.addComma(mLog.getGainedAmount()),
            mLog.addComma(mLog.getTotalAmount()),
            mLog.addComma(mLog.ratePerHr()),
            mLog.addComma(mLog.ratePerMin())
        );
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}