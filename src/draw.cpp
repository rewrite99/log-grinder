#include "draw.hpp"
#include "input_manager.hpp"
#include "moneylog.hpp"
#include "timer.hpp"

#include <chrono>
#include <fmt/compile.h>
#include <fmt/core.h>
#include <thread>

void draw(){
    MoneyLog& mlog {MoneyLog::Get()};

    int counter {};
    constexpr auto TEMPLATE {FMT_COMPILE(
        "\033[?25l\033[H"
        "Time\t{:>15}\n"
        "Gained\t{:>15}\n"
        "Total\t{:>15}\n"
        "{:>23}/hr\n"
        "{:>23}/min\n"
        "Redraw count: {}"
        )
    };
    Timer::MainTimer().startTimer();
    while (true){
        mlog.updateLog();

        if (Timer::MainTimer().refresh() || mlog.refresh()){
            ++counter;
            fmt::print(TEMPLATE,
            Timer::MainTimer().timeFormat(Timer::MainTimer().timeMs()),
            mlog.addComma(mlog.gainedAmount()),
            mlog.addComma(mlog.totalAmount()),
            mlog.addComma(mlog.ratePerHr()),
            mlog.addComma(mlog.ratePerMin()),
            counter
            );
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}