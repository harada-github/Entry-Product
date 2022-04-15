//!============================================================
//!
//!  @file    : GameScene.cpp
//!  @brief   : �Q�[���V�[���N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �Q�[���̑�܂��Ȃ��̂͂����ōs��
//!
//!============================================================
#pragma once


//============================================================
//�@�C���N���[�h
//============================================================
#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Resource.h"
#include "Camera.h"
#include "Audio.h"
#include "DungeonField.h"
#include "DungeonMap.h"
#include "Model.h"
#include "Sky.h"
#include "Fade.h"
#include "GameScene.h"
#include "ResultClearScene.h"
#include "ResultOverScene.h"
#include "StaminaBar.h"
#include "HitPointBar.h"
#include "DungeonPlayer.h"
#include "DungeonEnemy.h"


//============================================================
//�@�ϐ��錾
//============================================================
static Audio* bgm;
bool GameScene::isFade;
int GameScene::resultType;


//============================================================
//�@�֐�
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : ������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �I�u�W�F�N�g�̔z�u�Ȃǂ͂����ōs��
//!-----------------------------------------------------------
void GameScene::Init()
{
	// �ϐ�������
	isFade = false;
	resultType = 0;

	// �I�u�W�F�N�g�̔z�u
	// �_���W�����}�b�v
	AddGameObject<DungeonMap>(OBJECT3D_LAYER);
	AddGameObject<Camera>(CAMERA_LAYER);
	AddGameObject<HitPointBar>(OBJECT2D_LAYER)->SetBarType(0);
	AddGameObject<HitPointBar>(OBJECT2D_LAYER)->SetBarType(1);
	AddGameObject<StaminaBar>(OBJECT2D_LAYER)->SetBarType(0);
	AddGameObject<StaminaBar>(OBJECT2D_LAYER)->SetBarType(1);
	AddGameObject<DungeonField>(OBJECT3D_LAYER);
	AddGameObject<DungeonPlayer>(OBJECT3D_LAYER);

	AddGameObject<DungeonEnemy>(OBJECT3D_LAYER);
	AddGameObject<DungeonEnemy>(OBJECT3D_LAYER);
	AddGameObject<DungeonEnemy>(OBJECT3D_LAYER);
	AddGameObject<DungeonEnemy>(OBJECT3D_LAYER);
	AddGameObject<DungeonEnemy>(OBJECT3D_LAYER);
	
	AddGameObject<Sky>(NO_ZSORT_OBJECT_LAYER);
	AddGameObject<Fade>(OBJECT2D_LAYER);


	// BGM�̃��[�h
	bgm = Resource::ResourceAudioLoad("Asset\\Sound\\gm.wav");

	// BGM�̍Đ�
	bgm->Play(true);

	// �t�F�[�h�̃Z�b�g
	Fade::SetFade(1);
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : �I������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �V�[���̏I�������Ȃ�
//!-----------------------------------------------------------
void GameScene::Uninit()
{
	bgm->Stop();

	Scene::Uninit();
}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �V�[���̍X�V��L�[���͂Ȃ�
//!-----------------------------------------------------------
void GameScene::Update()
{
	Scene::Update();

	// �t�F�[�h������������V�[���J��
	if (isFade && Fade::GetFadeType() == 0)
	{
		if (resultType == 0)
		{
			Manager::SetScene<ResultClearScene>();
		}
		else if (resultType == 1)
		{
			Manager::SetScene<ResultOverScene>();
		}
	}
}


//!-----------------------------------------------------------
//! @fn      : SetResult(int type)
//! @brief   : ���U���g�V�[���̈ړ��Z�b�g
//! @param   : type...���U���g�̃^�C�v
//!            0�Ȃ�Q�[���N���A��� 1�Ȃ�Q�[���I�[�o�[���
//! @return  : �Ȃ�
//! @details : ���U���g�^�C�v��t�F�[�h�̐ݒ������
//!            Game::SetResult(0)�̂悤�Ɏg�p����
//!-----------------------------------------------------------
void GameScene::SetResult(int type)
{
	// �t�F�[�h���Ȃ�return
	if (isFade)return;

	// ���U���g�̃^�C�v��ݒ�
	resultType = type;

	// �t�F�[�h�I��
	isFade = true;
	Fade::SetFade(2);
}
