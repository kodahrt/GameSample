/*==============================================================================

   2Dシェーダーバーテクステ [shader_vertex_2d.hlsl]
														 Author : LCH
														 Date   : 2025/05/15
--------------------------------------------------------------------------------

==============================================================================*/
// 定数バッファ
cbuffer VS_CONSTANT_BUFFER : register(b0)
{
    float4x4 proj; // プロジェクション変換行列
    
};

cbuffer VS_CONSTANT_BUFFER : register(b1)
{
    float4x4 world; // ワールド変換行列
    
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
// 頂点シェーダ
//=============================================================================
VS_OUT main(VS_IN vi)
{
    VS_OUT vo;
    
    // 座標変換
    float4x4 mtx = mul(world, proj); // ワールド座標をクリップ座標に変換する行列を計算)
    
  //  vi.posL = mul(vi.posL, world); // ローカル座標をワールド座標に変換
  //  vi.posL = mul(vi.posL, proj); // ワールド座標をクリップ座標に変換
    
    vo.posH = mul(vi.posL, mtx);
    vo.color = vi.color;
    vo.uv = vi.uv;
    
    return vo;
}