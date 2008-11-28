#pragma once

class InputKeyboard
{
public:
    InputKeyboard();
    ~InputKeyboard();

    void AddInputEvent(int key, int eventNumber, bool onKeyPressed);
    void SetKeyPressed(int key);
    void SetKeyUnpressed(int key);
    bool IsEventTriggered(int eventNumber);
    void PostUpdate();

private:
    std::map<int,int> m_KeyboardPressedInputEvent;
    std::map<int,int> m_KeyboardReleasedInputEvent;
    std::vector<int> m_CurrentKeys;
    std::vector<int> m_CurrentKeysReleased;
};
