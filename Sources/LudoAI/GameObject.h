#pragma once

class GameObject
{
public:
    GameObject(std::wstring baseName);
    virtual ~GameObject();

    // Virtual
    virtual void Init();
    // Virtual
    virtual void Render();
    // Virtual
    virtual void Update();

    bool ObjectReadyToRender();

private:
    bool m_ObjectUpdated;
};
