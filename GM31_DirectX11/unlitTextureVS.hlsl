//!============================================================
//!
//!  @file    : unlitTextureVS.hlsl
//!  @brief   : ライティングなしテクスチャ用の頂点シェーダー
//!  @author  : 原田 陽央
//!  @details : ライティングなしテクスチャ用の頂点シェーダー
//!
//!============================================================
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{

	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

	Out.Position = mul(In.Position, wvp);
	Out.TexCoord = In.TexCoord;
	Out.Diffuse = In.Diffuse;

}

