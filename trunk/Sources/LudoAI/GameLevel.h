#pragma once
#include "LudoCore/LudoGlobal.h"

class GameObject;
class Rail;
class LudoCamera;

class GameLevel
{
public:
    GameLevel();
    ~GameLevel();

    bool Init(std::wstring levelFile);
    bool Update();
    bool Render();

private:
    std::vector<GameObject *> m_LevelObjects;
   
};
