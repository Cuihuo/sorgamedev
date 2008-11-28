#pragma once

class InputMouse
{
public:
    enum MouseAction
    {
        MOUSE_LEFT,
        MOUSE_UP,
        MOUSE_RIGHT,
        MOUSE_DOWN
    };

    InputMouse();
    ~InputMouse();

    void AddInputEvent(int action, int eventNumber);
    void SetMouseMouse(int x, int y);

    void PostUpdate();
    bool IsEventTriggered(int eventNumber);

private:
    std::map<int,int> m_MouseActionEvent;
    std::vector<int> m_CurrentAction;

    int m_LastX;
    int m_LastY;
};