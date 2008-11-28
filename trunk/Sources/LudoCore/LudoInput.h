#pragma once

class InputMouse;
class InputKeyboard;

class LudoInput
{
public:
    LudoInput();
    ~LudoInput();

    bool Init();    
    bool Update();
    void PostUpdate();

    bool IsEventTriggered(int eventNumber);

    InputKeyboard* GetKeyboard();
    InputMouse* GetMouse();

private:
    InputMouse *m_Mouse;
    InputKeyboard *m_Keyboard;
};