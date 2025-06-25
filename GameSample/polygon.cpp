/*==============================================================================

   �|���S���`�� [polygon.cpp]

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

static constexpr int NUM_VERTEX = 4; // ���_��


static ID3D11Buffer* g_pVertexBuffer = nullptr; // ���_�o�b�t�@

static ID3D11ShaderResourceView* g_pTexture = nullptr;// �e�N�X�`��


// ���ӁI�������ŊO������ݒ肳�����́BRelease�s�v�B

static ID3D11Device* g_pDevice = nullptr;

static ID3D11DeviceContext* g_pContext = nullptr;

static int g_NumVertex = 0; // ���݂̒��_���i���������ɐݒ肳���j
static float g_Radius = 100.0f; // �|���S���̔��a�i���������ɐݒ肳���j
static float g_Cx = 1000.0f; // �|���S���̒��SX���W�i���������ɐݒ肳���j
static float g_Cy = 500.0f; // �|���S���̒��SY���W�i���������ɐݒ肳���j
// ���_�\����

struct Vertex

{

	XMFLOAT3 position; // ���_���W

	XMFLOAT4 color;    // �F

	XMFLOAT2 texcoord;       // UV(texcoord �e�N�X�`���[���W)

};


void Polygon_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)

{

	// �f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̃`�F�b�N

	if (!pDevice || !pContext) {

		hal::dout << "Polygon_Initialize() : �^����ꂽ�f�o�C�X���R���e�L�X�g���s���ł�" << std::endl;

		return;

	}

	// �f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̕ۑ�

	g_pDevice = pDevice;

	g_pContext = pContext;

	// �_�̐���ݒ�
	g_NumVertex = g_Radius * 2.0f * XM_PI; // ���a��2�{�𒸓_���Ƃ���

	// ���_�o�b�t�@����

	D3D11_BUFFER_DESC bd = {};

	bd.Usage = D3D11_USAGE_DYNAMIC;

	bd.ByteWidth = sizeof(Vertex) * g_NumVertex;

	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	g_pDevice->CreateBuffer(&bd, NULL, &g_pVertexBuffer);

	// �e�N�X�`���ǂݍ���

	TexMetadata metadata;

	ScratchImage image;

	LoadFromWICFile(L"white.png", WIC_FLAGS_NONE, &metadata, image);

	HRESULT hr = CreateShaderResourceView(g_pDevice, image.GetImages(), image.GetImageCount(), metadata, &g_pTexture);

	if (FAILED(hr)) {

		MessageBox(nullptr, "�e�N�X�`���̓ǂݍ��݂Ɏ��s����", "�G���[", MB_OK | MB_ICONERROR);

	}

}

void Polygon_Finalize(void)

{

	SAFE_RELEASE(g_pTexture);

	SAFE_RELEASE(g_pVertexBuffer);

}

void Polygon_Draw(void)

{

	// �V�F�[�_�[��`��p�C�v���C���ɐݒ�

	Shader_Begin();

	// ���_�o�b�t�@�����b�N����

	D3D11_MAPPED_SUBRESOURCE msr;

	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// ���_�o�b�t�@�ւ̉��z�|�C���^���擾

	Vertex* v = (Vertex*)msr.pData;

	// ���_������������

	const float SCREEN_WIDTH = (float)Direct3D_GetBackBufferWidth();

	const float SCREEN_HEIGHT = (float)Direct3D_GetBackBufferHeight();

	constexpr float h = 512.0f;

	// ��ʂ̍��ォ��E���Ɍ�����������`�悷��
	const float rad = XM_2PI / g_NumVertex; // 1���_������̊p�x
	// ���_�������[�v���Ē��_����ݒ�
	for (int i = 0; i < g_NumVertex; ++i) {
		float angle = rad * i; // ���݂̒��_�̊p�x
		v[i].position.x = g_Cx + g_Radius * cosf(angle); // X���W
		v[i].position.y = g_Cy + g_Radius * sinf(angle); // Y���W
		v[i].position.z = 0.0f; // Z���W�i2D�Ȃ̂�0�j
		v[i].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f); // ���F
		v[i].texcoord = { 0.0f, 0.0f }; // UV���W�i�e�N�X�`�����W�j
	}

	// ���_�o�b�t�@�̃��b�N������
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// ���_�o�b�t�@��`��p�C�v���C���ɐݒ�

	UINT stride = sizeof(Vertex);

	UINT offset = 0;

	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// ���_�V�F�[�_�[�ɕϊ��s���ݒ�

	Shader_SetProjectionMatrix(XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));

	// �v���~�e�B�u�g�|���W�ݒ�

	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	// �e�N�X�`���ݒ�

	// g_pContext->PSSetShaderResources(0, 1, &g_pTexture);

	// �|���S���`�施�ߔ��s

	g_pContext->Draw(g_NumVertex, 0);

}
