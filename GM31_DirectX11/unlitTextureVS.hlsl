//!============================================================
//!
//!  @file    : unlitTextureVS.hlsl
//!  @brief   : ���C�e�B���O�Ȃ��e�N�X�`���p�̒��_�V�F�[�_�[
//!  @author  : ���c �z��
//!  @details : ���C�e�B���O�Ȃ��e�N�X�`���p�̒��_�V�F�[�_�[
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

