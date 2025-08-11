#include "input_manager.hpp"
#include "moneylog.hpp"
#include "timer.hpp"

#include <cstdlib>
#include <unordered_map>
#include <windows.h>

InputManager::InputManager(){
    for (const auto& [_, key] : key_binds){
        p_keystate[key[FIRST]] = c_keystate[key[FIRST]] = false;
        if (key[SECOND] != 0) p_keystate[key[SECOND]] = c_keystate[key[SECOND]] = false;
    }
}

InputManager& InputManager::Get(){
    static InputManager i_m {};
    return i_m;
}

void InputManager::update(){
    p_keystate = c_keystate;
    for (const auto& [_, key] : key_binds){
        c_keystate[key[FIRST]] = GetAsyncKeyState(key[FIRST]) & 0x8000;
        if (key[SECOND] != 0) c_keystate[key[SECOND]] = GetAsyncKeyState(key[SECOND]) & 0x8000;
    }
}

bool InputManager::isPressed(Action a) {
    const auto& key = key_binds[a];

    if (key[SECOND] == 0) return !p_keystate[key[FIRST]] && c_keystate[key[FIRST]];
    return (c_keystate[key[FIRST]]) && (!p_keystate[key[SECOND]] && c_keystate[key[SECOND]]);
}

void InputManager::handleInput(){
    update();
    if (isPressed(Action::Toggle)) Timer::MainTimer().toggle();
    if (isPressed(Action::Reset)){ 
        MoneyLog::Get().resetLog();
        Timer::MainTimer().resetTimer();
    }
    if (isPressed(Action::ResetGorb)) Timer::GorbTimer().restartTimer();
    if (isPressed(Action::Exit)) std::exit(EXIT_SUCCESS);
}