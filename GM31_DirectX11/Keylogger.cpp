//!============================================================
//!
//!  @file    : Keylogger.cpp
//!  @brief   : キー入力の記録制御
//!  @author  : 原田 陽央
//!
//!============================================================
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Keylogger.h"
#include "Keyboard.h"


//============================================================
//　グローバル変数宣言
//============================================================
typedef unsigned long KeyloggerType;
static KeyloggerType g_CurrentKeyState = 0; // そのフレームでのキーの状態保持用
static KeyloggerType g_PrevKeyState    = 0; // 前のフレームでのキーの状態保持用
static KeyloggerType g_TriggerKeyState = 0; // トリガー状態の確認用
static KeyloggerType g_ReleaseKeyState = 0; // リリース状態の確認用

static int g_KeyloggerMode = 0; // 0 - 通常 1 - 記録 2 - 再生
static KeyloggerType* g_pRecordCurrentData = NULL;
static int g_RecordFrame = 0;
static int g_RecordPlayFrame = 0;
static int g_RecordFrameMax = 0;

// キーロガーキーからキーボードキーへの変換表
// キーロガーキーのenumに対応する入力キーをいれる
static const Keyboard_Keys g_KKs[KL_MAX] =
{
	KK_W,     // 前
	KK_S,     // 後
	KK_A,     // 左
	KK_D,     // 右
	KK_E,     // 上
	KK_Q,     // 下
	KK_SPACE, // シーン移動
	KK_ENTER, // エンターキー
	KK_LEFT,  // 左回転
	KK_RIGHT, // 右回転
	KK_LEFTSHIFT, // 注視点回転用
	KK_D0,    // カメラのタイプ変化
	KK_D1,    // カメラのタイプ変化
	KK_D2,    // カメラのタイプ変化
	KK_D3,    // カメラのタイプ変化
	KK_L,     // 弾発射
};


//============================================================
//　関数
//============================================================
//------------------------------------------------------------
// キー入力の初期化
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
// キー入力の更新
//------------------------------------------------------------
void Keylogger_Update(void)
{
	// 前フレームのキー状態を保存しておく
	g_PrevKeyState = g_CurrentKeyState;

	// キーロガーモードによって動作変更
	if (g_KeyloggerMode <= 1)
	{
		// キーロガーキー状態取得
		g_CurrentKeyState = 0;
		for (int i = 0; i < KL_MAX; i++)
		{
			if (Keyboard_IsKeyDown(g_KKs[i]))
			{
				// iの数字（２進数として）のビットのおおきさ分左にシフト
				g_CurrentKeyState |= 1u << i;
			}
		}

		// キー記録モード
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
		// 再生モード
		// 安全処置（記録フレーム数よりも多く再生しようとした）
		if (g_RecordPlayFrame < g_RecordFrame)
		{
			g_CurrentKeyState = g_pRecordCurrentData[g_RecordPlayFrame++];
		}
		else
		{
			g_CurrentKeyState = 0;
			g_KeyloggerMode = 0; // 0…通常モードにする
		}

		// 上記のif文、または↓
		//g_CurrentKeyState = g_RecordPlayFrame < g_RecordFrame ? g_pRecordCurrentData[g_RecordPlayFrame++] : 0;
	}

	// 押した瞬間と離した瞬間のキーを取得
	g_TriggerKeyState = (g_PrevKeyState ^ g_CurrentKeyState) & g_CurrentKeyState;
	g_ReleaseKeyState = (g_PrevKeyState ^ g_CurrentKeyState) & g_PrevKeyState;
}


//------------------------------------------------------------
// キー入力の終了
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
// キー入力状態の取得
//  引数 ：
// 戻り値：押されていたら true
//------------------------------------------------------------
bool Keylogger_Press(KeyloggerKey kl)
{
	// ０だとfalseがかえる
	return g_CurrentKeyState & (1u << kl);
}


//------------------------------------------------------------
// キー入力状態の取得（押した瞬間）
//  引数 ：
// 戻り値：押した瞬間だったら true
//------------------------------------------------------------
bool Keylogger_Trigger(KeyloggerKey kl)
{
	return g_TriggerKeyState & (1u << kl);
}


//------------------------------------------------------------
// キー入力状態の取得（離した瞬間）
//  引数 ：
// 戻り値：離したら true
//------------------------------------------------------------
bool Keylogger_Release(KeyloggerKey kl)
{
	return g_ReleaseKeyState & (1u << kl);
}


//------------------------------------------------------------
// キー入力の記録スタート
//------------------------------------------------------------
void Keylogger_RecordStart(int frame_max)
{
	if (g_pRecordCurrentData)
	{
		free(g_pRecordCurrentData);
	}

	g_pRecordCurrentData = (KeyloggerType*)malloc(sizeof(KeyloggerType) * frame_max);
	g_KeyloggerMode = 1; // 1…記録モード
	g_RecordFrame = 0;
	g_RecordFrameMax = frame_max;
}


//------------------------------------------------------------
// キー入力の記録終了
//------------------------------------------------------------
void Keylogger_RecordEnd(void)
{
	if (!g_pRecordCurrentData)
	{
		return;
	}

	FILE* fp = fopen("keylogger.dat", "wb");
	// ファイルの先頭にデータ量を記録
	fwrite(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);
	// ファイルへデータを保存
	fwrite(g_pRecordCurrentData, sizeof(KeyloggerType), g_RecordFrame, fp);
	fclose(fp);

	g_KeyloggerMode = 0; // 通常モード

	if (g_pRecordCurrentData)
	{
		free(g_pRecordCurrentData);
		g_pRecordCurrentData = NULL;
	}
}


//------------------------------------------------------------
// キー入力の記録の読み込み
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
// キー入力の記録の再生
//------------------------------------------------------------
void Keylogger_RecordPlay(void)
{
	g_RecordPlayFrame = 0;
	g_KeyloggerMode = 2; // 2…再生モード
}


//------------------------------------------------------------
// キー入力の記録が再生中かどうか
//------------------------------------------------------------
bool Keylogger_IsRecordPlay(void)
{
	if (g_KeyloggerMode == 2)
	{
		return true;
	}

	return false;
}
