#include "LudoCore/LudoGlobal.h"
#include "LudoCore/InputKeyboard.h"

using std::vector;

InputKeyboard::InputKeyboard()
{

}

InputKeyboard::~InputKeyboard()
{

}

void InputKeyboard::PostUpdate()
{
    m_CurrentKeysReleased.clear();
}

void InputKeyboard::SetKeyPressed(int key)
{
    for (vector<int>::iterator iter = m_CurrentKeys.begin(); iter < m_CurrentKeys.end(); iter++)
    {
        if ((*iter) == key)
        {     
            return;
        }
    }

    m_CurrentKeys.push_back(key);
}

void InputKeyboard::SetKeyUnpressed(int key)
{
    m_CurrentKeysReleased.push_back(key);

    for (vector<int>::iterator iter = m_CurrentKeys.begin(); iter < m_CurrentKeys.end(); iter++)
    {
        if ((*iter) == key)
        {
            m_CurrentKeys.erase(iter);
            return;
        }
    }
}

void InputKeyboard::AddInputEvent(int key, int eventNumber, bool onKeyPressed)
{
    if (onKeyPressed)
    {
        m_KeyboardPressedInputEvent[key] = eventNumber;
    }
    else
    {
        m_KeyboardReleasedInputEvent[key] = eventNumber;
    }
}

bool InputKeyboard::IsEventTriggered(int eventNumber)
{
    for (unsigned int i = 0; i < m_CurrentKeys.size(); i++)
    {
        if (m_KeyboardPressedInputEvent.size() > 0 && m_KeyboardPressedInputEvent[m_CurrentKeys[i]] == eventNumber)
        {
            return true;
        }
    }

    for (unsigned int i = 0; i < m_CurrentKeysReleased.size(); i++)
    {
        if (m_KeyboardReleasedInputEvent.size() > 0 && m_KeyboardReleasedInputEvent[m_CurrentKeysReleased[i]] == eventNumber)
        {
            return true;
        }
    }
    return false;
}