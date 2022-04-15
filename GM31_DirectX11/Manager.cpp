//!============================================================
//!
//!  @file    : Manager.cpp
//!  @brief   : �}�l�[�W���[�N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �}�l�[�W���[�N���X�̎���
//!             �V�[���̊Ǘ�
//!             �Q�[���̑�܂��ȊǗ����s��
//!
//!============================================================
#pragma once
#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "Resource.h"
#include "Keyboard.h"
#include "Keylogger.h"
#include "Audio.h"
#include "Scene.h"
#include "GameScene.h"
#include "TitleScene.h"



//============================================================
//�@�ϐ��錾
//============================================================
Scene* Manager::scene = NULL;


//============================================================
//�@�֐�
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : ������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : ����������
//!-----------------------------------------------------------
void Manager::Init()
{
	// �����_���[�̏�����
	Renderer::Init();

	// �L�[�{�[�h�̏�����
	Keyboard_Initialize();

	// �L�[���[�K�[�̏�����
	Keylogger_Initialize();

	// �I�[�f�B�I�̏�����
	Audio::InitMaster();

	// ���\�[�X�̏�����
	Resource::Init();

	// �V�[���̏�����
	scene = new TitleScene();
	scene->Init();
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : �I������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �I������
//!-----------------------------------------------------------
void Manager::Uninit()
{
	// �V�[���̏I��
	scene->Uninit();
	delete scene;

	// ���\�[�X�̏I��
	Resource::Uninit();

	// �I�[�f�B�I�̏I��
	Audio::UninitMaster();

	// �L�[���K�[�L�[�̏I������
	Keylogger_Finalize();

	// �����_���[�̏I��
	Renderer::Uninit();
}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �X�V����
//!-----------------------------------------------------------
void Manager::Update()
{
	// �L�[���K�[�L�[�̍X�V
	Keylogger_Update();

	// �V�[���̍X�V
	scene->Update();
}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : �`�������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �`�揈��
//!-----------------------------------------------------------
void Manager::Draw()
{
	Renderer::Begin();

	// �V�[���̕`��
	scene->Draw();

	Renderer::End();
}
