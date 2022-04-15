//!============================================================
//!
//!  @file    : DungeonPlayer.cpp
//!  @brief   : �v���C���[�N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �v���C���[�N���X�̎���
//!             �Q�[���I�u�W�F�N�g�N���X���p��
//!
//!============================================================
#pragma once


//============================================================
//�@�C���N���[�h
//============================================================
#include <time.h>
#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "Scene.h"
#include "GameScene.h"
#include "Resource.h"
#include "Keylogger.h"
#include "Audio.h"
#include "Camera.h"
#include "DungeonPlayer.h"
#include "DungeonEnemy.h"
#include "DungeonMap.h"
#include "Block.h"
#include "Stair.h"


//============================================================
//�@�ϐ��錾
//============================================================
static Scene* scene = NULL;
//AnimationModel* DungeonPlayer::aniModel;
Audio* DungeonPlayer::audioSE;

//DungeonEnemy* dungeonEnemy = NULL;
std::vector<DungeonEnemy*> enemysList;


//============================================================
//�@�֐�
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : ������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : ����������
//!            �A�j���[�V�������f���̐���
//!            �V�F�[�_�[�̐ݒ�
//!            �V�[���̏��̎擾
//!            �g�p����I�[�f�B�I�̃��[�h
//!-----------------------------------------------------------
void DungeonPlayer::Init()
{
	// �V�[���̏��̎擾
	scene = Manager::GetScene();

	// �_���W�����}�b�v�̎擾
	dungeonMap = scene->GetGameObject<DungeonMap>(OBJECT3D_LAYER);

	// �ϐ�������
	xMapNumber = xPreMapNumber = 26;
	zMapNumber = zPreMapNumber = 10;

	// �X�e�[�^�X������
	hitPoint = 100.0f;

	// �v���C���[�̈ʒu�������_���ɐݒ�
	// ���̕ǂ��l�����������𐶐�
	int mapDataX = (rand() % DUNGEON_MAP_DATA_X - 2) + 1;
	int mapDataZ = (rand() % DUNGEON_MAP_DATA_Z - 2) + 1;

	// �������������ɑΉ������ʒu���v���C���[��ݒ�ł���ꏊ�ɂȂ�܂ŁA�����𐶐�����
	while (!dungeonMap->IsMapDataMove(mapDataX, mapDataZ))
	{
		mapDataX = (rand() % DUNGEON_MAP_DATA_X - 2) + 1;
		mapDataZ = (rand() % DUNGEON_MAP_DATA_Z - 2) + 1;
	}

	// �ϐ�������
	xMapNumber = xPreMapNumber = mapDataX;
	zMapNumber = zPreMapNumber = mapDataZ;

	// �ݒ肷��ʒu��Ԃ�
	position = dungeonMap->GetCenterPosition(mapDataX, mapDataZ);

	// �ϐ��̏�����
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale    = D3DXVECTOR3(0.02f, 0.02f, 0.02f);
	move     = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	isMove   = false;
	aniFrame = 0;
	aniType  = 1;

	// �V�F�[�_�[�̐���
	Renderer::CreateVertexShader(&vertexShader, &vertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&pixelShader, "vertexLightingPS.cso");

	// ���f���̐���
	aniModel = Resource::ResourceAnimationModelLoad("Asset\\Model\\animationTest\\Akai_Idle.fbx");
	aniModel->LoadAnimation("Asset\\Model\\animationTest\\Akai_Idle.fbx", "Idle");
	aniModel->LoadAnimation("Asset\\Model\\animationTest\\Akai_Walking.fbx", "Walking");
	aniModel->LoadAnimation("Asset\\Model\\animationTest\\Akai_SwingDancing.fbx", "SwingDancing");
	aniModel->LoadAnimation("Asset\\Model\\animationTest\\Akai_HurricaneKick.fbx", "HurricaneKick");

	// SE�̃��[�h
	audioSE = Resource::ResourceAudioLoad("Asset\\Sound\\jump.wav");
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : �I������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void DungeonPlayer::Uninit()
{

}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �L�[���͂ł̈ړ�
//!            ���I�u�W�F�N�g�Ƃ̓����蔻��
//!            �A�j���[�V�������f���̍X�V
//!-----------------------------------------------------------
void DungeonPlayer::Update()
{
	// �J������������^�C�v�����擾
	Camera* camera = scene->GetGameObject<Camera>(CAMERA_LAYER);

	// �J�����������Ȃ��^�C�v�̏ꍇ�̓v���C���[�̓��삪�\
	if (!camera->CheckOnlyCameraMove())
	{
		// �L�[���͂ňړ�
		if (Keylogger_Press(KL_W) && Keylogger_Press(KL_D))
		{
			SetMoveVector(4);
		}
		else if (Keylogger_Press(KL_W) && Keylogger_Press(KL_A))
		{
			SetMoveVector(5);
		}
		else if (Keylogger_Press(KL_S) && Keylogger_Press(KL_D))
		{
			SetMoveVector(6);
		}
		else if (Keylogger_Press(KL_S) && Keylogger_Press(KL_A))
		{
			SetMoveVector(7);
		}
		else if (Keylogger_Press(KL_W))
		{
			SetMoveVector(0);
		}
		else if (Keylogger_Press(KL_S))
		{
			SetMoveVector(1);
		}
		else if (Keylogger_Press(KL_D))
		{
			SetMoveVector(2);
		}
		else if (Keylogger_Press(KL_A))
		{
			SetMoveVector(3);
		}
		else
		{
			aniType = 1;
		}
	}


	// �ړ����Ă���Ԃ̏���
	if (isMove)
	{
		// �ړ��t���[�����X�V
		moveFrame++;

		// ���W���X�V
		position += move;

		// �A�j���[�V�����̐ݒ�
		aniType = 2;
	}
	if (moveFrame >= moveFrameMax)
	{
		// �ړ���̏���
		AfterMoveProcess();
	}


	// �A�j���[�V�����t���[���̍X�V
	aniFrame++;


#ifndef _DEBUG

	// �����[�X���̂݃A�j���[�V����
	switch (aniType)
	{
	case 0:

		break;

	case 1:
		aniModel->Update("Idle", aniFrame);
		break;

	case 2:
		aniModel->Update("Walking", aniFrame);
		break;

	case 3:
		aniModel->Update("Attack", aniFrame);
		break;

	case 4:
		aniModel->Update("Down", aniFrame);
		break;

	default:
		break;
	}

#endif


	// �Q�[���I�[�o�[�̏���
	if (hitPoint <= 0.0f)
	{
		// �Q�[���I�[�o�[��ʂ�
		dungeonMap->SetGameOver();
	}

	// �K�i�Ƃ̓����蔻��
	// �����ۂ͓����蔻��ł͂Ȃ��}�b�v�f�[�^��������擾���Đ��䂷��
	Stair* stair = scene->GetGameObject<Stair>(OBJECT3D_LAYER);
	// ������͈͂��v�Z
	D3DXVECTOR3 direction = position - stair->GetPosition();
	float length = D3DXVec3Length(&direction);
	if (length < 0.5f)
	{
		// �Q�[���N���A��ʂ�
		dungeonMap->SetGameClear();
	}

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
void DungeonPlayer::Draw()
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
	aniModel->Draw();
}



//!-----------------------------------------------------------
//! @fn      : SetMoveVector(int type)
//! @brief   : �ړ������̃Z�b�g
//! @param   : type...�ړ������������̃^�C�v
//! @return  : �Ȃ�
//! @details : �ړ������������̐ݒ�̎���
//!            type ��0�Ȃ�O�A1�Ȃ���
//!            2�Ȃ�E�A3�Ȃ獶
//!            4�Ȃ�E�O�A5�Ȃ獶�O
//!            6�Ȃ�E��A7�Ȃ獶������ɐݒ�
//!-----------------------------------------------------------
void DungeonPlayer::SetMoveVector(int type)
{
	// �ړ����Ȃ�return
	if (isMove)
	{
		return;
	}

	// �O
	xPreMapNumber = xMapNumber;
	zPreMapNumber = zMapNumber;


	switch (type)
	{
		// �O�ړ�
	case 0:
		if(zMapNumber < DUNGEON_MAP_DATA_Z - 1)
		{
			zMapNumber--;
			rotation = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
		}
		break;

		// ��ړ�
	case 1:
		if (zMapNumber > 0)
		{
			zMapNumber++;
			rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		break;

		// �E�ړ�
	case 2:
		if (xMapNumber < DUNGEON_MAP_DATA_X - 1)
		{
			xMapNumber++;
			rotation = D3DXVECTOR3(0.0f, 4.71f, 0.0f);
		}
		break;

		// ���ړ�
	case 3:
		if (xMapNumber > 0)
		{
			xMapNumber--;
			rotation = D3DXVECTOR3(0.0f, 1.57f, 0.0f);
		}
		break;

		// �E�O�ړ�
	case 4:
		if (xMapNumber < DUNGEON_MAP_DATA_X - 1 && zMapNumber < DUNGEON_MAP_DATA_Z - 1)
		{
			xMapNumber++;
			zMapNumber--;
			rotation = D3DXVECTOR3(0.0f, 3.925f, 0.0f);
		}
		break;

		// ���O�ړ�
	case 5:
		if (xMapNumber > 0 && zMapNumber < DUNGEON_MAP_DATA_Z - 1)
		{
			xMapNumber--;
			zMapNumber--;
			rotation = D3DXVECTOR3(0.0f, 2.355f, 0.0f);
		}
		break;

		// �E��ړ�
	case 6:
		if (xMapNumber < DUNGEON_MAP_DATA_X - 1 && zMapNumber > 0)
		{
			xMapNumber++;
			zMapNumber++;
			rotation = D3DXVECTOR3(0.0f, 5.495f, 0.0f);
		}
		break;

		// ����ړ�
	case 7:
		if (xMapNumber > 0 && zMapNumber > 0)
		{
			xMapNumber--;
			zMapNumber++;
			rotation = D3DXVECTOR3(0.0f, 0.785f, 0.0f);
		}
		break;

	default:
		break;
	}

	// �i�݂����}�X���ǂȂ�return
	if (!dungeonMap->IsMapDataMove(xMapNumber, zMapNumber))
	{
		xMapNumber = xPreMapNumber;
		zMapNumber = zPreMapNumber;
		return;
	}

	// �ϐ��̒���
	move = (dungeonMap->GetCenterPosition(xMapNumber, zMapNumber) - dungeonMap->GetCenterPosition(xPreMapNumber, zPreMapNumber)) / moveFrameMax;
	aniType = 2;
	isMove = true;

}


//!-----------------------------------------------------------
//! @fn      : GetHitPoint()
//! @brief   : �v���C���[�̃q�b�g�|�C���g���擾����
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : 
//!-----------------------------------------------------------
float DungeonPlayer::GetHitPoint()
{
	return hitPoint;
}


//!-----------------------------------------------------------
//! @fn      : AfterMoveProcess()
//! @brief   : ���̃}�X�ֈړ�������̏���
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : 
//!-----------------------------------------------------------
void DungeonPlayer::AfterMoveProcess()
{
	// �ړ��Ɏg�p�����ϐ��̃��Z�b�g
	isMove = false;
	moveFrame = 0;

	// �v���C���[�̍��W���}�b�v�̍��W�ɍ��킹�Ē���
	position = dungeonMap->GetCenterPosition(xMapNumber, zMapNumber);

	// �O���W�̕ۑ�
	prePosition = position;

	// �v���C���[�̃q�b�g�|�C���g�����炷
	hitPoint -= 0.5f;

	// �G�l�~�[���̍X�V
	enemysList = scene->GetGameObjects<DungeonEnemy>(OBJECT3D_LAYER);

	for (DungeonEnemy* enemy : enemysList)
	{
		std::srand((unsigned int)time(NULL));
		int enemyNum = rand() % 8;

		enemy->SetMoveVector(enemyNum);
	}
}
