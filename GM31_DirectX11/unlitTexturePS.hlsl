//!============================================================
//!
//!  @file    : unlitTexturePS.hlsl
//!  @brief   : ライティングなしテクスチャ用のピクセルシェーダー
//!  @author  : 原田 陽央
//!  @details : ライティングなしテクスチャ用のピクセルシェーダー
//!
//!============================================================
#include "common.hlsl"


Texture2D		g_Texture : register( t0 );
SamplerState	g_SamplerState : register( s0 );


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);	
	outDiffuse *= In.Diffuse;
}
