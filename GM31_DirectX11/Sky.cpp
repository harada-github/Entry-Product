//!============================================================
//!
//!  @file    : Sky.cpp
//!  @brief   : �X�J�C�h�[���N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �X�J�C�h�[�������̃N���X
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
#include "Model.h"
#include "Sky.h"


//============================================================
//�@�ϐ��錾
//============================================================
Model* Sky::model;


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
//!            ���f���̓����ɉ摜�𒣂�I�u�W�F�N�g��傫�������邱�Ƃŕ\��
//!-----------------------------------------------------------
void Sky::Init()
{
	position = D3DXVECTOR3(0.0f, 0.0f, -6.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale    = D3DXVECTOR3(100.0f, 100.0f, 100.0f);

	// �V�F�[�_�[�̐���
	Renderer::CreateVertexShader(&vertexShader, &vertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&pixelShader, "unlitTexturePS.cso");

	// ���f���̐���
	model = Resource::ResourceModelLoad("Asset\\Model\\sky\\sky.obj");
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : �I������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void Sky::Uninit()
{
	
}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void Sky::Update()
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
void Sky::Draw()
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
