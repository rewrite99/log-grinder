#include "console_setup.hpp"
#include "draw.hpp"
#include "moneylog.hpp"

int main(){
    ConsoleSetup cs {};

    MoneyLog::Get().setFilePath("D:\\MultiMC\\instances\\1.21.1\\.minecraft\\logs\\latest.log");

    draw();

    return 0;
}