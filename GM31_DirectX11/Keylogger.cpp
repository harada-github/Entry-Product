//!============================================================
//!
//!  @file    : Keylogger.cpp
//!  @brief   : �L�[���͂̋L�^����
//!  @author  : ���c �z��
//!
//!============================================================
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Keylogger.h"
#include "Keyboard.h"


//============================================================
//�@�O���[�o���ϐ��錾
//============================================================
typedef unsigned long KeyloggerType;
static KeyloggerType g_CurrentKeyState = 0; // ���̃t���[���ł̃L�[�̏�ԕێ��p
static KeyloggerType g_PrevKeyState    = 0; // �O�̃t���[���ł̃L�[�̏�ԕێ��p
static KeyloggerType g_TriggerKeyState = 0; // �g���K�[��Ԃ̊m�F�p
static KeyloggerType g_ReleaseKeyState = 0; // �����[�X��Ԃ̊m�F�p

static int g_KeyloggerMode = 0; // 0 - �ʏ� 1 - �L�^ 2 - �Đ�
static KeyloggerType* g_pRecordCurrentData = NULL;
static int g_RecordFrame = 0;
static int g_RecordPlayFrame = 0;
static int g_RecordFrameMax = 0;

// �L�[���K�[�L�[����L�[�{�[�h�L�[�ւ̕ϊ��\
// �L�[���K�[�L�[��enum�ɑΉ�������̓L�[�������
static const Keyboard_Keys g_KKs[KL_MAX] =
{
	KK_W,     // �O
	KK_S,     // ��
	KK_A,     // ��
	KK_D,     // �E
	KK_E,     // ��
	KK_Q,     // ��
	KK_SPACE, // �V�[���ړ�
	KK_ENTER, // �G���^�[�L�[
	KK_LEFT,  // ����]
	KK_RIGHT, // �E��]
	KK_LEFTSHIFT, // �����_��]�p
	KK_D0,    // �J�����̃^�C�v�ω�
	KK_D1,    // �J�����̃^�C�v�ω�
	KK_D2,    // �J�����̃^�C�v�ω�
	KK_D3,    // �J�����̃^�C�v�ω�
	KK_L,     // �e����
};


//============================================================
//�@�֐�
//============================================================
//------------------------------------------------------------
// �L�[���͂̏�����
//------------------------------------------------------------
void Keylogger_Initialize(void)
{
	g_CurrentKeyState = 0;
	g_PrevKeyState = 0;
	g_TriggerKeyState = 0;
	g_ReleaseKeyState = 0;

	g_KeyloggerMode = 0;
	g_pRecordCurrentData = NULL;
	g_RecordFrame = 0;
	g_RecordPlayFrame = 0;
	g_RecordFrameMax = 0;
}


//------------------------------------------------------------
// �L�[���͂̍X�V
//------------------------------------------------------------
void Keylogger_Update(void)
{
	// �O�t���[���̃L�[��Ԃ�ۑ����Ă���
	g_PrevKeyState = g_CurrentKeyState;

	// �L�[���K�[���[�h�ɂ���ē���ύX
	if (g_KeyloggerMode <= 1)
	{
		// �L�[���K�[�L�[��Ԏ擾
		g_CurrentKeyState = 0;
		for (int i = 0; i < KL_MAX; i++)
		{
			if (Keyboard_IsKeyDown(g_KKs[i]))
			{
				// i�̐����i�Q�i���Ƃ��āj�̃r�b�g�̂������������ɃV�t�g
				g_CurrentKeyState |= 1u << i;
			}
		}

		// �L�[�L�^���[�h
		if (g_KeyloggerMode == 1)
		{
			if (g_RecordPlayFrame < g_RecordFrameMax)
			{
				g_pRecordCurrentData[g_RecordFrame++] = g_CurrentKeyState;
			}
		}
	}
	else
	{
		// �Đ����[�h
		// ���S���u�i�L�^�t���[�������������Đ����悤�Ƃ����j
		if (g_RecordPlayFrame < g_RecordFrame)
		{
			g_CurrentKeyState = g_pRecordCurrentData[g_RecordPlayFrame++];
		}
		else
		{
			g_CurrentKeyState = 0;
			g_KeyloggerMode = 0; // 0�c�ʏ탂�[�h�ɂ���
		}

		// ��L��if���A�܂��́�
		//g_CurrentKeyState = g_RecordPlayFrame < g_RecordFrame ? g_pRecordCurrentData[g_RecordPlayFrame++] : 0;
	}

	// �������u�ԂƗ������u�Ԃ̃L�[���擾
	g_TriggerKeyState = (g_PrevKeyState ^ g_CurrentKeyState) & g_CurrentKeyState;
	g_ReleaseKeyState = (g_PrevKeyState ^ g_CurrentKeyState) & g_PrevKeyState;
}


//------------------------------------------------------------
// �L�[���͂̏I��
//------------------------------------------------------------
void Keylogger_Finalize(void)
{
	if (g_pRecordCurrentData)
	{
		free(g_pRecordCurrentData);
		g_pRecordCurrentData = NULL;
	}
}


//------------------------------------------------------------
// �L�[���͏�Ԃ̎擾
//  ���� �F
// �߂�l�F������Ă����� true
//------------------------------------------------------------
bool Keylogger_Press(KeyloggerKey kl)
{
	// �O����false��������
	return g_CurrentKeyState & (1u << kl);
}


//------------------------------------------------------------
// �L�[���͏�Ԃ̎擾�i�������u�ԁj
//  ���� �F
// �߂�l�F�������u�Ԃ������� true
//------------------------------------------------------------
bool Keylogger_Trigger(KeyloggerKey kl)
{
	return g_TriggerKeyState & (1u << kl);
}


//------------------------------------------------------------
// �L�[���͏�Ԃ̎擾�i�������u�ԁj
//  ���� �F
// �߂�l�F�������� true
//------------------------------------------------------------
bool Keylogger_Release(KeyloggerKey kl)
{
	return g_ReleaseKeyState & (1u << kl);
}


//------------------------------------------------------------
// �L�[���͂̋L�^�X�^�[�g
//------------------------------------------------------------
void Keylogger_RecordStart(int frame_max)
{
	if (g_pRecordCurrentData)
	{
		free(g_pRecordCurrentData);
	}

	g_pRecordCurrentData = (KeyloggerType*)malloc(sizeof(KeyloggerType) * frame_max);
	g_KeyloggerMode = 1; // 1�c�L�^���[�h
	g_RecordFrame = 0;
	g_RecordFrameMax = frame_max;
}


//------------------------------------------------------------
// �L�[���͂̋L�^�I��
//------------------------------------------------------------
void Keylogger_RecordEnd(void)
{
	if (!g_pRecordCurrentData)
	{
		return;
	}

	FILE* fp = fopen("keylogger.dat", "wb");
	// �t�@�C���̐擪�Ƀf�[�^�ʂ��L�^
	fwrite(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);
	// �t�@�C���փf�[�^��ۑ�
	fwrite(g_pRecordCurrentData, sizeof(KeyloggerType), g_RecordFrame, fp);
	fclose(fp);

	g_KeyloggerMode = 0; // �ʏ탂�[�h

	if (g_pRecordCurrentData)
	{
		free(g_pRecordCurrentData);
		g_pRecordCurrentData = NULL;
	}
}


//------------------------------------------------------------
// �L�[���͂̋L�^�̓ǂݍ���
//------------------------------------------------------------
void Keylogger_RecordLoad(void)
{
	FILE* fp = fopen("keylogger.dat", "rb");
	fread(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);

	if (g_pRecordCurrentData)
	{
		free(g_pRecordCurrentData);
	}
	g_pRecordCurrentData = (KeyloggerType*)malloc(sizeof(KeyloggerType) * g_RecordFrame);

	fread(g_pRecordCurrentData, sizeof(KeyloggerType), g_RecordFrame, fp);
	fclose(fp);
}


//------------------------------------------------------------
// �L�[���͂̋L�^�̍Đ�
//------------------------------------------------------------
void Keylogger_RecordPlay(void)
{
	g_RecordPlayFrame = 0;
	g_KeyloggerMode = 2; // 2�c�Đ����[�h
}


//------------------------------------------------------------
// �L�[���͂̋L�^���Đ������ǂ���
//------------------------------------------------------------
bool Keylogger_IsRecordPlay(void)
{
	if (g_KeyloggerMode == 2)
	{
		return true;
	}

	return false;
}
