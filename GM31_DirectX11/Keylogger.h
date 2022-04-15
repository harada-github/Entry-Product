//!============================================================
//!
//!  @file    : Keylogger.h
//!  @brief   : キー入力の記録制御
//!  @author  : 原田 陽央
//!
//!============================================================
#ifndef KEYLOGGER_H_
#define KEYLOGGER_H_


// キーロガーキー列挙型
// 使うキーの役目で名前をいれる
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


// キー入力の初期化
void Keylogger_Initialize(void);

// キー入力の更新
void Keylogger_Update(void);

// キー入力の終了
void Keylogger_Finalize(void);


// キー入力状態の取得
//  引数 ：
// 戻り値：押されていたら true
bool Keylogger_Press(KeyloggerKey kl);

// キー入力状態の取得（押した瞬間）
//  引数 ：
// 戻り値：押した瞬間だったら true
bool Keylogger_Trigger(KeyloggerKey kl);

// キー入力状態の取得（離した瞬間）
//  引数 ：
// 戻り値：離したら true
bool Keylogger_Release(KeyloggerKey kl);


void Keylogger_RecordStart(int frame_max);
void Keylogger_RecordEnd(void);
void Keylogger_RecordLoad(void);
void Keylogger_RecordPlay(void);
bool Keylogger_IsRecordPlay(void);


#endif // KEYLOGGER_H_
