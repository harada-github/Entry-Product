//!============================================================
//!
//!  @file    : TitlePress.cpp
//!  @brief   : �^�C�g����ʂ̃v���X�G���^�[�I�u�W�F�N�g�N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �^�C�g����ʂ̃v���X�G���^�[�I�u�W�F�N�g
//!             �|���S��2D�N���X�N���X���p��
//!
//!============================================================
#pragma once


//============================================================
//�@�C���N���[�h
//============================================================
#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "Resource.h"
#include "TitlePress.h"


//============================================================
//�@�֐�
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : ������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : ���_�f�[�^�̑ł�����
//!            �e�N�X�`���̓ǂݍ���
//!            �V�F�[�_�[�̐ݒ�
//!-----------------------------------------------------------
void TitlePress::Init()
{
	float temp = 190.0f;

	//�Z���_�̃f�[�^�ł����݁Z
	vertex[0].Position = D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 + temp, 0.0f);
	vertex[0].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH / 4 * 3, SCREEN_HEIGHT / 4 + temp, 0.0f);
	vertex[1].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 * 3 + temp, 0.0f);
	vertex[2].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH / 4 * 3, SCREEN_HEIGHT / 4 * 3 + temp, 0.0f);
	vertex[3].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	//�Z�e�N�X�`���̓ǂݍ��݁Z
	texture = Resource::ResourceTextureLoad("Asset/Texture/�v���X�G���^�[.png");

	// �G���[�`�F�b�N
	if (texture == NULL)
	{
		return;
	}

	assert(texture);

	//�Z�R���p�C���ς݃V�F�[�_�[�v���O�����̓ǂݍ��݁Z
	Renderer::CreateVertexShader(&vertexShader, &vertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&pixelShader, "unlitTexturePS.cso");

	// �p�����̃��\�b�h���Ăяo��
	Polygon2D::Init();
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : �I������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void TitlePress::Uninit()
{

}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void TitlePress::Update()
{
	frame++;

	if (frame <= 40)
	{
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (frame <= 80)
	{
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f);
	}
	else
	{
		frame = 0;
	}
	
	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);
}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : �`�������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �p������Draw�֐��̌Ăяo��
//!-----------------------------------------------------------
void TitlePress::Draw()
{
	// �p�����̃��\�b�h���Ăяo��
	Polygon2D::Draw();
}
