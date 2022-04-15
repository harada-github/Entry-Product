//!============================================================
//!
//!  @file    : TitleScene.cpp
//!  @brief   : �^�C�g���V�[���N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �^�C�g����ʂ̍\���͂��ׂĂ����ōs��
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
#include "Polygon2D.h"
#include "Fade.h"
#include "TitleBG.h"
#include "TitleName.h"
#include "TitlePress.h"
#include "TitleScene.h"
#include "GameScene.h"


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
void TitleScene::Init()
{
	AddGameObject<TitleBG>(OBJECT2D_LAYER);
	AddGameObject<TitleName>(OBJECT2D_LAYER);
	AddGameObject<TitlePress>(OBJECT2D_LAYER);
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
void TitleScene::Uninit()
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
void TitleScene::Update()
{
	// �p�����̃��\�b�h�̌Ăяo��
	Scene::Update();

	// �L�[����
	if (Keylogger_Trigger(KL_ENTER) && !isFade)
	{
		// �t�F�[�h�Z�b�g
		isFade = true;
		Fade::SetFade(2);
	}

	// �t�F�[�h������������V�[���J��
	if (isFade && Fade::GetFadeType() == 0)
	{
		Manager::SetScene<GameScene>();
	}
}
