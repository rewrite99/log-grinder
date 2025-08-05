#include "console_setup.hpp"
#include "draw.hpp"
#include "timer.hpp"

int main(){
    ConsoleSetup cs {};

    mainLog().setFilePath("D:\\MultiMC\\instances\\1.21.1\\.minecraft\\logs\\latest.log");

    draw();

    return 0;
}