//!============================================================
//!
//!  @file    : TitleName.cpp
//!  @brief   : �^�C�g����ʂ̃^�C�g���N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �^�C�g����ʂ̃^�C�g���I�u�W�F�N�g
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
#include "TitleName.h"


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
void TitleName::Init()
{
	// �ϐ��̏�����
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	mass = 1.0f;
	tension.x = 0.0f;
	tension.y = 0.0f;
	deltaTime = 0.03f;
	position.x = SCREEN_WIDTH  / 2;
	position.y = SCREEN_HEIGHT / 2 - 300.0f;

	// ���_�̃f�[�^�ł�����
	vertex[0].Position = D3DXVECTOR3(position.x - SCREEN_WIDTH / 5 * 2, position.y - SCREEN_HEIGHT / 5 * 2, 0.0f);
	vertex[0].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(position.x + SCREEN_WIDTH / 5 * 2, position.y - SCREEN_HEIGHT / 5 * 2, 0.0f);
	vertex[1].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(position.x - SCREEN_WIDTH / 5 * 2, position.y + SCREEN_HEIGHT / 5 * 2, 0.0f);
	vertex[2].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(position.x + SCREEN_WIDTH / 5 * 2, position.y + SCREEN_HEIGHT / 5 * 2, 0.0f);
	vertex[3].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	// �e�N�X�`���̓ǂݍ���
	texture = Resource::ResourceTextureLoad("Asset/Texture/�t�V�M�̃_���W����.png");

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
void TitleName::Uninit()
{

}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : ���́A�d�́A��R��������l�����߂�
//!            ���̒l������W���X�V����
//!-----------------------------------------------------------
void TitleName::Update()
{
	// ����
	tension.x = (640.0f - position.x) * 2.0f;
	tension.y = (300.0f - position.y) * 2.0f;

	// �d��
	tension.y += 9.8f * mass;

	// ��R
	tension.x -= velocity.x * 0.6f;
	tension.y -= velocity.y * 0.6f;

	// ���͂ɂ�����
	velocity.x += (tension.x / mass) * deltaTime;
	velocity.y += (tension.y / mass) * deltaTime;

	// �ړ�
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;

	// ���W�̍X�V
	vertex[0].Position = D3DXVECTOR3(position.x - SCREEN_WIDTH / 5 * 2, position.y - SCREEN_HEIGHT / 5 * 2, 0.0f);
	vertex[1].Position = D3DXVECTOR3(position.x + SCREEN_WIDTH / 5 * 2, position.y - SCREEN_HEIGHT / 5 * 2, 0.0f);
	vertex[2].Position = D3DXVECTOR3(position.x - SCREEN_WIDTH / 5 * 2, position.y + SCREEN_HEIGHT / 5 * 2, 0.0f);
	vertex[3].Position = D3DXVECTOR3(position.x + SCREEN_WIDTH / 5 * 2, position.y + SCREEN_HEIGHT / 5 * 2, 0.0f);
	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);
}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : �`�������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �p������Draw�֐��̌Ăяo��
//!-----------------------------------------------------------
void TitleName::Draw()
{
	// �p�����̃��\�b�h���Ăяo��
	Polygon2D::Draw();
}
