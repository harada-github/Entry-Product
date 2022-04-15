//!============================================================
//!
//!  @file    : Audio.cpp
//!  @brief   : �I�[�f�B�I�N���X�̃\�[�X�t�@�C��
//!  @author  : �z�z
//!  @details : �I�[�f�B�I�i�T�E���h�j�̊ȈՎ���
//!
//!============================================================
#pragma once


//============================================================
//�@�C���N���[�h
//============================================================
#include "Main.h"
#include "Audio.h"


//============================================================
//�@�ϐ��錾
//============================================================
IXAudio2*				Audio::audioXAudio = NULL;
IXAudio2MasteringVoice*	Audio::masteringVoice = NULL;


//============================================================
//�@�֐�
//============================================================
//!-----------------------------------------------------------
//! @fn      : InitMaster()
//! @brief   : �}�X�^�̏�����������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : COM�̏�����
//!            XAudio�̐���
//!            �}�X�^�����O�{�C�X�̐���
//!-----------------------------------------------------------
void Audio::InitMaster()
{
	// COM������
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio����
	XAudio2Create(&audioXAudio, 0);

	// �}�X�^�����O�{�C�X����
	audioXAudio->CreateMasteringVoice(&masteringVoice);
}


//!-----------------------------------------------------------
//! @fn      : UninitMaster()
//! @brief   : �}�X�^�̏�����������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �}�X�^�����O�{�C�X�̉��
//!            XAudio�̉��
//!            COM�̏I������
//!-----------------------------------------------------------
void Audio::UninitMaster()
{
	// �}�X�^�����O�{�C�X�̉��
	masteringVoice->DestroyVoice();

	// XAudio�̉��
	audioXAudio->Release();

	// COM�̏I������
	CoUninitialize();
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : �I������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �V�[���̏I�������Ȃ�
//!-----------------------------------------------------------
void Audio::Uninit()
{
	sourceVoice->Stop();
	sourceVoice->DestroyVoice();

	delete[] soundData;
}


//!-----------------------------------------------------------
//! @fn      : Load(const char *audioFileName)
//! @brief   : �I�[�f�B�I�f�[�^�̃��[�h������
//! @param   : audioFileName...���[�h�������t�@�C����
//! @return  : �Ȃ�
//! @details : �T�E���h�f�[�^�̓ǂݍ���
//!            �T�E���h�\�[�X�̐���
//!-----------------------------------------------------------
void Audio::Load(const char *audioFileName)
{

	// �T�E���h�f�[�^�Ǎ�
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


	// �T�E���h�\�[�X����
	audioXAudio->CreateSourceVoice(&sourceVoice, &wfx);
	assert(sourceVoice);
}


//!-----------------------------------------------------------
//! @fn      : Play(bool loop = false)
//! @brief   : �T�E���h�̍Đ�
//! @param   : loop...���[�v�Đ������邩�ǂ���
//! @return  : �Ȃ�
//! @details : �T�E���h�̍Đ�������
//!            �o�b�t�@��ݒ肵�Đ�����
//!            loop �� true �Ȃ烋�[�v�Đ�����i�����l�� false �j
//!-----------------------------------------------------------
void Audio::Play(bool loop)
{
	sourceVoice->Stop();
	sourceVoice->FlushSourceBuffers();

	// �o�b�t�@�ݒ�
	XAUDIO2_BUFFER bufinfo;

	memset(&bufinfo, 0x00, sizeof(bufinfo));
	bufinfo.AudioBytes = length;
	bufinfo.pAudioData = soundData;
	bufinfo.PlayBegin = 0;
	bufinfo.PlayLength = playLength;

	// ���[�v�ݒ�
	if (loop)
	{
		bufinfo.LoopBegin = 0;
		bufinfo.LoopLength = playLength;
		bufinfo.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	sourceVoice->SubmitSourceBuffer(&bufinfo, NULL);

	sourceVoice->SetVolume(0.1f);

	// �Đ�
	sourceVoice->Start();

}


//!-----------------------------------------------------------
//! @fn      : Stop()
//! @brief   : �T�E���h�̒�~
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �T�E���h�̒�~������
//!-----------------------------------------------------------
void Audio::Stop()
{
	sourceVoice->Stop();
}

