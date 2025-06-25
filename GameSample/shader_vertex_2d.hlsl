/*==============================================================================

   2D�V�F�[�_�[�o�[�e�N�X�e [shader_vertex_2d.hlsl]
														 Author : LCH
														 Date   : 2025/05/15
--------------------------------------------------------------------------------

==============================================================================*/
// �萔�o�b�t�@
cbuffer VS_CONSTANT_BUFFER : register(b0)
{
    float4x4 proj; // �v���W�F�N�V�����ϊ��s��
    
};

cbuffer VS_CONSTANT_BUFFER : register(b1)
{
    float4x4 world; // ���[���h�ϊ��s��
    
};

struct VS_IN
{
    float4 posL : POSITION0;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
};

struct VS_OUT
{
    float4 posH : SV_POSITION;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
};

//=============================================================================
// ���_�V�F�[�_
//=============================================================================
VS_OUT main(VS_IN vi)
{
    VS_OUT vo;
    
    // ���W�ϊ�
    float4x4 mtx = mul(world, proj); // ���[���h���W���N���b�v���W�ɕϊ�����s����v�Z)
    
  //  vi.posL = mul(vi.posL, world); // ���[�J�����W�����[���h���W�ɕϊ�
  //  vi.posL = mul(vi.posL, proj); // ���[���h���W���N���b�v���W�ɕϊ�
    
    vo.posH = mul(vi.posL, mtx);
    vo.color = vi.color;
    vo.uv = vi.uv;
    
    return vo;
}