//!============================================================
//!
//!  @file    : AnimationModel.h
//!  @brief   : �A�j���[�V�������f���N���X�̃w�b�_�[�t�@�C��
//!  @author  : ���c �z��
//!  @details : �A�j���[�V�������f���̃��[�h�A�A�����[�h
//!             �������邽�߂̃{�[���̍쐬
//!
//!============================================================
#pragma once


//============================================================
//�@�C���N���[�h
//============================================================
#include <unordered_map>
#include "assimp//cimport.h"
#include "assimp//scene.h"
#include "assimp//postprocess.h"
#include "assimp//matrix4x4.h"
#pragma comment (lib, "assimp.lib")


//!===========================================================
//! @struct DEFORM_VERTEX
//! @brief   : �ό`�㒸�_�\����
//!===========================================================
struct DEFORM_VERTEX
{
	aiVector3D  Position;
	aiVector3D  Normal;
	int         BoneNum; 
	std::string BoneName[4];   // �{���̓{�[���C���f�b�N�X�ŊǗ�����ׂ�
	float       BoneWeight[4];
};

//!===========================================================
//! @struct BONE
//! @brief   : �{�[���\����
//!===========================================================
struct BONE
{
	aiMatrix4x4 Matrix;
	aiMatrix4x4 AnimationMatrix;
	aiMatrix4x4 OffsetMatrix;
};


//!===========================================================
//! @class AnimationModel
//! @brief   : �A�j���[�V�������f���̍쐬���s���N���X
//!===========================================================
class AnimationModel
{
public:

	//!-------------------------------------------------------
	//! @fn      : Load(const char *loadFileName)
	//! @brief   : ���f���̃��[�h������
	//! @param   : loadFileName...���[�h����t�@�C���̖��O
	//! @return  : �Ȃ�
	//! @details : �t�@�C���̓ǂݍ���
	//!            ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�𐶐�
	//!            �ό`�㒸�_�f�[�^�ƃ{�[���f�[�^��������
	//!            �e�N�X�`���̓ǂݍ���
	//!-------------------------------------------------------
	void Load(const char *loadFileName);

	//!-------------------------------------------------------
	//! @fn         : LoadAnimation(const char *animationFileName, const char* animationName)
	//! @brief      : �A�j���[�V�����̃��[�h������
	//! @param arg1 : animationFileName...���[�h����A�j���[�V�����̃t�@�C����
	//! @param arg2 : animationName.......�A�j���[�V������ݒ肷��ۂ̖��O
	//! @return     : �Ȃ�
	//! @details    : �t�@�C���̓ǂݍ���
	//!-------------------------------------------------------
	void LoadAnimation(const char *animationFileName, const char* animationName);

	//!-------------------------------------------------------
	//! @fn      : Unload()
	//! @brief   : ���f���̃A�����[�h������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̉��
	//!            ���̑������[�X�������s��
	//!-------------------------------------------------------
	void Unload();

	//!-------------------------------------------------------
	//! @fn         : Update(const char* animationName, int animationFrame)
	//! @brief      : ���f���̍X�V����������
	//! @param arg1 : animationName....�ݒ肵���A�j���[�V�����̖��O
	//! @param arg2 : animationFrame...�X�V����ۂ̃t���[��
	//! @return     : �Ȃ�
	//! @details    : �A�j���[�V�����̍X�V
	//!               �Đ��������A�j���[�V�����̖��O�ƍĐ����邽�߂̃t���[���������Ɏg�p
	//!-------------------------------------------------------
	void Update(const char* animationName, int animationFrame);

	//!-------------------------------------------------------
	//! @fn      : Draw()
	//! @brief   : ���f���̕`�������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �`��ݒ�����ĕ`����s��
	//!-------------------------------------------------------
	void Draw();

private:

	//!-------------------------------------------------------
	//! @fn      : CreateBone(aiNode* node)
	//! @brief   : �{�[���f�[�^�̍쐬������
	//! @param   : node...
	//! @return  : �Ȃ�
	//! @details : �q���Ȃ��ă{�[�����쐬
	//!-------------------------------------------------------
	void CreateBone(aiNode* node);

	//!-------------------------------------------------------
	//! @fn         : UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix)
	//! @brief      : �{�[���}�g���N�X���X�V������
	//! @param arg1 : node.....�C���|�[�g�t�@�C���̃��[�g�m�[�h
	//! @param arg2 : matrix...�X�V����{�[���}�g���N�X
	//! @return     : �Ȃ�
	//! @details    : �}�g���N�X����Z���ă}�g���N�X���X�V
	//!-------------------------------------------------------
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);

	//! �C���|�[�g�t�@�C�����i�[
	const aiScene* aniAiScene = NULL;

	//! ���_�o�b�t�@
	ID3D11Buffer** vertexBuffer;

	//! �C���f�b�N�X�o�b�t�@
	ID3D11Buffer** indexBuffer;

	//! a�A�j���[�V�����f�[�^
	std::unordered_map<std::string, const aiScene*> animation;

	//! �e�N�X�`���f�[�^
	std::unordered_map<std::string, ID3D11ShaderResourceView*> texture;

	//! �ό`�㒸�_�f�[�^
	std::vector<DEFORM_VERTEX>* deformVertex;
	
	//! �{�[���f�[�^
	std::unordered_map<std::string, BONE> bone;

};


