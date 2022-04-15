//!============================================================
//!
//!  @file    : Resource.cpp
//!  @brief   : ���\�[�X�N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : ���\�[�X�֘A�̊Ǘ��̎���
//!
//!============================================================
#pragma once


//============================================================
//�@�C���N���[�h
//============================================================
#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "Model.h"
#include "AnimationModel.h"
#include "Resource.h"
#include <stdlib.h>


//============================================================
//�@�ϐ��錾
//============================================================
ResourceTextureData* Resource::resourceTextureData;
int Resource::resourceTextureCount;

ResourceModelData* Resource::resourceModelData;
int Resource::resourceModelCount;

ResourceAnimationModelData* Resource::resourceAniModelData;
int Resource::resourceAniModelCount;

ResourceAudioData* Resource::resourceAudioData;
int Resource::resourceAudioCount;


//============================================================
//�@�֐�
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : ������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������ƃ������m��
//!-----------------------------------------------------------
void Resource::Init()
{
	// �ϐ��̏�����
	resourceTextureCount = 0;
	resourceModelCount = 0;
	resourceAniModelCount = 0;
	resourceAudioCount = 0;

	// �f�[�^�i�[�p�̕ϐ��̃������m��
	resourceTextureData  = (ResourceTextureData*)malloc(TEXTURE_MAX * sizeof(ResourceTextureData));
	resourceModelData    = (ResourceModelData*)malloc(MODEL_MAX * sizeof(ResourceModelData));
	resourceAniModelData = (ResourceAnimationModelData*)malloc(ANIMATIONMODEL_MAX * sizeof(ResourceAnimationModelData));
	resourceAudioData    = (ResourceAudioData*)malloc(AUDIO_MAX * sizeof(ResourceAudioData));

	// �g�p���Ă��Ȃ��̈�ׂ̈�id��-1�����E������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		resourceTextureData[i].textureData = NULL;
		resourceTextureData[i].id = -1;
	}
	for (int i = 0; i < MODEL_MAX; i++)
	{
		resourceModelData[i].modelData = NULL;
		resourceModelData[i].id = -1;
	}
	for (int i = 0; i < ANIMATIONMODEL_MAX; i++)
	{
		resourceAniModelData[i].aniModelData = NULL;
		resourceAniModelData[i].id = -1;
	}
	for (int i = 0; i < AUDIO_MAX; i++)
	{
		resourceAudioData[i].audioData = NULL;
		resourceAudioData[i].id = -1;
	}
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : �I������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �f�[�^�ƃ��������
//!-----------------------------------------------------------
void Resource::Uninit()
{
	// ���[�h�����I�[�f�B�I�̃f�[�^���������
	for (int i = 0; i < AUDIO_MAX; i++)
	{
		if (resourceAudioData[i].id != -1)
		{
			resourceAudioData[i].audioData->Uninit();
			delete resourceAudioData[i].audioData;
		}
	}

	// ���[�h�����A�j���[�V�������f���̃f�[�^���������
	for (int i = 0; i < ANIMATIONMODEL_MAX; i++)
	{
		if (resourceAniModelData[i].id != -1)
		{
			delete resourceAniModelData[i].aniModelData;
		}
	}

	// ���[�h�������f���̃f�[�^���������
	for (int i = 0; i < MODEL_MAX; i++)
	{
		if (resourceModelData[i].id != -1)
		{
			delete resourceModelData[i].modelData;
		}
	}

	// ���[�h�����e�N�X�`���̃f�[�^���������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (resourceTextureData[i].id != -1)
		{
			resourceTextureData[i].textureData->Release();
		}
	}

	// �f�[�^�i�[�p�̕ϐ������
	free(resourceAudioData);
	free(resourceAniModelData);
	free(resourceModelData);
	free(resourceTextureData);
}


//!-----------------------------------------------------------
//! @fn      : ResourceTextureLoad(const char* loadFileName)
//! @brief   : �e�N�X�`���̃��[�h������
//! @param   : loadFileName...���[�h����t�@�C���̖��O
//! @return  : ���[�h�ς݂܂��̓��[�h�����f�[�^��Ԃ�
//! @details : �e�N�X�`���̃��[�h������
//!�@          �e�N�X�`�������[�h�ς݂��ǂ����`�F�b�N
//!�@          ���[�h�ς݂Ȃ炻�̃f�[�^��Ԃ�
//!�@          �����łȂ��ꍇ�̓��[�h���Ă��̃f�[�^��Ԃ�
//!-----------------------------------------------------------
ID3D11ShaderResourceView* Resource::ResourceTextureLoad(const char* loadFileName)
{
	// �������[�h���Ȃ��ׂ̏���
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		// �i�[���Ă���f�[�^�ɓ����t�@�C������������true
		if (strcmp(resourceTextureData[i].fileName, loadFileName) == 0)
		{
			// ���[�h�ς݂̃e�N�X�`���̃f�[�^��Ԃ�
			return resourceTextureData[i].textureData;
		}
	}

	// �m�ۂ���Ă���ꍇ�f�[�^�Ƀt�@�C������id���i�[
	strcpy(resourceTextureData[resourceTextureCount].fileName, loadFileName);
	resourceTextureData[resourceTextureCount].id = resourceTextureCount;

	// �e�N�X�`�������[�h
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(), resourceTextureData[resourceTextureCount].fileName, NULL,
		NULL, &resourceTextureData[resourceTextureCount].textureData, NULL);

	// �G���[�`�F�b�N
	assert(resourceTextureData[resourceTextureCount].textureData);

	// �J�E���g�𑝂₷
	resourceTextureCount++;

	// ���[�h�����e�N�X�`���̃f�[�^��Ԃ�
	return resourceTextureData[resourceTextureCount - 1].textureData;
}


//!-----------------------------------------------------------
//! @fn      : ResourceModelLoad(const char* loadFileName)
//! @brief   : ���f���̃��[�h������
//! @param   : loadFileName...���[�h����t�@�C���̖��O
//! @return  : ���[�h�ς݂܂��̓��[�h�����f�[�^��Ԃ�
//! @details : ���f���̃��[�h������
//!�@          ���f�������[�h�ς݂��ǂ����`�F�b�N
//!�@          ���[�h�ς݂Ȃ炻�̃f�[�^��Ԃ�
//!�@          �����łȂ��ꍇ�̓��[�h���Ă��̃f�[�^��Ԃ�
//!-----------------------------------------------------------
Model* Resource::ResourceModelLoad(const char* loadFileName)
{
	// �������[�h���Ȃ��ׂ̏���
	for (int i = 0; i < MODEL_MAX; i++)
	{
		// �i�[���Ă���f�[�^�ɓ����t�@�C������������true
		if (strcmp(resourceModelData[i].fileName, loadFileName) == 0)
		{
			// ���[�h�ς݂̃��f���̃f�[�^��Ԃ�
			return resourceModelData[i].modelData;
		}
	}

	// �m�ۂ���Ă���ꍇ�f�[�^�Ƀt�@�C������id���i�[
	strcpy(resourceModelData[resourceModelCount].fileName, loadFileName);
	resourceModelData[resourceModelCount].id = resourceModelCount;

	// ���f�������[�h
	resourceModelData[resourceModelCount].modelData = new Model();
	resourceModelData[resourceModelCount].modelData->Load(loadFileName);

	// �J�E���g�𑝂₷
	resourceModelCount++;

	// ���[�h�������f���̃f�[�^��Ԃ�
	return resourceModelData[resourceModelCount - 1].modelData;
}


//!-----------------------------------------------------------
//! @fn      : ResourceAnimationModelLoad(const char* loadFileName)
//! @brief   : �A�j���[�V�������f���̃��[�h������
//! @param   : loadFileName...���[�h����t�@�C���̖��O
//! @return  : ���[�h�ς݂܂��̓��[�h�����f�[�^��Ԃ�
//! @details : �A�j���[�V�������f���̃��[�h������
//!�@          �A�j���[�V�������f�������[�h�ς݂��ǂ����`�F�b�N
//!�@          ���[�h�ς݂Ȃ炻�̃f�[�^��Ԃ�
//!�@          �����łȂ��ꍇ�̓��[�h���Ă��̃f�[�^��Ԃ�
//!-----------------------------------------------------------
AnimationModel* Resource::ResourceAnimationModelLoad(const char* loadFileName)
{
	// �������[�h���Ȃ��ׂ̏���
	for (int i = 0; i < ANIMATIONMODEL_MAX; i++)
	{
		// �i�[���Ă���f�[�^�ɓ����t�@�C������������true
		if (strcmp(resourceAniModelData[i].fileName, loadFileName) == 0)
		{
			// ���[�h�ς݂̃��f���̃f�[�^��Ԃ�
			return resourceAniModelData[i].aniModelData;
		}
	}

	// �m�ۂ���Ă���ꍇ�f�[�^�Ƀt�@�C������id���i�[
	strcpy(resourceAniModelData[resourceAniModelCount].fileName, loadFileName);
	resourceAniModelData[resourceAniModelCount].id = resourceAniModelCount;

	// ���f�������[�h
	resourceAniModelData[resourceAniModelCount].aniModelData = new AnimationModel();
	resourceAniModelData[resourceAniModelCount].aniModelData->Load(loadFileName);

	// �J�E���g�𑝂₷
	resourceAniModelCount++;

	// ���[�h�������f���̃f�[�^��Ԃ�
	return resourceAniModelData[resourceAniModelCount - 1].aniModelData;
}


//!-----------------------------------------------------------
//! @fn      : ResourceAudioLoad(const char* loadFileName)
//! @brief   : �I�[�f�B�I�f�[�^�̃��[�h������
//! @param   : loadFileName...���[�h����t�@�C���̖��O
//! @return  : ���[�h�ς݂܂��̓��[�h�����f�[�^��Ԃ�
//! @details : �I�[�f�B�I�f�[�^�̃��[�h������
//!�@          �I�[�f�B�I�f�[�^�����[�h�ς݂��ǂ����`�F�b�N
//!�@          ���[�h�ς݂Ȃ炻�̃f�[�^��Ԃ�
//!�@          �����łȂ��ꍇ�̓��[�h���Ă��̃f�[�^��Ԃ�
//!-----------------------------------------------------------
Audio* Resource::ResourceAudioLoad(const char* loadFileName)
{
	// �������[�h���Ȃ��ׂ̏���
	for (int i = 0; i < AUDIO_MAX; i++)
	{
		// �i�[���Ă���f�[�^�ɓ����t�@�C������������true
		if (strcmp(resourceAudioData[i].fileName, loadFileName) == 0)
		{
			// ���[�h�ς݂̃I�[�f�B�I�̃f�[�^��Ԃ�
			return resourceAudioData[i].audioData;
		}
	}

	// �m�ۂ���Ă���ꍇ�f�[�^�Ƀt�@�C������id���i�[
	strcpy(resourceAudioData[resourceAudioCount].fileName, loadFileName);
	resourceAudioData[resourceAudioCount].id = resourceAudioCount;

	// �I�[�f�B�I�����[�h
	resourceAudioData[resourceAudioCount].audioData = new Audio();
	resourceAudioData[resourceAudioCount].audioData->Load(loadFileName);

	// �J�E���g�𑝂₷
	resourceAudioCount++;

	// ���[�h�����I�[�f�B�I�̃f�[�^��Ԃ�
	return resourceAudioData[resourceAudioCount - 1].audioData;
}

