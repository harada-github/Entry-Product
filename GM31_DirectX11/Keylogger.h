//!============================================================
//!
//!  @file    : Keylogger.h
//!  @brief   : �L�[���͂̋L�^����
//!  @author  : ���c �z��
//!
//!============================================================
#ifndef KEYLOGGER_H_
#define KEYLOGGER_H_


// �L�[���K�[�L�[�񋓌^
// �g���L�[�̖�ڂŖ��O�������
typedef enum KeyloggerKey_tag
{
	KL_W,
	KL_S,
	KL_A,
	KL_D,
	KL_E,
	KL_Q,
	KL_SPACE,
	KL_ENTER,
	KL_TURN_LEFT,
	KL_TURN_RIGHT,
	KL_LEFTSHIFT,
	KL_0, // CAMERA_DEBUG
	KL_1, // CAMERA_FIXED
	KL_2, // CAMERA_PLAYER
	KL_3, // CAMERA_Dungeon_PLAYER
	KL_L,
	KL_MAX
}KeyloggerKey;


// �L�[���͂̏�����
void Keylogger_Initialize(void);

// �L�[���͂̍X�V
void Keylogger_Update(void);

// �L�[���͂̏I��
void Keylogger_Finalize(void);


// �L�[���͏�Ԃ̎擾
//  ���� �F
// �߂�l�F������Ă����� true
bool Keylogger_Press(KeyloggerKey kl);

// �L�[���͏�Ԃ̎擾�i�������u�ԁj
//  ���� �F
// �߂�l�F�������u�Ԃ������� true
bool Keylogger_Trigger(KeyloggerKey kl);

// �L�[���͏�Ԃ̎擾�i�������u�ԁj
//  ���� �F
// �߂�l�F�������� true
bool Keylogger_Release(KeyloggerKey kl);


void Keylogger_RecordStart(int frame_max);
void Keylogger_RecordEnd(void);
void Keylogger_RecordLoad(void);
void Keylogger_RecordPlay(void);
bool Keylogger_IsRecordPlay(void);


#endif // KEYLOGGER_H_
