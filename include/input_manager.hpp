#pragma once

#include <array>
#include <unordered_map>
#include <windows.h>

class InputManager{
public:
    enum class Action {Toggle, Reset, Exit};
    enum class KeyIndex {First, Second};

    static InputManager& Get();

    void update();
    bool isPressed(Action a);
    void handleInput();

private:
    InputManager();

    static constexpr size_t FIRST  = static_cast<size_t>(KeyIndex::First);
    static constexpr size_t SECOND = static_cast<size_t>(KeyIndex::Second);

    std::unordered_map<Action, std::array<int, 2>> key_binds{
        {Action::Toggle, {'Q', 'S'}},
        {Action::Reset, {'Q', 'R'}},
        {Action::Exit, {'Q', VK_ESCAPE}}
    };
    std::unordered_map<int, bool> p_keystate {};
    std::unordered_map<int, bool> c_keystate {};
};