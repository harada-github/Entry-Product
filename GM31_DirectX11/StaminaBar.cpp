//!============================================================
//!
//!  @file    : StaminaBar.cpp
//!  @brief   : �X�^�~�i�̃Q�[�W�o�[�N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �X�^�~�i�̃Q�[�W�o�[�̃I�u�W�F�N�g
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
#include "StaminaBar.h"
#include "Scene.h"
#include "DungeonPlayer.h"


//============================================================
//�@�ϐ��錾
//============================================================
static Scene* scene = NULL;


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
void StaminaBar::Init()
{
	// �V�[���̏��̎擾
	scene = Manager::GetScene();

	//�Z���_�̃f�[�^�ł����݁Z
	vertex[0].Position = D3DXVECTOR3(850.0f, 70.0f, 0.0f);
	vertex[0].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(1250.0f, 70.0f, 0.0f);
	vertex[1].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(850.0f, 110.0f, 0.0f);
	vertex[2].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(1250.0f, 110.0f, 0.0f);
	vertex[3].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
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
void StaminaBar::Uninit()
{

}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �v���C���[�̃X�^�~�i���擾����
//!            �Z�o���������ɂ���ăQ�[�W�̕���ύX����
//!-----------------------------------------------------------
void StaminaBar::Update()
{
	// �v���C���[�̃X�^�~�i��\������^�C�v�̏ꍇ�̏���
	if (barType == 1)
	{
		// �v���C���[�̏����擾
		DungeonPlayer* dungeonPlayer = scene->GetGameObject<DungeonPlayer>(OBJECT3D_LAYER);

		// �v���C���[�̃X�^�~�i���犄�����Z�o
		float staminaPercent = dungeonPlayer->GetHitPoint() / 100.0f;

		// �Q�[�W�o�[���X�V
		vertex[0].Position = D3DXVECTOR3(850.0f, 70.0f, 0.0f);
		vertex[1].Position = D3DXVECTOR3(850.0f + (staminaPercent * 400.0f), 70.0f, 0.0f);
		vertex[2].Position = D3DXVECTOR3(850.0f, 110.0f, 0.0f);
		vertex[3].Position = D3DXVECTOR3(850.0f + (staminaPercent * 400.0f), 110.0f, 0.0f);

		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);
	}
}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : �`�������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �p������Draw�֐��̌Ăяo��
//!-----------------------------------------------------------
void StaminaBar::Draw()
{
	// �p�����̃��\�b�h���Ăяo��
	Polygon2D::Draw();
}


//!-----------------------------------------------------------
//! @fn      : SetBarType()
//! @brief   : �Q�[�W�o�[�̃^�C�v�̐ݒ�
//! @param   : setBarType
//! @return  : �Ȃ�
//! @details : ��������Q�[�W�o�[�̃^�C�v�̐ݒ�
//!-----------------------------------------------------------
void StaminaBar::SetBarType(int setBarType)
{
	barType = setBarType;
}
