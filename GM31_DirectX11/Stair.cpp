//!============================================================
//!
//!  @file    : Stair.cpp
//!  @brief   : �K�i�N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �K�i�N���X�̎���
//!             �Q�[���I�u�W�F�N�g�N���X���p��
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
#include "GameScene.h"
#include "Model.h"
#include "Stair.h"


//============================================================
//�@�ϐ��錾
//============================================================
// �X�^�e�B�b�N�����o�ϐ���cpp�ōēx�錾���K�v
Model* Stair::model;


//============================================================
//�@�֐�
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : ������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : ����������
//!            ���f���̐���
//!            �V�F�[�_�[�̐ݒ�
//!-----------------------------------------------------------
void Stair::Init()
{
	// �ϐ�������
	position = D3DXVECTOR3(0.0f, 0.0f, 5.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// �V�F�[�_�[�̐���
	Renderer::CreateVertexShader(&vertexShader, &vertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&pixelShader, "vertexLightingPS.cso");

	// ���f���̐���
	//model = Resource::ResourceModelLoad("Asset\\Model\\item\\GM31_5.obj");
	model = Resource::ResourceModelLoad("Asset\\Model\\stair\\GM31_6.obj");
	//model = Resource::ResourceModelLoad("Asset\\Model\\riceball\\GM31_7.obj");
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : �I������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void Stair::Uninit()
{
	
}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void Stair::Update()
{
	
}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : �`�������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �V�F�[�_�[�̐ݒ�
//!            �}�g���N�X�̐ݒ�
//!            ���f���̕`��
//!-----------------------------------------------------------
void Stair::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(vertexLayout);

	// �V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(vertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(pixelShader, NULL, 0);

	// �}�g���N�X�ݒ�
	D3DXMATRIX World, Scale, Rotate, Trans;
	D3DXMatrixScaling(&Scale, this->scale.x, this->scale.y, this->scale.z);
	D3DXMatrixRotationYawPitchRoll(&Rotate, this->rotation.y, this->rotation.x, this->rotation.z);
	D3DXMatrixTranslation(&Trans, this->position.x, this->position.y, this->position.z);
	World = Scale * Rotate * Trans;
	Renderer::SetWorldMatrix(&World);

	// ���f���̕`��
	model->Draw();
}
