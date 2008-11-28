///////////////////////////////
// Filename: GameObject.cpp
///////////////////////////////
#include "LudoCore/LudoGlobal.h"
#include "GameObject.h"

GameObject::GameObject(std::wstring baseName)
{
    m_ObjectUpdated = false;
    baseName;
}

GameObject::~GameObject()
{

}

// Virtual
void GameObject::Init()
{

}

// Virtual
void GameObject::Render()
{
    m_ObjectUpdated = false;
}

// Virtual
void GameObject::Update()
{
    m_ObjectUpdated = true;
}

bool GameObject::ObjectReadyToRender()
{
    return m_ObjectUpdated;
}
