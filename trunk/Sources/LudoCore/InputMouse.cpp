#include "LudoCore/LudoGlobal.h"
#include "LudoCore/InputMouse.h"

InputMouse::InputMouse() :
    m_LastX(-1),
    m_LastY(-1)
{
    m_MouseActionEvent.clear();
}

InputMouse::~InputMouse()
{

}

void InputMouse::PostUpdate()
{
    m_CurrentAction.clear();
}

bool InputMouse::IsEventTriggered(int eventNumber)
{
    for (unsigned int i = 0; i < m_CurrentAction.size(); i++)
    {
        if (m_MouseActionEvent.size() > 0 && m_MouseActionEvent[m_CurrentAction[i]] == eventNumber)
        {
            return true;
        }
    }
    return false;
}

void InputMouse::AddInputEvent(int action, int eventNumber)
{
    m_MouseActionEvent[action] = eventNumber;
}

void InputMouse::SetMouseMouse(int x, int y)
{
    if (m_LastX != -1)
    {
        if (x > m_LastX)
        {
            m_CurrentAction.push_back(MOUSE_RIGHT);
        }
        else if (x < m_LastX)
        {
            m_CurrentAction.push_back(MOUSE_LEFT);
        }

        if (y > m_LastY)
        {
            m_CurrentAction.push_back(MOUSE_UP);
        }
        else if (y < m_LastY)
        {
            m_CurrentAction.push_back(MOUSE_DOWN);
        }
    }

    m_LastX = x; 
    m_LastY = y;
}