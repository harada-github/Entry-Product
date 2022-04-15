//!============================================================
//!
//!  @file    : Block.cpp
//!  @brief   : �u���b�N�N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �u���b�N�̎���
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
#include "Scene.h"
#include "Camera.h"
#include "Model.h"
#include "Block.h"


//============================================================
//�@�ϐ��錾
//============================================================
Model* Block::model;


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
void Block::Init()
{
	// �ϐ�������
	position = D3DXVECTOR3(0.0f, 0.0f, 5.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 0.5f, 1.0f);

	isDraw = false;
	
	// �V�F�[�_�[�̐���
	Renderer::CreateVertexShader(&vertexShader, &vertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&pixelShader, "vertexLightingPS.cso");

	// ���f���̐���
	model = Resource::ResourceModelLoad("Asset\\Model\\block\\GM31_4.obj");
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : �I������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void Block::Uninit()
{
	
}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void Block::Update()
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
void Block::Draw()
{
	// ������J�����O
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(CAMERA_LAYER);
	
	if (!camera->CheckView(position))
	{
		return;
	}

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


//!-----------------------------------------------------------
//! @fn      : SetIsDraw(bool setIsDraw)
//! @brief   : �`������邩���݂�ύX
//! @param   : setIsDraw...true�܂���false
//! @return  : �Ȃ�
//! @details : ������ true �Ȃ�`���L��
//!                   false �Ȃ�`��𖳌�   
//!-----------------------------------------------------------
void Block::SetIsDraw(bool setIsDraw)
{
	isDraw = setIsDraw;
}
