//!============================================================
//!
//!  @file    : Resource.h
//!  @brief   : ���\�[�X�N���X�̃w�b�_�[�t�@�C��
//!  @author  : ���c �z��
//!  @details : ���\�[�X�֘A�̊Ǘ��̎���
//!
//!============================================================
#pragma once


//============================================================
//�@�C���N���[�h
//============================================================
#include "Model.h"
#include "AnimationModel.h"
#include "Audio.h"


//!===========================================================
//! @def TEXTURE_MAX
//! @brief   : �e�N�X�`���ő�Ǘ���
//!
//! @def MODEL_MAX
//! @brief   : ���f���ő�Ǘ���
//!
//! @def ANIMATIONMODEL_MAX
//! @brief   : �A�j���[�V�������f���ő�Ǘ���
//!
//! @def AUDIO_MAX
//! @brief   : �I�[�f�B�I�ő�Ǘ���
//!===========================================================
#define TEXTURE_MAX          (10)
#define MODEL_MAX            (10)
#define ANIMATIONMODEL_MAX   (10)
#define AUDIO_MAX            (10)


//!===========================================================
//! @struct ResourceTextureData
//! @brief   : �e�N�X�`���f�[�^�Ǘ��\����
//!===========================================================
struct ResourceTextureData
{
	ID3D11ShaderResourceView* textureData;
	char fileName[256];
	int id;
};

//!===========================================================
//! @struct ResourceModelData
//! @brief   : ���f���f�[�^�Ǘ��\����
//!===========================================================
struct ResourceModelData
{
	Model* modelData;
	char fileName[256];
	int id;
};

//!===========================================================
//! @struct ResourceAnimationModelData
//! @brief   : �A�j���[�V�������f���f�[�^�Ǘ��\����
//!===========================================================
struct ResourceAnimationModelData
{
	AnimationModel* aniModelData;
	char fileName[256];
	int id;
};


//!===========================================================
//! @struct ResourceAudioData
//! @brief   : �I�[�f�B�I�f�[�^�Ǘ��\����
//!===========================================================
struct ResourceAudioData
{
	Audio* audioData;
	char fileName[256];
	int id;
};



//!===========================================================
//! @class Resource
//! @brief   : ���\�[�X�֘A�̊Ǘ��̎����̃N���X
//!===========================================================
class Resource
{
public:

	//!-------------------------------------------------------
	//! @fn      : Resource()
	//! @brief   : �R���X�g���N�^
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������e�Ȃ�
	//!-------------------------------------------------------
	Resource(){}

	//!-------------------------------------------------------
	//! @fn      : ~Resource()
	//! @brief   : �f�X�g���N�^
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������e�Ȃ�
	//!-------------------------------------------------------
	~Resource(){}

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : ������������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������ƃ������m��
	//!-------------------------------------------------------
	static void Init();

	//!-------------------------------------------------------
	//! @fn      : Uninit()
	//! @brief   : �I������������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �f�[�^�ƃ��������
	//!-------------------------------------------------------
	static void Uninit();

	//!-------------------------------------------------------
	//! @fn      : ResourceTextureLoad(const char* loadFileName)
	//! @brief   : �e�N�X�`���̃��[�h������
	//! @param   : loadFileName...���[�h����t�@�C���̖��O
	//! @return  : ���[�h�ς݂܂��̓��[�h�����f�[�^��Ԃ�
	//! @details : �e�N�X�`���̃��[�h������
	//!�@          �e�N�X�`�������[�h�ς݂��ǂ����`�F�b�N
    //!�@          ���[�h�ς݂Ȃ炻�̃f�[�^��Ԃ�
    //!�@          �����łȂ��ꍇ�̓��[�h���Ă��̃f�[�^��Ԃ�
	//!-------------------------------------------------------
	static ID3D11ShaderResourceView* ResourceTextureLoad(const char* loadFileName);

	//!-------------------------------------------------------
	//! @fn      : ResourceModelLoad(const char* loadFileName)
	//! @brief   : ���f���̃��[�h������
	//! @param   : loadFileName...���[�h����t�@�C���̖��O
	//! @return  : ���[�h�ς݂܂��̓��[�h�����f�[�^��Ԃ�
	//! @details : ���f���̃��[�h������
	//!�@          ���f�������[�h�ς݂��ǂ����`�F�b�N
	//!�@          ���[�h�ς݂Ȃ炻�̃f�[�^��Ԃ�
	//!�@          �����łȂ��ꍇ�̓��[�h���Ă��̃f�[�^��Ԃ�
	//!-------------------------------------------------------
	static Model* ResourceModelLoad(const char* loadFileName);

	//!-------------------------------------------------------
	//! @fn      : ResourceAnimationModelLoad(const char* loadFileName)
	//! @brief   : �A�j���[�V�������f���̃��[�h������
	//! @param   : loadFileName...���[�h����t�@�C���̖��O
	//! @return  : ���[�h�ς݂܂��̓��[�h�����f�[�^��Ԃ�
	//! @details : �A�j���[�V�������f���̃��[�h������
	//!�@          �A�j���[�V�������f�������[�h�ς݂��ǂ����`�F�b�N
	//!�@          ���[�h�ς݂Ȃ炻�̃f�[�^��Ԃ�
	//!�@          �����łȂ��ꍇ�̓��[�h���Ă��̃f�[�^��Ԃ�
	//!-------------------------------------------------------
	static AnimationModel* ResourceAnimationModelLoad(const char* loadFileName);

	//!-------------------------------------------------------
	//! @fn      : ResourceAudioLoad(const char* loadFileName)
	//! @brief   : �I�[�f�B�I�f�[�^�̃��[�h������
	//! @param   : loadFileName...���[�h����t�@�C���̖��O
	//! @return  : ���[�h�ς݂܂��̓��[�h�����f�[�^��Ԃ�
	//! @details : �I�[�f�B�I�f�[�^�̃��[�h������
	//!�@          �I�[�f�B�I�f�[�^�����[�h�ς݂��ǂ����`�F�b�N
	//!�@          ���[�h�ς݂Ȃ炻�̃f�[�^��Ԃ�
	//!�@          �����łȂ��ꍇ�̓��[�h���Ă��̃f�[�^��Ԃ�
	//!-------------------------------------------------------
	static Audio* ResourceAudioLoad(const char* loadFileName);

private:

	//! �e�N�X�`���f�[�^�֘A�ϐ�
	static ResourceTextureData*  resourceTextureData;
	static int resourceTextureCount;

	//! ���f���f�[�^�֘A�ϐ�
	static ResourceModelData* resourceModelData;
	static int resourceModelCount;

	//! �A�j���[�V�������f���f�[�^�֘A�ϐ�
	static ResourceAnimationModelData* resourceAniModelData;
	static int resourceAniModelCount;

	//! �I�[�f�B�I�f�[�^�֘A�ϐ�
	static ResourceAudioData* resourceAudioData;
	static int resourceAudioCount;

};