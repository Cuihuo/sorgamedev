#pragma once
#include "LudoCore/Singleton.h"

class GameLevel;
class LudoRenderer;
class LudoCamera;
class LudoInput;

class LudoEngine : public Singleton<LudoEngine>
{
    friend class Singleton<LudoEngine>;

public:
    bool UpdateGame();
    bool UpdateObjects();
    bool RenderObjects();

    bool LoadGame();
    LudoRenderer *GetRender(){ return m_Renderer; }
    LudoCamera *GetCamera(){ return m_Camera; }
    LudoInput *GetInput(){ return m_Input; }

private:
    LudoEngine();
    ~LudoEngine();

    enum Mode
    {
        LOAD_REQUESTED,
        LOADING,
        MENU,
        PLAYING,
    };

    Mode            m_CurrentMode;

    GameLevel       *m_CurrentLevel;
    bool            m_LevelLoaded;
    LudoRenderer    *m_Renderer;
    LudoCamera      *m_Camera;
    LudoInput       *m_Input;
};
