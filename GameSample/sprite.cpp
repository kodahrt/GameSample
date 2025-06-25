/*==============================================================================

   ƒXƒvƒ‰ƒCƒg•`‰æ [sprite.cpp]
														 Author : LCH
														 Date   : 2025/06/13
--------------------------------------------------------------------------------

==============================================================================*/
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"
#include "shader.h"
#include "debug_ostream.h"
#include "Sprite.h"
#include "texture.h"
#pragma comment(lib, "d3d11.lib")

static constexpr int NUM_VERTEX = 4;  // ’¸“_”


static ID3D11Buffer* g_pVertexBuffer = nullptr;  // ’¸“_ƒoƒbƒtƒ@
static ID3D11ShaderResourceView* g_pTexture = nullptr;//ƒeƒNƒXƒ`ƒƒ

// ’ˆÓI‰Šú‰»‚ÅŠO•”‚©‚çİ’è‚³‚ê‚é‚à‚ÌBRelease•s—vB
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;

// ’¸“_\‘¢‘Ì
struct Vertex
{
	XMFLOAT3 position; // ’¸“_À•W
	XMFLOAT4 color;      // F
	XMFLOAT2 uv;       // uv (2D)
};


void Sprite_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	// ƒfƒoƒCƒX‚ÆƒfƒoƒCƒXƒRƒ“ƒeƒLƒXƒg‚Ìƒ`ƒFƒbƒN
	if (!pDevice || !pContext) {
		hal::dout << "Sprite_Initialize() : ÓE¨¤é¤E¿¥Ç¥Ğ¥¤¥¹¤«¥³¥ó¥Æ¥­¥¹¥È¤¬²»Õı¤Ç¤¹" << std::endl;
		return;
	}


	// ƒfƒoƒCƒX‚ÆƒfƒoƒCƒXƒRƒ“ƒeƒLƒXƒg‚Ì•Û‘¶
	g_pDevice = pDevice;
	g_pContext = pContext;

	
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	g_pDevice->CreateBuffer(&bd, NULL, &g_pVertexBuffer);

	
}

void Sprite_Finalize(void)
{
	SAFE_RELEASE(g_pTexture);
	SAFE_RELEASE(g_pVertexBuffer);
}
void Sprite_Begin() {
    // ’¸“_ƒVƒF[ƒ_[‚É•ÏŠ·s—ñ‚ğİ’è
    const float SCREEN_WIDTH = (float)Direct3D_GetBackBufferWidth();
    const float SCREEN_HEIGHT = (float)Direct3D_GetBackBufferHeight();
    Shader_SetProjectionMatrix(XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));
}

void Sprite_Draw(int texid, float dx, float dy, const XMFLOAT4& color) {
    Shader_Begin();

    // ’¸“_ƒoƒbƒtƒ@‚ğƒƒbƒN‚·‚é
    D3D11_MAPPED_SUBRESOURCE msr;
    g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
    Vertex* v = (Vertex*)msr.pData;

    // ’¸“_î•ñ‚ğ‘‚«‚İ
    unsigned int dw = Texture_Width(texid);
    unsigned int dh = Texture_Height(texid);

    v[0].position = { dx,      dy,      0.0f };
    v[1].position = { dx + dw, dy,      0.0f };
    v[2].position = { dx,      dy + dh, 0.0f };
    v[3].position = { dx + dw, dy + dh, 0.0f };

    v[0].color = color;
    v[1].color = color;
    v[2].color = color;
    v[3].color = color;

    v[0].uv = { 0.0f, 0.0f };
    v[1].uv = { 1.0f, 0.0f };
    v[2].uv = { 0.0f, 1.0f };
    v[3].uv = { 1.0f, 1.0f };

    g_pContext->Unmap(g_pVertexBuffer, 0);

    // ‰ñ“]s—ñ‚ğƒVƒF[ƒ_[‚Éİ’è
    Shader_SetWorldMatrix(XMMatrixIdentity());

    // ’¸“_ƒoƒbƒtƒ@‚ğ•`‰æƒpƒCƒvƒ‰ƒCƒ“‚Éİ’è
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

    // ƒvƒŠƒ~ƒeƒBƒuƒgƒ|ƒƒWİ’è
    g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    // ƒeƒNƒXƒ`ƒƒİ’è
    Texture_SetTexture(texid);

    // ƒ|ƒŠƒSƒ“•`‰æ–½—ß”­s
    g_pContext->Draw(NUM_VERTEX, 0);
}

void Sprite_Draw(int texid, float dx, float dy, float dw, float dh, const XMFLOAT4& color) {
    Shader_Begin();

    // ’¸“_ƒoƒbƒtƒ@‚ğƒƒbƒN‚·‚é
    D3D11_MAPPED_SUBRESOURCE msr;
    g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
    Vertex* v = (Vertex*)msr.pData;

    v[0].position = { dx,      dy,      0.0f };
    v[1].position = { dx + dw, dy,      0.0f };
    v[2].position = { dx,      dy + dh, 0.0f };
    v[3].position = { dx + dw, dy + dh, 0.0f };

    v[0].color = color;
    v[1].color = color;
    v[2].color = color;
    v[3].color = color;

    v[0].uv = { 0.0f, 0.0f };
    v[1].uv = { 1.0f, 0.0f };
    v[2].uv = { 0.0f, 1.0f };
    v[3].uv = { 1.0f, 1.0f };

    g_pContext->Unmap(g_pVertexBuffer, 0);

    // ‰ñ“]s—ñ‚ğƒVƒF[ƒ_[‚Éİ’è
    Shader_SetWorldMatrix(XMMatrixIdentity());

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

    g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    Texture_SetTexture(texid);
    g_pContext->Draw(NUM_VERTEX, 0);
}

void Sprite_Draw(int texid, float dx, float dy, int px, int py, int pw, int ph, const XMFLOAT4& color) {
    Shader_Begin();

    D3D11_MAPPED_SUBRESOURCE msr;
    g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
    Vertex* v = (Vertex*)msr.pData;

    v[0].position = { dx,      dy,      0.0f };
    v[1].position = { dx + pw, dy,      0.0f };
    v[2].position = { dx,      dy + ph, 0.0f };
    v[3].position = { dx + pw, dy + ph, 0.0f };

    v[0].color = color;
    v[1].color = color;
    v[2].color = color;
    v[3].color = color;

    float tw = Texture_Width(texid);
    float th = Texture_Height(texid);

    float u0 = px / tw;
    float v0 = py / th;
    float u1 = (px + pw) / tw;
    float v1 = (py + ph) / th;

    v[0].uv = { u0, v0 };
    v[1].uv = { u1, v0 };
    v[2].uv = { u0, v1 };
    v[3].uv = { u1, v1 };

	// ’¸“_ƒoƒbƒtƒ@‚ÌƒƒbƒN‚ğ‰ğœ
    g_pContext->Unmap(g_pVertexBuffer, 0);

    // ‰ñ“]s—ñ‚ğƒVƒF[ƒ_[‚Éİ’è
    Shader_SetWorldMatrix(XMMatrixIdentity());

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

    g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    Texture_SetTexture(texid);
    g_pContext->Draw(NUM_VERTEX, 0);
}

void Sprite_Draw(int texid, float dx, float dy, float dw, float dh, int px, int py, int pw, int ph, const XMFLOAT4& color) {
    Shader_Begin();

    D3D11_MAPPED_SUBRESOURCE msr;
    g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
    Vertex* v = (Vertex*)msr.pData;

    v[0].position = { dx,      dy,      0.0f };
    v[1].position = { dx + dw, dy,      0.0f };
    v[2].position = { dx,      dy + dh, 0.0f };
    v[3].position = { dx + dw, dy + dh, 0.0f };

    v[0].color = color;
    v[1].color = color;
    v[2].color = color;
    v[3].color = color;

    float tw = Texture_Width(texid);
    float th = Texture_Height(texid);

    float u0 = px / tw;
    float v0 = py / th;
    float u1 = (px + pw) / tw;
    float v1 = (py + ph) / th;

    v[0].uv = { u0, v0 };
    v[1].uv = { u1, v0 };
    v[2].uv = { u0, v1 };
    v[3].uv = { u1, v1 };

    g_pContext->Unmap(g_pVertexBuffer, 0);

    // ‰ñ“]s—ñ‚ğƒVƒF[ƒ_[‚Éİ’è
    Shader_SetWorldMatrix(XMMatrixIdentity());

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

    g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    Texture_SetTexture(texid);
    g_pContext->Draw(NUM_VERTEX, 0);
}

void Sprite_Draw(int texid, float dx, float dy, float dw, float dh, int px, int py, int pw, int ph, float angle, const XMFLOAT4& color) {
    
    Shader_Begin();

    D3D11_MAPPED_SUBRESOURCE msr;
    g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
    Vertex* v = (Vertex*)msr.pData;

    v[0].position = { -0.5f, -0.5f, 0.0f };
    v[1].position = { +0.5f, -0.5f, 0.0f };
    v[2].position = { -0.5f, +0.5f, 0.0f };
    v[3].position = { +0.5f, +0.5f, 0.0f };

    v[0].color = color;
    v[1].color = color;
    v[2].color = color;
    v[3].color = color;

    float tw = Texture_Width(texid);
    float th = Texture_Height(texid);

    float u0 = px / tw;
    float v0 = py / th;
    float u1 = (px + pw) / tw;
    float v1 = (py + ph) / th;

    v[0].uv = { u0, v0 };
    v[1].uv = { u1, v0 };
    v[2].uv = { u0, v1 };
    v[3].uv = { u1, v1 };

    g_pContext->Unmap(g_pVertexBuffer, 0);

	// ‰ñ“]s—ñ‚ğƒVƒF[ƒ_[‚Éİ’è
	XMMATRIX scale = XMMatrixScaling(dw, dh, 1.0f);
	XMMATRIX rotation = XMMatrixRotationZ(angle);
    XMMATRIX translation = XMMatrixTranslation(dx, dy, 0.0f);
	
	Shader_SetWorldMatrix(scale * rotation * translation);

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

    g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    Texture_SetTexture(texid);
    g_pContext->Draw(NUM_VERTEX, 0);
}
