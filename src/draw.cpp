#include "draw.hpp"
#include "moneylog.hpp"
#include "timer.hpp"

#include <chrono>
#include <fmt/compile.h>
#include <fmt/core.h>
#include <thread>

void draw(){
    MoneyLog& mlog {MoneyLog::Get()};

    constexpr auto TEMPLATE {FMT_COMPILE(
        "\033[H"
        "Time\t{:>15}\n"
        "Gained\t{:>15}\n"
        "Total\t{:>15}\n"
        "{:>23}/hr\n"
        "{:>23}/min\n"
        )
    };

    Timer::MainTimer().startTimer();

    while (true){
        mlog.updateLog();
        fmt::print(TEMPLATE,
            Timer::MainTimer().timeFormat(Timer::MainTimer().timeMs()),
            mlog.addComma(mlog.gainedAmount()),
            mlog.addComma(mlog.totalAmount()),
            mlog.addComma(mlog.ratePerHr()),
            mlog.addComma(mlog.ratePerMin())
        );
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}