//!============================================================
//!
//!  @file    : unlitTexturePS.hlsl
//!  @brief   : ���C�e�B���O�Ȃ��e�N�X�`���p�̃s�N�Z���V�F�[�_�[
//!  @author  : ���c �z��
//!  @details : ���C�e�B���O�Ȃ��e�N�X�`���p�̃s�N�Z���V�F�[�_�[
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