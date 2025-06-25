/*==============================================================================

   ポリゴン描画 [polygon.cpp]

														 Author : Youhei Sato

														 Date   : 2025/05/15

--------------------------------------------------------------------------------

==============================================================================*/

#include <d3d11.h>

#include <DirectXMath.h>

#include "DirectXTex.h"

using namespace DirectX;

#include "direct3d.h"

#include "shader.h"

#include "debug_ostream.h"

#include "polygon.h"

#pragma comment(lib, "d3d11.lib")

static constexpr int NUM_VERTEX = 4; // 頂点数


static ID3D11Buffer* g_pVertexBuffer = nullptr; // 頂点バッファ

static ID3D11ShaderResourceView* g_pTexture = nullptr;// テクスチャ


// 注意！初期化で外部から設定されるもの。Release不要。

static ID3D11Device* g_pDevice = nullptr;

static ID3D11DeviceContext* g_pContext = nullptr;

static int g_NumVertex = 0; // 現在の頂点数（初期化時に設定される）
static float g_Radius = 100.0f; // ポリゴンの半径（初期化時に設定される）
static float g_Cx = 1000.0f; // ポリゴンの中心X座標（初期化時に設定される）
static float g_Cy = 500.0f; // ポリゴンの中心Y座標（初期化時に設定される）
// 頂点構造体

struct Vertex

{

	XMFLOAT3 position; // 頂点座標

	XMFLOAT4 color;    // 色

	XMFLOAT2 texcoord;       // UV(texcoord テクスチャー座標)

};


void Polygon_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)

{

	// デバイスとデバイスコンテキストのチェック

	if (!pDevice || !pContext) {

		hal::dout << "Polygon_Initialize() : 与えられたデバイスかコンテキストが不正です" << std::endl;

		return;

	}

	// デバイスとデバイスコンテキストの保存

	g_pDevice = pDevice;

	g_pContext = pContext;

	// 点の数を設定
	g_NumVertex = g_Radius * 2.0f * XM_PI; // 半径の2倍を頂点数とする

	// 頂点バッファ生成

	D3D11_BUFFER_DESC bd = {};

	bd.Usage = D3D11_USAGE_DYNAMIC;

	bd.ByteWidth = sizeof(Vertex) * g_NumVertex;

	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	g_pDevice->CreateBuffer(&bd, NULL, &g_pVertexBuffer);

	// テクスチャ読み込み

	TexMetadata metadata;

	ScratchImage image;

	LoadFromWICFile(L"white.png", WIC_FLAGS_NONE, &metadata, image);

	HRESULT hr = CreateShaderResourceView(g_pDevice, image.GetImages(), image.GetImageCount(), metadata, &g_pTexture);

	if (FAILED(hr)) {

		MessageBox(nullptr, "テクスチャの読み込みに失敗した", "エラー", MB_OK | MB_ICONERROR);

	}

}

void Polygon_Finalize(void)

{

	SAFE_RELEASE(g_pTexture);

	SAFE_RELEASE(g_pVertexBuffer);

}

void Polygon_Draw(void)

{

	// シェーダーを描画パイプラインに設定

	Shader_Begin();

	// 頂点バッファをロックする

	D3D11_MAPPED_SUBRESOURCE msr;

	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// 頂点バッファへの仮想ポインタを取得

	Vertex* v = (Vertex*)msr.pData;

	// 頂点情報を書き込み

	const float SCREEN_WIDTH = (float)Direct3D_GetBackBufferWidth();

	const float SCREEN_HEIGHT = (float)Direct3D_GetBackBufferHeight();

	constexpr float h = 512.0f;

	// 画面の左上から右下に向かう線分を描画する
	const float rad = XM_2PI / g_NumVertex; // 1頂点あたりの角度
	// 頂点数分ループして頂点情報を設定
	for (int i = 0; i < g_NumVertex; ++i) {
		float angle = rad * i; // 現在の頂点の角度
		v[i].position.x = g_Cx + g_Radius * cosf(angle); // X座標
		v[i].position.y = g_Cy + g_Radius * sinf(angle); // Y座標
		v[i].position.z = 0.0f; // Z座標（2Dなので0）
		v[i].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f); // 白色
		v[i].texcoord = { 0.0f, 0.0f }; // UV座標（テクスチャ座標）
	}

	// 頂点バッファのロックを解除
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// 頂点バッファを描画パイプラインに設定

	UINT stride = sizeof(Vertex);

	UINT offset = 0;

	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// 頂点シェーダーに変換行列を設定

	Shader_SetProjectionMatrix(XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));

	// プリミティブトポロジ設定

	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	// テクスチャ設定

	// g_pContext->PSSetShaderResources(0, 1, &g_pTexture);

	// ポリゴン描画命令発行

	g_pContext->Draw(g_NumVertex, 0);

}
