/*==============================================================================

   �|���S�� [polygon.cpp]
														 Author : LCH
														 Date   : 2025/05/15
--------------------------------------------------------------------------------

==============================================================================*/
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"
#include "debug_ostream.h"
#include <fstream>


static ID3D11VertexShader* g_pVertexShader = nullptr;
static ID3D11InputLayout* g_pInputLayout = nullptr;
static ID3D11Buffer* g_pVSConstantBuffer0 = nullptr;
static ID3D11Buffer* g_pVSConstantBuffer1 = nullptr;
static ID3D11PixelShader* g_pPixelShader = nullptr;
static ID3D11SamplerState* g_pSamplerState = nullptr;


static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;


bool Shader_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	HRESULT hr; // ??????{??

	// ?f?o?C?X??f?o?C?X?R???e?L?X?g??`?F?b?N
	if (!pDevice || !pContext) {
		hal::dout << "Shader_Initialize() have failed" << std::endl;
		return false;
	}

	// ?f?o?C?X??f?o?C?X?R???e?L?X?g????
	g_pDevice = pDevice;
	g_pContext = pContext;


	// ???O?R???p?C???????_?V?F?[?_?[???????
	std::ifstream ifs_vs("shader_vertex_2d.cso", std::ios::binary);

	if (!ifs_vs) {
		MessageBox(nullptr, "Shader vertex failed\n\nshader_vertex_2d.cso", "????`", MB_OK);
		return false;
	}

	// ?t?@?C???T?C?Y???��
	ifs_vs.seekg(0, std::ios::end);
	ifs_vs.seekg(0, std::ios::end); // ?t?@?C???|?C???^???????
	std::streamsize filesize = ifs_vs.tellg(); // ?t?@?C???|?C???^???u???��?i????t?@?C???T?C?Y?j
	ifs_vs.seekg(0, std::ios::beg);// ?t?@?C???|?C???^???????
	

	// ?o?C?i???f?[?^???i?[???????o?b?t?@???m??
	unsigned char* vsbinary_pointer = new unsigned char[filesize];

	ifs_vs.read((char*)vsbinary_pointer, filesize); // ?o?C?i???f?[?^???????
	ifs_vs.close(); // ?t?@?C????????


	// ???_?V?F?[?_?[???
	hr = g_pDevice->CreateVertexShader(vsbinary_pointer, filesize, nullptr, &g_pVertexShader);

	if (FAILED(hr)) {
		hal::dout << "Shader_Initialize() ?V?F?[?_?[??????????s???????" << std::endl;
		delete[] vsbinary_pointer; // ?????????[?N?????????o?C?i???f?[?^??o?b?t?@?????
		return false;
	}


	// ???_???C?A?E?g???`
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT num_elements = ARRAYSIZE(layout); // ?z???v?f?????��
	// ???_???C?A?E?g???
	hr = g_pDevice->CreateInputLayout(layout, num_elements, vsbinary_pointer, filesize, &g_pInputLayout);

	delete[] vsbinary_pointer; // ?o?C?i???f?[?^??o?b?t?@?????

	if (FAILED(hr)) {
		hal::dout << "Shader_Initialize() ?V?F?[?_?[??????????s???????" << std::endl;
		return false;
	}


	// ???_?V?F?[?_?[?p???o?b?t?@???
	D3D11_BUFFER_DESC buffer_desc{};
	buffer_desc.ByteWidth = sizeof(XMFLOAT4X4);// ?o?b?t?@??T?C?Y
	buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;  // ?o?C???h?t???O

	g_pDevice->CreateBuffer(&buffer_desc, nullptr, &g_pVSConstantBuffer0);
	g_pDevice->CreateBuffer(&buffer_desc, nullptr, &g_pVSConstantBuffer1);

	// ???O?R???p?C?????s?N?Z???V?F?[?_?[???????
	std::ifstream ifs_ps("shader_pixel_2d.cso", std::ios::binary);
	if (!ifs_ps) {
		MessageBox(nullptr, "?s?N?Z???V?F?[?_?[??????????s???????\n\nshader_pixel_2d.cso", "?G???[", MB_OK);
		return false;
	}

	ifs_ps.seekg(0, std::ios::end);
	filesize = ifs_ps.tellg();
	ifs_ps.seekg(0, std::ios::beg);

	unsigned char* psbinary_pointer = new unsigned char[filesize];
	ifs_ps.read((char*)psbinary_pointer, filesize);
	ifs_ps.close();

	// ?s?N?Z???V?F?[?_?[???
	hr = g_pDevice->CreatePixelShader(psbinary_pointer, filesize, nullptr, &g_pPixelShader);

	delete[] psbinary_pointer;  // ?o?C?i???f?[?^??o?b?t?@?????

	if (FAILED(hr)) {
		hal::dout << "Shader_Initialize() ?V?F?[?_?[??????????s???????" << std::endl;
		return false;
	}

	//?T???v???[?X?e?[?g???
	D3D11_SAMPLER_DESC sampler_desc = {};
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; // ???`???t?B???^?????O

	// UV?Q??O???��?? (UV?A?h???b?V???O???[?h)
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

	sampler_desc.BorderColor[0] = 0.0f;
	sampler_desc.BorderColor[1] = 0.0f;
	sampler_desc.BorderColor[2] = 0.0f;
	sampler_desc.BorderColor[3] = 0.0f;

	sampler_desc.MipLODBias = 0.0f;
	sampler_desc.MaxAnisotropy = 8;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampler_desc.MinLOD = 0.0f;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

	// ?T???v???[?X?e?[?g?????
	if (FAILED(g_pDevice->CreateSamplerState(&sampler_desc, &g_pSamplerState))) {
		return false;
	}

	return true;

}

void Shader_Finalize()
{
	SAFE_RELEASE(g_pSamplerState);
	SAFE_RELEASE(g_pPixelShader);
	SAFE_RELEASE(g_pVSConstantBuffer1);
	SAFE_RELEASE(g_pVSConstantBuffer0);
	SAFE_RELEASE(g_pInputLayout);
	SAFE_RELEASE(g_pVertexShader);
}

void Shader_SetWorldMatrix(const DirectX::XMMATRIX& matrix)
{
	// ???o?b?t?@?i?[?p?s???\??????`
	XMFLOAT4X4 transpose;

	// ?s???]?u??????o?b?t?@?i?[?p?s?????
	XMStoreFloat4x4(&transpose, XMMatrixTranspose(matrix));

	// ???o?b?t?@??s????Z?b?g
	g_pContext->UpdateSubresource(g_pVSConstantBuffer1, 0, nullptr, &transpose, 0, 0);
}

void Shader_SetProjectionMatrix(const DirectX::XMMATRIX& matrix)
{
	// ???o?b?t?@?i?[?p?s???\??????`
	XMFLOAT4X4 transpose;

	// ?s???]?u??????o?b?t?@?i?[?p?s?????
	XMStoreFloat4x4(&transpose, XMMatrixTranspose(matrix));

	// ???o?b?t?@??s????Z?b?g
	g_pContext->UpdateSubresource(g_pVSConstantBuffer0, 0, nullptr, &transpose, 0, 0);
}

void Shader_Begin()
{
	// ???_?V?F?[?_?[??s?N?Z???V?F?[?_?[??`??p?C?v???C??????
	g_pContext->VSSetShader(g_pVertexShader, nullptr, 0);
	g_pContext->PSSetShader(g_pPixelShader, nullptr, 0);

	// ???_???C?A?E?g??`??p?C?v???C??????
	g_pContext->IASetInputLayout(g_pInputLayout);

	// ???o?b?t?@??`??p?C?v???C??????
	g_pContext->VSSetConstantBuffers(0, 1, &g_pVSConstantBuffer0);
	g_pContext->VSSetConstantBuffers(1, 1, &g_pVSConstantBuffer1);

	//?T???v???[?X?e?[?g??`??p?C?v???C??????
	g_pContext->PSSetSamplers(0, 1, &g_pSamplerState);
}
