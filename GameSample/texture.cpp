/*==============================================================================

   //Direct3Dの初期化関連 [direct3d.cpp]
														 //Author : Satou Youhei
														 //Date   : 2025/06/13
//--------------------------------------------------------------------------------

//==============================================================================*/

#include "texture.h"
#include "direct3d.h"
#include <string>
#include "DirectXTex.h"
using namespace DirectX;

static constexpr int TEXTURE_MAX = 256;//texture generator

struct Texture
{
	std::wstring filename;
	ID3D11ShaderResourceView* pTexture;
	unsigned int width;
	unsigned int height;
};

static Texture g_Textures[TEXTURE_MAX]{};
static unsigned int g_SetTextureIndex = -1;
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;

void Texture_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	for (Texture& t : g_Textures) {
		t.pTexture = nullptr;
	}
	g_SetTextureIndex = -1;

	g_pDevice = pDevice;
	g_pContext = pContext;
}

void Texture_Finalize(void)
{
	Texture_AllRelease();
}

int Texture_Load(const wchar_t* pFilename)
{
	//すでに読み込んだファイルは読み込んまない
	for (int i = 0; i < TEXTURE_MAX; i++) {
		if (g_Textures[i].filename == pFilename) {
			return i;
		}
	}

	//空いてる管理料を探す
	for (int i = 0; i < TEXTURE_MAX; i++) {

		if (g_Textures[i].pTexture)continue;//使用中

		
		TexMetadata metadata;
		ScratchImage image;

	HRESULT hr = LoadFromWICFile(pFilename, WIC_FLAGS_NONE, &metadata, image);

	if (FAILED(hr)) {
		MessageBoxW(nullptr, L"テクスチャの読み込みに失敗しました", pFilename, MB_OK | MB_ICONERROR);
		return -1;
	}

	g_Textures[i].filename = pFilename;
	g_Textures[i].width = (unsigned int)metadata.width;
	g_Textures[i].height =(unsigned int) metadata.height;

	hr = CreateShaderResourceView(g_pDevice, 
		image.GetImages(),image.GetImageCount(),metadata, &g_Textures[i].pTexture);
	
	return i;
}
	return -1;
}

void Texture_AllRelease()
{
	for (Texture& t : g_Textures) {
		t.filename.clear();
		SAFE_RELEASE(t.pTexture);
	}

}

void Texture_SetTexture(int texid)
{
	if (texid < 0) return;
	
	//if (g_SetTextureIndex == texid) return;

	g_SetTextureIndex = texid;

	// テクスチャ設定
	g_pContext->PSSetShaderResources(0, 1, &g_Textures[texid].pTexture);
}

unsigned int Texture_Width(int texid)
{
	if (texid < 0) return 0;

	return g_Textures[texid].width;	
}

unsigned int Texture_Height(int texid)
{
	if (texid < 0) return 0;

	return g_Textures[texid].height;
}
