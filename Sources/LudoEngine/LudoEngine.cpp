///////////////////////////////
// File : Ludo Engine
// Description : This class is the main Engine. 
// Author : Jean-Sylvain Sormany
///////////////////////////////

#include "LudoCore/LudoGlobal.h"
#include "LudoEngine.h"
#include "LudoCore/ErrorLogger.h"
#include "LudoCore/LudoTimer.h"
#include "LudoCore/LudoStringManager.h"
#include "LudoCore/LudoInput.h"
#include "LudoAI/GameLevel.h"
#include "LudoRenderer/LudoRenderer.h"
#include "LudoRenderer/LudoCamera.h"
#include "LudoCore/LudoInputEvent.h"
#include "LudoCore/InputKeyboard.h"
#include "LudoCore/InputMouse.h"

static const float CAMERA_STEP = 10.0f;
static const float FULL_CIRCLE_DEG = 360.0f;
LudoEngine::LudoEngine() :
    m_CurrentMode(LOAD_REQUESTED),
    m_CurrentLevel(NULL),
    m_LevelLoaded(false),
    m_Renderer(NULL),
    m_Camera(NULL),
    m_Input(NULL)
{
    m_Renderer = LudoRenderer::GetInstance();
    m_Camera = LUDO_NEW LudoCamera();
    m_Renderer->SetCamera(m_Camera);
    m_Input = LUDO_NEW LudoInput();

    m_Input->Init();

    m_Input->GetKeyboard()->AddInputEvent(VK_PRIOR,CAMERA_TURN_UP,true);
    m_Input->GetKeyboard()->AddInputEvent(VK_NEXT,CAMERA_TURN_DOWN,true);
    m_Input->GetKeyboard()->AddInputEvent(VK_HOME,CAMERA_TURN_RIGHT,true);
    m_Input->GetKeyboard()->AddInputEvent(VK_END,CAMERA_TURN_LEFT,true);

    m_Input->GetKeyboard()->AddInputEvent(VK_UP,CAMERA_MOVE_UP,true);
    m_Input->GetKeyboard()->AddInputEvent(VK_DOWN,CAMERA_MOVE_DOWN,true);
    m_Input->GetKeyboard()->AddInputEvent(VK_RIGHT,CAMERA_MOVE_RIGHT,true);
    m_Input->GetKeyboard()->AddInputEvent(VK_LEFT,CAMERA_MOVE_LEFT,true);
    
    m_Input->GetKeyboard()->AddInputEvent(VK_SHIFT,CAMERA_FORWARD_BACKWARD,true);

    m_Input->GetKeyboard()->AddInputEvent(VK_SPACE,CAMERA_RESET,false);
    m_Input->GetKeyboard()->AddInputEvent(VK_ESCAPE,APPLICATION_EXIT,false);
    m_Input->GetKeyboard()->AddInputEvent(VK_F1,WIREFRAME_MODE,false);

    m_Input->GetMouse()->AddInputEvent(InputMouse::MOUSE_LEFT,CAMERA_TURN_RIGHT);
    m_Input->GetMouse()->AddInputEvent(InputMouse::MOUSE_RIGHT,CAMERA_TURN_LEFT);
}

LudoEngine::~LudoEngine()
{
    LUDO_SAFE_DELETE(m_Camera);
    LUDO_SAFE_DELETE(m_CurrentLevel);
    LUDO_SAFE_DELETE(m_Input);
    m_Renderer->Destroy();
    m_LevelLoaded = false;
}

bool LudoEngine::UpdateGame()
{
    if (m_CurrentMode == LOAD_REQUESTED)
    {
        LudoEngine::GetInstance()->LoadGame();
        m_CurrentMode = PLAYING;
    }
    else if (m_LevelLoaded && m_CurrentMode == PLAYING)
    {
        m_Input->Update();

        if (m_Input->IsEventTriggered(CAMERA_TURN_RIGHT))
        {
            m_Camera->RotateY(LUDO_2_PI / FULL_CIRCLE_DEG);
        }
        if (m_Input->IsEventTriggered(CAMERA_TURN_LEFT))
        {
            m_Camera->RotateY(-LUDO_2_PI / FULL_CIRCLE_DEG);
        }   
        if (m_Input->IsEventTriggered(CAMERA_FORWARD_BACKWARD))
        {
            if (m_Input->IsEventTriggered(CAMERA_MOVE_UP))
            {
                m_Camera->Translate(0,-CAMERA_STEP,0);
            }
            if (m_Input->IsEventTriggered(CAMERA_MOVE_DOWN))
            {
                m_Camera->Translate(0,CAMERA_STEP,0);
            }            
        }
        else
        {
            if (m_Input->IsEventTriggered(CAMERA_MOVE_UP))
            {
                m_Camera->Translate(0,0.0f,CAMERA_STEP);
            }
            if (m_Input->IsEventTriggered(CAMERA_MOVE_DOWN))
            {
                m_Camera->Translate(0,0.0f,-CAMERA_STEP);
            }
        }
        
        if (m_Input->IsEventTriggered(CAMERA_MOVE_RIGHT))
        {
            m_Camera->Translate(-CAMERA_STEP,0.0f,0);
        }
        if (m_Input->IsEventTriggered(CAMERA_MOVE_LEFT))
        {
            m_Camera->Translate(CAMERA_STEP,0.0f,0);
        }
        if (m_Input->IsEventTriggered(CAMERA_RESET))
        {
            m_Camera->Reset();
        }
        if (m_Input->IsEventTriggered(WIREFRAME_MODE))
        {
            m_Renderer->SwitchWireframeDisplayMode();
        }
        if (m_Input->IsEventTriggered(APPLICATION_EXIT))
        {
            return false;
        }

        LudoTimer::GetInstance()->Update();
        LudoEngine::GetInstance()->UpdateObjects();
        LudoEngine::GetInstance()->RenderObjects();

        m_Input->PostUpdate();
        return true;
    }

    return true;
}

bool LudoEngine::UpdateObjects()
{
    if (m_CurrentLevel)
    {
        m_CurrentLevel->Update();
    }

    return true;
}

bool LudoEngine::RenderObjects()
{
    m_Renderer->BeginScene();

    if (m_CurrentLevel)
    {
        m_CurrentLevel->Render();
    }

    m_Renderer->EndScene();


    return true;
}

bool LudoEngine::LoadGame()
{
    m_CurrentMode = LOADING;
    m_CurrentLevel = LUDO_NEW GameLevel();
    m_LevelLoaded = m_CurrentLevel->Init(LudoStringManager::GetInstance()->GetString(MAIN_LEVEL_FILENAME));
    return m_LevelLoaded;
}
