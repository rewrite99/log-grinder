#include "input_manager.hpp"
#include "timer.hpp"

#include <cstdlib>
#include <unordered_map>
#include <windows.h>

InputManager::InputManager(){
    for (const auto& [act, k] : bindings)
        prev[act] = cur[act] = false;
}

InputManager& InputManager::Get(){
    static InputManager i_m {};
    return i_m;
}

void InputManager::update(){
    prev = cur;
    for (const auto& [act, k] : bindings){
        bool k1 {(GetAsyncKeyState(k[0]) & 0x8000) != 0};
        bool k2 {k[1] == 0 ? true : ((GetAsyncKeyState(k[1]) & 0x8000) != 0)};
        cur[act] = k1 && k2;
    }
}

bool InputManager::isPressed(Action a){
    return !prev.at(a) && cur.at(a);
}

void InputManager::handleInput(){
    if (isPressed(Action::Toggle)) Timer::MainTimer().toggle();
    if (isPressed(Action::Reset))  Timer::MainTimer().resetTimer();
    if (isPressed(Action::Exit))   std::exit(EXIT_SUCCESS);
}