//!============================================================
//!
//!  @file    : ResultClearScene.cpp
//!  @brief   : ���U���g�N���A�V�[���N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �Q�[���N���A��ʂ̐ݒ�͂����ōs��
//!
//!============================================================
#pragma once


//============================================================
//�@�C���N���[�h
//============================================================
#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "Keylogger.h"
#include "GameObject.h"
#include "Resource.h"
#include "ResultClearBG.h"
#include "Fade.h"
#include "ResultClearScene.h"
#include "TitleScene.h"


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
void ResultClearScene::Init()
{
	AddGameObject<ResultClearBG>(OBJECT2D_LAYER);
	AddGameObject<Fade>(OBJECT2D_LAYER);

	// �t�F�[�h�̃Z�b�g
	Fade::SetFade(1);

	// �ϐ�������
	isFade = false;
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : �I������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �V�[���̏I�������Ȃ�
//!-----------------------------------------------------------
void ResultClearScene::Uninit()
{
	// �p�����̃��\�b�h�̌Ăяo��
	Scene::Uninit();
}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �V�[���̍X�V��L�[���͂Ȃ�
//!-----------------------------------------------------------
void ResultClearScene::Update()
{
	// �p�����̃��\�b�h�̌Ăяo��
	Scene::Update();

	// �L�[����
	if (Keylogger_Trigger(KL_SPACE) && !isFade)
	{
		// �t�F�[�h�Z�b�g
		isFade = true;
		Fade::SetFade(2);
	}

	// �t�F�[�h������������V�[���J��
	if (isFade && Fade::GetFadeType() == 0)
	{
		Manager::SetScene<TitleScene>();
	}
}

