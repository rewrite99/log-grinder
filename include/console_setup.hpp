#pragma once

#include <fmt/core.h>
#include <windows.h>

struct ConsoleSetup{
    HANDLE hOut = nullptr, hIn = nullptr;
    DWORD oldOut = 0, oldIn = 0;

    ConsoleSetup(){
        hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        hIn = GetStdHandle(STD_INPUT_HANDLE);

        if (GetConsoleMode(hOut, &oldOut)){
            DWORD outMode = oldOut | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, outMode);
        }

        if (GetConsoleMode(hIn, &oldIn)){
            DWORD mask = static_cast<DWORD>(ENABLE_MOUSE_INPUT | ENABLE_QUICK_EDIT_MODE);
            DWORD inMode = oldIn & ~mask;
            SetConsoleMode(hIn, inMode);
        }

        fmt::print("\033[H\033[0J");
    }

    ~ConsoleSetup(){
        SetConsoleMode(hOut, oldOut);
        SetConsoleMode(hIn, oldIn);
    }

    ConsoleSetup(const ConsoleSetup&) = delete;
    ConsoleSetup& operator=(const ConsoleSetup&) = delete;
    ConsoleSetup(ConsoleSetup&&) = delete;
    ConsoleSetup& operator=(ConsoleSetup&&) = delete;
};