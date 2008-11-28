#include "LudoCore/LudoGlobal.h"
#include "LudoInput.h"
#include "InputKeyboard.h"
#include "InputMouse.h"

LudoInput::LudoInput()
{
    m_Mouse = LUDO_NEW InputMouse();
    m_Keyboard = LUDO_NEW InputKeyboard();
}

LudoInput::~LudoInput()
{
    LUDO_DELETE(m_Mouse);
    LUDO_DELETE(m_Keyboard);
}

bool LudoInput::Init()
{
    return true;
}

bool LudoInput::Update()
{
    return true;
}

void LudoInput::PostUpdate()
{
    m_Keyboard->PostUpdate();
    m_Mouse->PostUpdate();
}

bool LudoInput::IsEventTriggered(int eventNumber)
{
    if (m_Keyboard->IsEventTriggered(eventNumber))
    {
        return true;
    }
    else if (m_Mouse->IsEventTriggered(eventNumber))
    {
        return true;
    }

    return false;
}

InputKeyboard* LudoInput::GetKeyboard()
{
    return m_Keyboard;
}

InputMouse* LudoInput::GetMouse()
{
    return m_Mouse;
}