///////////////////////////////
// Filename: LudoTexture.cpp
// Description: wrapper for a texture
// Created on: 23/10/2007
///////////////////////////////
#include "LudoCore/LudoGlobal.h"
#include "LudoTexture.h"
#include "LudoRenderer.h"
#include "LudoEngine/LudoEngine.h"
#include "LudoCore/FileReader.h"
#include "LudoCore/ErrorLogger.h"
#include <Dxerr.h>

using std::string;

LudoTexture::LudoTexture()
{
    m_Texture = NULL;
    m_TextureLoaded = false;
    m_Name = "";
    m_Width = 0;
    m_Height = 0;
}

LudoTexture::LudoTexture(string filename)
{
    m_Name = filename;
    m_TextureLoaded = false;
    m_Texture = NULL;
    m_Width = 0;
    m_Height = 0;
    LoadTexture();
}

LudoTexture::~LudoTexture()
{
    UnloadTexture();
}

LPDIRECT3DTEXTURE9 LudoTexture::GetTexture()
{
    if (m_Texture == NULL)
    {
        return 0;
    }
    return m_Texture;
}

void LudoTexture::SetTextureFile(string filename)
{
    m_Name = filename;
    LoadTexture();
}

void LudoTexture::SetSize(int height, int width)
{
    m_Height = height;
    m_Width = width;
}

string LudoTexture::GetTextureFile()
{
    return m_Name;
}

void LudoTexture::LoadTexture()
{
    if (LudoEngine::GetInstance()->GetRender()->GetpDevice() != NULL)
    {
        UnloadTexture();

        FileReader fr(m_Name.c_str());
        int size = 0;
        char *memblock = (char *)fr.GetFileData(size);

        LPDIRECT3DDEVICE9 d3dDevice = LudoEngine::GetInstance()->GetRender()->GetpDevice();

        if ( memblock && d3dDevice )
        {
            if (m_Name.find(".png") != -1 || m_Name.find(".PNG") != -1)
            {
                m_Width = ((byte)memblock[16] << 24) + ((byte)memblock[17] << 16) + ((byte)memblock[18] << 8) + ((byte)memblock[19]);
                m_Height = ((byte)memblock[20] << 24) + ((byte)memblock[21] << 16) + ((byte)memblock[22] << 8) + ((byte)memblock[23]);
            }
            else if (m_Name.find(".jpg") != -1 || m_Name.find(".JPG") != -1)
            {
                // Check for valid JPEG header (null terminated JFIF)
                if(((byte)memblock[0]) == 0xFF && ((byte)memblock[1]) == 0xD8
                    && ((byte)memblock[2]) == 0xFF && ((byte)memblock[3]) == 0xE0
                    && memblock[6] == 'J' && memblock[7] == 'F' && memblock[8] == 'I'
                    && memblock[9] == 'F' && memblock[10] == 0x00)
                {
                    int i = 4;
                    unsigned short block_length = ((byte)memblock[i]) * 256 + ((byte)memblock[i+1]);
                    while(i < size)
                    {
                        i += block_length;
                        if(i < size && ((byte)memblock[i]) == 0xFF)
                        {
                            if (((byte)memblock[i+1]) == 0xC0)
                            {
                                m_Height = ((byte)memblock[i+5]*256) + ((byte)memblock[i+6]);
                                m_Width = ((byte)memblock[i+7]*256) + ((byte)memblock[i+8]);
                            }
                            else
                            {
                                i += 2;                                     //Skip the block marker
                                block_length = ((byte)memblock[i]) * 256 + ((byte)memblock[i+1]);   //Go to the next block
                            }
                        }
                    }
                }

                if (m_Width == 0 && m_Height == 0)
                {
                    ErrorLogger::GetInstance()->LogError("Invalid JPEG!",false);
                    LUDO_DELETE[] memblock;
                    return;
                }
            }
            else
            {
                ErrorLogger::GetInstance()->LogError("Unsupported texture!",false);
                LUDO_DELETE[] memblock;
                return;
            }

            HRESULT result = D3DXCreateTextureFromFileInMemoryEx(d3dDevice, memblock, size,
                m_Width,                     //width
                m_Height,                    //height
                1,                           //mip levels
                NULL,                        //usage
                D3DFMT_UNKNOWN,              //texture color format
                D3DPOOL_MANAGED,             //memory class
                D3DX_FILTER_TRIANGLE | D3DX_FILTER_DITHER | D3DX_FILTER_MIRROR,                //filter
                D3DX_DEFAULT,                //mip filter
                0,                           //deactivate color key ( NEW )
                NULL,                        //source info
                NULL,                        //pallette
                &m_Texture);                  //texture object

            if (result != S_OK)
            {
                const char *c = DXGetErrorDescription(result);
                ErrorLogger::GetInstance()->LogError(c,false);
                LUDO_DELETE[] memblock;
                return;
            }

            m_TextureLoaded = true;
            LUDO_DELETE[] memblock;
        }
    }
}

void LudoTexture::UnloadTexture()
{
    if(m_Texture)
    {
        m_Texture->Release();
        m_Texture = NULL;
        m_TextureLoaded = false;
        m_Width = 0;
        m_Height = 0;
    }
}

int LudoTexture::GetWidth()
{
    return m_Width;
}

int LudoTexture::GetHeight()
{
    return m_Height;
}
