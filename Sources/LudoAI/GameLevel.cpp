///////////////////////////////
// Filename: GameLevel.cpp
///////////////////////////////
#include "LudoCore/LudoGlobal.h"
#include "GameLevel.h"
#include "LudoCore/XMLDocument.h"
#include "LudoCore/XMLDataNode.h"
#include "LudoCore/LudoStringManager.h"
#include "LudoCore/ErrorLogger.h"
#include "LudoCore/LudoUtilities.h"
#include "LudoCore/LudoVector.h"
#include "LudoAI/GameObject.h"

#include "LudoAI/Rail.h"
#include "LudoAI/Ground.h"
#include "LudoAI/SkyDome.h"

#include "LudoRenderer/LudoCamera.h"

GameLevel::GameLevel()
{
    m_LevelObjects.clear();
}

GameLevel::~GameLevel()
{
    for (unsigned int i = 0; i < m_LevelObjects.size(); i++)
    {
        LUDO_SAFE_DELETE(m_LevelObjects[i]);
    }
    m_LevelObjects.clear();
}

bool GameLevel::Init(std::wstring levelFile)
{
    Rail *firstRail = NULL;
    Rail *prevRail = NULL;
    Rail *currentRail = NULL;
    XMLDocument doc(levelFile.c_str());

    if (!doc.IsValid())
    {
        return false;
    }

    // Read in the circuit
    LudoStringManager *sm = LudoStringManager::GetInstance();
    int numTrack = doc.GetNumDataNodes(sm->GetString(XML_TAG_PART).c_str());
    if (numTrack == 0)
    {
        ErrorLogger::GetInstance()->LogError(L"No track read in file", false);
        return false;
    }

    LudoVector *allTrackPos = LUDO_NEW LudoVector[numTrack];

    for (int i = 0; i < numTrack; i++)
    {
        const XMLDataNode *rootNode = doc.GetDataNode(sm->GetString(XML_TAG_PART).c_str(),i);
        float x = 0;
        float y = 0;
        float z = 0;

        for (unsigned int j = 0; j < rootNode->GetChildren().size(); j++)
        {
            const XMLDataNode *currNode = rootNode->GetChildren()[j];
            if (LudoUtilities::AreStringsEqual(currNode->GetName(),sm->GetString(XML_TAG_XPOS).c_str(),true))
            {
                x = (float)(LudoUtilities::StringToInt(currNode->GetInnerText()));
            }
            else if (LudoUtilities::AreStringsEqual(currNode->GetName(),sm->GetString(XML_TAG_YPOS).c_str(),true))
            {
                y = (float)(LudoUtilities::StringToInt(currNode->GetInnerText()));
            }
            else if (LudoUtilities::AreStringsEqual(currNode->GetName(),sm->GetString(XML_TAG_ZPOS).c_str(),true))
            {
                z = (float)(LudoUtilities::StringToInt(currNode->GetInnerText()));
            }
        }
        allTrackPos[i].Set(x,y,z);               
        currentRail = LUDO_NEW Rail(&allTrackPos[i],sm->GetString(RAIL_NAME));
        m_LevelObjects.push_back(currentRail);
        if (prevRail)
        {
            prevRail->SetNextRail(currentRail);
        }
        prevRail = currentRail;

        if (firstRail == NULL)
        {
            firstRail = currentRail;
        }
    }

    LUDO_SAFE_DELETE_ARRAY(allTrackPos);

    currentRail->SetNextRail(firstRail);

    // Create a ground object
    m_LevelObjects.push_back(LUDO_NEW Ground(sm->GetString(GROUND_NAME)));

    // Create the sky object
    m_LevelObjects.push_back(LUDO_NEW SkyDome(sm->GetString(SKY_NAME)));

    for (unsigned int i = 0; i < m_LevelObjects.size(); i++)
    {
        m_LevelObjects[i]->Init();
    }

    return true;
}

bool GameLevel::Update()
{   
    for (unsigned int i = 0; i < m_LevelObjects.size(); i++)
    {
        m_LevelObjects[i]->Update();
    }

    

    return true;
}

bool GameLevel::Render()
{
    for (unsigned int i = 0; i < m_LevelObjects.size(); )
    {
        if (m_LevelObjects[i]->ObjectReadyToRender())
        {
            m_LevelObjects[i]->Render();
            i++;
        }
    }

    return true;
}


