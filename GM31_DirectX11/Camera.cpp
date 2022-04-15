//!============================================================
//!
//!  @file    : Camera.cpp
//!  @brief   : �J�����N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �J�����̎���
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
#include "Keylogger.h"
#include "GameScene.h"
#include "Model.h"
#include "DungeonPlayer.h"
#include "Camera.h"


//============================================================
//�@�֐�
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : ������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������ƃx�N�g���̐��K��
//!-----------------------------------------------------------
void Camera::Init()
{
	// �ϐ��̏�����
	position      = D3DXVECTOR3(0.0f, 10.0f, -13.0f);
	vecFront      = D3DXVECTOR3(0.0f, -0.5f,   1.0f);
	vecSide       = D3DXVECTOR3(1.0f,  0.0f,   0.0f);
	vecUp         = D3DXVECTOR3(0.0f,  1.0f,   0.0f);
	target        = D3DXVECTOR3(0.0f,  0.0f,   0.0f);
	vecTemp       = D3DXVECTOR3(0.0f,  0.0f,   0.0f);
	vecPlayerView = D3DXVECTOR3(0.0f, 8.0f, -5.0f);

	player = nullptr;

	moveSpeed   = 0.3f;
	rotateSpeed = 0.02f;

	rotateAt = false;

	cameraType = CAMERA_Dungeon_PLAYER;

	// �O�����x�N�g���ƉE�����x�N�g���ƒ��p�ɂȂ������x�N�g�����Z�o
	D3DXVec3Cross(&vecUp, &vecFront, &vecSide);

	// �e�x�N�g���𐳋K���i�����P�Ɂj����
	D3DXVec3Normalize(&vecFront, &vecFront);
	D3DXVec3Normalize(&vecSide, &vecSide);
	D3DXVec3Normalize(&vecUp, &vecUp);

	D3DXMatrixIdentity(&viewMatrix);

	// �J�����̏����ʒu���Ȃ���
	target = position + vecFront;
	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &vecUp);
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : �I������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void Camera::Uninit()
{

}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �L�[���͂ɂ��J�����̃^�C�v�̕ύX
//!            �L�[���͂ɂ��J�����̈ړ�
//!            �^�C�v�ɂ���Ď����̕ύX
//!-----------------------------------------------------------
void Camera::Update()
{
#ifdef _DEBUG
	// �f�o�b�O���J�����̃^�C�v��ύX�\
	// �J�����̃^�C�v��ω�
	if (Keylogger_Trigger(KL_0))
	{
		cameraType = CAMERA_DEBUG;
	}
	else if (Keylogger_Trigger(KL_1))
	{
		cameraType = CAMERA_FIXED;
	}
	else if (Keylogger_Trigger(KL_2))
	{
		cameraType = CAMERA_PLAYER;
	}
	else if (Keylogger_Trigger(KL_3))
	{
		cameraType = CAMERA_Dungeon_PLAYER;
	}

#endif

	switch (cameraType)
	{
	case CAMERA_DEBUG:
	// CAMERA_DEBUG���̃J��������
	    // �O
		if (Keylogger_Press(KL_W))
		{
			CameraKeyInput(KL_W);
		}
		// ���
		if (Keylogger_Press(KL_S))
		{
			CameraKeyInput(KL_S);
		}
		// �E
		if (Keylogger_Press(KL_D))
		{
			CameraKeyInput(KL_D);
		}
		// ��
		if (Keylogger_Press(KL_A))
		{
			CameraKeyInput(KL_A);
		}
		// ��
		if (Keylogger_Press(KL_E))
		{
			CameraKeyInput(KL_E);
		}
		// ��
		if (Keylogger_Press(KL_Q))
		{
			CameraKeyInput(KL_Q);
		}
		// �E��]
		if (Keylogger_Press(KL_TURN_RIGHT))
		{
			CameraKeyInput(KL_TURN_RIGHT);
		}
		// ����]
		if (Keylogger_Press(KL_TURN_LEFT))
		{
			CameraKeyInput(KL_TURN_LEFT);
		}
		// �����_��]�I���I�t
		if (Keylogger_Press(KL_LEFTSHIFT))
		{
			rotateAt = true;
		}
		else
		{
			rotateAt = false;
		}

		// �����_���Z�o����
		target = position + vecFront;

		// �r���[�s��̍쐬
		D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &vecUp);

		break;


	case CAMERA_FIXED:
		// CAMERA_FIXED���̃J��������
		// �ϐ��̏�����
		position = D3DXVECTOR3(0.0f, 80.0f, 0.0f);

		// �����_�̐ݒ�
		target   = D3DXVECTOR3(0.0f,  0.0f, 0.0f);

		// �r���[�s��̍쐬
		D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &vecUp);

		break;


	case CAMERA_PLAYER:
	   
		break;

	case CAMERA_Dungeon_PLAYER:
		// CAMERA_Dungeon_PLAYER���̃J��������
		player = Manager::GetScene()->GetGameObject<DungeonPlayer>(OBJECT3D_LAYER);
		target = player->GetPosition();

		// �����_����|�W�V�������Z�o
		position = target + vecPlayerView;

		// �r���[�s��̍쐬
		D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		break;

	default:
		break;
	}
}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : �`�������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �r���[�}�g���N�X�ݒ�
//!            �v���W�F�N�V�����}�g���N�X�ݒ�
//!            �j�A�ƃt�@�[�̒l�̐ݒ�
//!-----------------------------------------------------------
void Camera::Draw()
{
	// �r���[�}�g���N�X�ݒ�
	Renderer::SetViewMatrix(&viewMatrix);

	// �Ō��̓j�A�ƃt�@�[�̒l
	if (cameraType == CAMERA_Dungeon_PLAYER)
	{
		D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 500.0f);
	}
	else
	{
		D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
	}
	
	Renderer::SetProjectionMatrix(&projectionMatrix);

}


//!-----------------------------------------------------------
//! @fn      : Camera_GetViewMatrix()
//! @brief   : �J�����̃r���[�s��̎擾
//! @param   : �Ȃ�
//! @return  : �J�����̃r���[�s��
//! @details : �J�����̃r���[�s���Ԃ�
//!-----------------------------------------------------------
D3DXMATRIX Camera::Camera_GetViewMatrix() const
{
	return viewMatrix;
}


//!-----------------------------------------------------------
//! @fn      : CheckView(D3DXVECTOR3 objectPosition)
//! @brief   : ������J�����O�̎���
//! @param   : objectPosition...�`�F�b�N�������I�u�W�F�N�g�̍��W
//! @return  : �ݒ肵��������͈͓̔��ɃI�u�W�F�N�g�����邩�ǂ���
//! @details : �ϐ��Ɏw�肵���I�u�W�F�N�g���W��
//!            ������͈͓̔��ɂ��邩���`�F�b�N����
//!            ���݂���ꍇ�ɂ� true ��Ԃ�
//!-----------------------------------------------------------
bool Camera::CheckView(D3DXVECTOR3 objectPosition)
{
	// �ϐ���p��
	D3DXMATRIX vp, invvp;
	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];
	D3DXVECTOR3 v, v1, v2, n[4];

	vp = viewMatrix * projectionMatrix;

	D3DXMatrixInverse(&invvp, NULL, &vp);

	// ������̉��̒��_�𐶐�
	if (cameraType == CAMERA_Dungeon_PLAYER)
	{
		vpos[0] = D3DXVECTOR3(-1.2f,  1.2f, 1.0f);
		vpos[1] = D3DXVECTOR3( 1.2f,  1.2f, 1.0f);
		vpos[2] = D3DXVECTOR3( 1.2f, -1.3f, 1.0f);
		vpos[3] = D3DXVECTOR3(-1.2f, -1.3f, 1.0f);
	}
	else
	{
		vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
		vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		vpos[2] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
		vpos[3] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	}
	

	// �ϊ�
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&wpos[i], &vpos[i], &invvp);
	}

	// �Ώۂ̃I�u�W�F�N�g�ƃJ�����̃|�W�V�����̍�����ۑ�
	v = objectPosition - position;

	// ����̌v�Z ������̊O�̏ꍇ��false��Ԃ�
	for (int i = 0; i < 4; i++)
	{
		// ������̏�̖ʂ̏�񂩂� n �̔z��Ɋi�[���Ă���
		if (i == 3)
		{
			// i ���R�̂Ƃ��݂̂̏���
			v1 = wpos[0] - position;
		}
		else
		{
			v1 = wpos[i + 1] - position;
		}

		v2 = wpos[i] - position;

		// �O�ς��v�Z
		D3DXVec3Cross(&n[i], &v1, &v2);

		// ���ʂ̕������}�C�i�X�̏ꍇ��false��Ԃ�
		if (D3DXVec3Dot(&n[i], &v) < 0.0f)
		{
			return false;
		}
	}

	return true;
}


//!-----------------------------------------------------------
//! @fn      : CheckOnlyCameraMove()
//! @brief   : �J�����݂̂����ł���J�����^�C�v���ǂ����̃`�F�b�N
//! @param   : �Ȃ�
//! @return  : �J�����݂̂����ł����Ԃ��ǂ���
//! @details : �J�����݂̂����ł���J�����^�C�v���ǂ�����
//!            �`�F�b�N���Ă��̉ۂ�Ԃ�
//!            �J�����݂̂�������^�C�v�̏ꍇ�� true
//!            �J�����������Ȃ��^�C�v�̏ꍇ�́@ false
//!-----------------------------------------------------------
bool Camera::CheckOnlyCameraMove()
{
	if (cameraType == CAMERA_DEBUG)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//!-----------------------------------------------------------
//! @fn      : CameraKeyInput(KeyloggerKey keyType)
//! @brief   : �L�[���͂̍ۂ̃J��������
//! @param   : keyType...���͂��ꂽ�L�[�̃^�C�v
//! @return  : �Ȃ�
//! @details : �O�㍶�E�㉺�̈ړ��Ɖ�]�̎���
//!            �����ꂽ�L�[�ɑ΂��Ă̈ړ����]���s��
//!-----------------------------------------------------------
void Camera::CameraKeyInput(KeyloggerKey keyType)
{
	//if (cameraType != CAMERA_DEBUG) return;

	// W�܂���S�������ꂽ�Ƃ��i�O��j
	if (keyType == KL_W || keyType == KL_S)
	{
		// �ړ������ȊO���O�ɂ��Đ��K��
		vecTemp = vecFront;
		vecTemp.y = 0.0f;
		D3DXVec3Normalize(&vecTemp, &vecTemp);

		// ���W�X�V
		keyType == KL_W ?  position += (vecTemp * moveSpeed) : position -= (vecTemp * moveSpeed);
	}

	// D�܂���A�������ꂽ�Ƃ��i���E�j
	if (keyType == KL_D || keyType == KL_A)
	{
		// �ړ������ȊO���O�ɂ��Đ��K��
		vecTemp = vecSide;
		D3DXVec3Normalize(&vecTemp, &vecTemp);

		// ���W�X�V
		keyType == KL_D ? position += (vecTemp * moveSpeed) : position -= (vecTemp * moveSpeed);
	}

	// E�܂���Q�������ꂽ�Ƃ��i�㉺�j
	if (keyType == KL_E || keyType == KL_Q)
	{
		// �ړ������ȊO���O�ɂ��Đ��K��
		vecTemp = vecUp;
		vecTemp.x = 0.0f;
		vecTemp.z = 0.0f;
		D3DXVec3Normalize(&vecTemp, &vecTemp);

		// ���W�X�V
		keyType == KL_E ? position += (vecTemp * moveSpeed) : position -= (vecTemp * moveSpeed);
	}

	// ���܂��́��������ꂽ�Ƃ��i��]�j
	if (keyType == KL_TURN_RIGHT || keyType == KL_TURN_LEFT)
	{
		// �E�ƍ��ŕω�
		keyType == KL_TURN_RIGHT ? D3DXMatrixRotationY(&mtxTempR, rotateSpeed) : D3DXMatrixRotationY(&mtxTempR, -rotateSpeed);

		// ���ꂼ��̃x�N�g������]
		D3DXVec3TransformNormal(&vecFront, &vecFront, &mtxTempR);
		D3DXVec3TransformNormal(&vecSide, &vecSide, &mtxTempR);
		D3DXVec3TransformNormal(&vecUp, &vecUp, &mtxTempR);

	}
}
