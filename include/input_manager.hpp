#pragma once

#include <array>
#include <unordered_map>
#include <windows.h>

class InputManager{
public:
    enum class Action {Toggle, Reset, Exit};

    static InputManager& Get();

    void update();   
    bool isPressed(Action a);
    void handleInput();

private:
    InputManager();

    std::unordered_map<Action, std::array<int, 2>> bindings{
        {Action::Toggle, {'S', 0}},
        {Action::Reset, {'R', 0}},
        {Action::Exit, {VK_CONTROL, 'Q'}}
    };
    std::unordered_map<Action, bool> prev {};
    std::unordered_map<Action, bool> cur {};
};