/*==============================================================================

   2D shaderpixel[shader_pixel_2d.hlsl]S				 Author : LCH
														 Date   : 2025/05/15
--------------------------------------------------------------------------------

==============================================================================*/

struct PS_IN
{
    float4 posH : SV_POSITION;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
};

Texture2D tex;     // ?e?N?X?`??
SamplerState samp; //

float4 main(PS_IN pi) : SV_TARGET
{
    // a * b
    //a.r * b.r a.g * b.g a.b * b.b a.a *b.a
    return tex.Sample(samp, pi.uv) * pi.color;
}
