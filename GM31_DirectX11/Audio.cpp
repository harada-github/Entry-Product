//!============================================================
//!
//!  @file    : Audio.cpp
//!  @brief   : オーディオクラスのソースファイル
//!  @author  : 配布
//!  @details : オーディオ（サウンド）の簡易実装
//!
//!============================================================
#pragma once


//============================================================
//　インクルード
//============================================================
#include "Main.h"
#include "Audio.h"


//============================================================
//　変数宣言
//============================================================
IXAudio2*				Audio::audioXAudio = NULL;
IXAudio2MasteringVoice*	Audio::masteringVoice = NULL;


//============================================================
//　関数
//============================================================
//!-----------------------------------------------------------
//! @fn      : InitMaster()
//! @brief   : マスタの初期化をする
//! @param   : なし
//! @return  : なし
//! @details : COMの初期化
//!            XAudioの生成
//!            マスタリングボイスの生成
//!-----------------------------------------------------------
void Audio::InitMaster()
{
	// COM初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio生成
	XAudio2Create(&audioXAudio, 0);

	// マスタリングボイス生成
	audioXAudio->CreateMasteringVoice(&masteringVoice);
}


//!-----------------------------------------------------------
//! @fn      : UninitMaster()
//! @brief   : マスタの初期化をする
//! @param   : なし
//! @return  : なし
//! @details : マスタリングボイスの解放
//!            XAudioの解放
//!            COMの終了処理
//!-----------------------------------------------------------
void Audio::UninitMaster()
{
	// マスタリングボイスの解放
	masteringVoice->DestroyVoice();

	// XAudioの解放
	audioXAudio->Release();

	// COMの終了処理
	CoUninitialize();
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : 終了処理をする
//! @param   : なし
//! @return  : なし
//! @details : シーンの終了処理など
//!-----------------------------------------------------------
void Audio::Uninit()
{
	sourceVoice->Stop();
	sourceVoice->DestroyVoice();

	delete[] soundData;
}


//!-----------------------------------------------------------
//! @fn      : Load(const char *audioFileName)
//! @brief   : オーディオデータのロードをする
//! @param   : audioFileName...ロードしたいファイル名
//! @return  : なし
//! @details : サウンドデータの読み込み
//!            サウンドソースの生成
//!-----------------------------------------------------------
void Audio::Load(const char *audioFileName)
{

	// サウンドデータ読込
	WAVEFORMATEX wfx = { 0 };

	{
		HMMIO hmmio = NULL;
		MMIOINFO mmioinfo = { 0 };
		MMCKINFO riffchunkinfo = { 0 };
		MMCKINFO datachunkinfo = { 0 };
		MMCKINFO mmckinfo = { 0 };
		UINT32 buflen;
		LONG readlen;


		hmmio = mmioOpen((LPSTR)audioFileName, &mmioinfo, MMIO_READ);
		assert(hmmio);

		riffchunkinfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(hmmio, &riffchunkinfo, NULL, MMIO_FINDRIFF);

		mmckinfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(hmmio, &mmckinfo, &riffchunkinfo, MMIO_FINDCHUNK);

		if (mmckinfo.cksize >= sizeof(WAVEFORMATEX))
		{
			mmioRead(hmmio, (HPSTR)&wfx, sizeof(wfx));
		}
		else
		{
			PCMWAVEFORMAT pcmwf = { 0 };
			mmioRead(hmmio, (HPSTR)&pcmwf, sizeof(pcmwf));
			memset(&wfx, 0x00, sizeof(wfx));
			memcpy(&wfx, &pcmwf, sizeof(pcmwf));
			wfx.cbSize = 0;
		}
		mmioAscend(hmmio, &mmckinfo, 0);

		datachunkinfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(hmmio, &datachunkinfo, &riffchunkinfo, MMIO_FINDCHUNK);



		buflen = datachunkinfo.cksize;
		soundData = new unsigned char[buflen];
		readlen = mmioRead(hmmio, (HPSTR)soundData, buflen);


		length = readlen;
		playLength = readlen / wfx.nBlockAlign;


		mmioClose(hmmio, 0);
	}


	// サウンドソース生成
	audioXAudio->CreateSourceVoice(&sourceVoice, &wfx);
	assert(sourceVoice);
}


//!-----------------------------------------------------------
//! @fn      : Play(bool loop = false)
//! @brief   : サウンドの再生
//! @param   : loop...ループ再生をするかどうか
//! @return  : なし
//! @details : サウンドの再生を実装
//!            バッファを設定し再生する
//!            loop が true ならループ再生する（初期値は false ）
//!-----------------------------------------------------------
void Audio::Play(bool loop)
{
	sourceVoice->Stop();
	sourceVoice->FlushSourceBuffers();

	// バッファ設定
	XAUDIO2_BUFFER bufinfo;

	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = length;
	bufinfo.pAudioData = soundData;
	bufinfo.PlayBegin = 0;
	bufinfo.PlayLength = playLength;

	// ループ設定
	if (loop)
	{
		bufinfo.LoopBegin = 0;
		bufinfo.LoopLength = playLength;
		bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	sourceVoice->SubmitSourceBuffer(&bufinfo, NULL);

	sourceVoice->SetVolume(0.1f);

	// 再生
	sourceVoice->Start();

}


//!-----------------------------------------------------------
//! @fn      : Stop()
//! @brief   : サウンドの停止
//! @param   : なし
//! @return  : なし
//! @details : サウンドの停止を実装
//!-----------------------------------------------------------
void Audio::Stop()
{
	sourceVoice->Stop();
}

