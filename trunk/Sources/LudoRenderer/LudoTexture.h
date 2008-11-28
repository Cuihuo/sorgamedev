#pragma once
#include <string>
#include <d3d9.h>
#include "../External/DirectXSDK/Include/d3dx9.h"
#include "../LudoCore/LudoGlobal.h"

class LudoTexture
{
public:
    LudoTexture();
    LudoTexture(std::string filename);
    ~LudoTexture();

    void LoadTexture();
    void UnloadTexture();

    LPDIRECT3DTEXTURE9                  GetTexture();
    std::string                         GetTextureFile();
    bool                                GetTextureLoaded(){ return m_TextureLoaded; };
    int                                 GetWidth();
    int                                 GetHeight();
    void                                SetTextureFile(std::string filename);
    void                                SetSize(int height, int width);

private:
    LPDIRECT3DTEXTURE9 m_Texture;
    std::string m_Name;
    bool m_TextureLoaded;
    int m_Width;
    int m_Height;
};

