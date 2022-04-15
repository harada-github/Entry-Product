//!============================================================
//!
//!  @file    : Fade.cpp
//!  @brief   : �t�F�[�h�N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : ��ʂ̃t�F�[�h���s���t�F�[�h�I�u�W�F�N�g�̎���
//!             �|���S��2D�N���X���p��
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
#include "Fade.h"


//============================================================
//�@�ϐ��錾
//============================================================
int Fade::fadeType;
float Fade::fadeAlpha;


//============================================================
//�@�֐�
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : ������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �ϐ��̏�����
//!            ���_�f�[�^�̑ł�����
//!            �e�N�X�`���̓ǂݍ���
//!            �V�F�[�_�[�̐ݒ�
//!-----------------------------------------------------------
void Fade::Init()
{
	// �ϐ�������
	fadeType = 0;
	fadeAlpha = 0.0f;

	// ���_�̃f�[�^�ł�����
	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	vertex[1].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	vertex[2].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	vertex[3].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	// �e�N�X�`���̓ǂݍ���
	texture = Resource::ResourceTextureLoad("Asset/Texture/bg_white.jpg");

	// �G���[�`�F�b�N
	if (texture == NULL)
	{
		return;
	}
	assert(texture);

	// �R���p�C���ς݂̃V�F�[�_�[�v���O�����������œǂݍ���
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
void Fade::Uninit()
{
	
}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �A���t�@�̒l��ω�������
//!            �t�F�[�h�C���E�A�E�g�̎������s��
//!-----------------------------------------------------------
void Fade::Update()
{
	if (fadeType == 0)
	{

	}
	else if (fadeType == 1)
	{
		fadeAlpha -= 0.01f;

		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);
	}
	else if (fadeType == 2)
	{
		fadeAlpha += 0.01f;

		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);
	}

	if (fadeAlpha >= 1.05f || fadeAlpha <= -0.05f)
	{
		fadeType = 0;
	}
}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : �`�������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : @details : �p������Draw�֐��̌Ăяo��
//!-----------------------------------------------------------
void Fade::Draw()
{
	// �p�����̃��\�b�h���Ăяo��
	Polygon2D::Draw();
}


//!-----------------------------------------------------------
//! @fn      : SetFade(int type)
//! @brief   : �t�F�[�h�̃Z�b�g
//! @param   : type.....�t�F�[�h�̃^�C�v
//! @return  : �Ȃ�
//! @details : �O���I�Ƀt�F�[�h�̃Z�b�g����ۂɎg�p
//!            ��ʂ������Ȃ�A������Ԃ���ʏ�̉�ʂɂȂ�t�F�[�h
//!            type ��1�Ȃ�t�F�[�h�C���A2�Ȃ�t�F�[�h�A�E�g
//!-----------------------------------------------------------
void Fade::SetFade(int type)
{
	fadeType = type;

	if (fadeType == 0)
	{
		
	}
	else if (fadeType == 1)
	{
		fadeAlpha = 1.0f;
	}
	else if (fadeType == 2)
	{
		fadeAlpha = 0.0f;
	}
}


//!-----------------------------------------------------------
//! @fn      : GetFadeType()
//! @brief   : �t�F�[�h�̃^�C�v�̎擾
//! @param   : �Ȃ�
//! @return  : type�i���݂̃t�F�[�h�̃^�C�v�j
//! @details : ���݂̃t�F�[�h�̃^�C�v���擾����
//!-----------------------------------------------------------
int Fade::GetFadeType()
{
	return fadeType;
}
