//!============================================================
//!
//!  @file    : ResultOverScene.cpp
//!  @brief   : ���U���g�I�[�o�[�V�[���N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �Q�[���I�[�o�[��ʂ̐ݒ�͂����ōs��
//!
//!============================================================
#pragma once
#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "Keylogger.h"
#include "GameObject.h"
#include "Resource.h"
#include "ResultOverBG.h"
#include "Fade.h"
#include "ResultOverScene.h"
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
void ResultOverScene::Init()
{
	AddGameObject<ResultOverBG>(OBJECT2D_LAYER);
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
void ResultOverScene::Uninit()
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
void ResultOverScene::Update()
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

