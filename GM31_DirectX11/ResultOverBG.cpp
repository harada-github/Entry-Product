//!============================================================
//!
//!  @file    : ResultOverBG.h
//!  @brief   : �Q�[���I�[�o�[��ʂ̔w�i�I�u�W�F�N�g�N���X�̃w�b�_�[�t�@�C��
//!  @author  : ���c �z��
//!  @details : �Q�[���I�[�o�[��ʂ̔w�i�I�u�W�F�N�g
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
#include "ResultOverBG.h"


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
void ResultOverBG::Init()
{
	// ���_�̃f�[�^�ł�����
	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	vertex[1].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	vertex[2].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	vertex[3].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	// �e�N�X�`���̓ǂݍ���
	texture = Resource::ResourceTextureLoad("Asset/Texture/gmover.JPG");
	
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
void ResultOverBG::Uninit()
{
	
}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void ResultOverBG::Update()
{

}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : �`�������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �p������Draw�֐��̌Ăяo��
//!-----------------------------------------------------------
void ResultOverBG::Draw()
{
	// �p�����̃��\�b�h���Ăяo��
	Polygon2D::Draw();
}
