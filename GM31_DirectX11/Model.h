//!============================================================
//!
//!  @file    : Model.h
//!  @brief   : ���f���N���X�̃w�b�_�[�t�@�C��
//!  @author  : �w�Z�z�z�̃t�@�C��
//!  @details : ���f���̎���
//!             �A�j���[�V�������g�p���Ȃ��I�u�W�F�N�g�͂��̃N���X���g�p
//!
//!============================================================
#pragma once


//!===========================================================
//! @struct MODEL_MATERIAL
//! @brief   : �}�e���A���\����
//!===========================================================
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
	ID3D11ShaderResourceView*	Texture;
};

//!===========================================================
//! @struct SUBSET
//! @brief   : �`��T�u�Z�b�g�\����
//!===========================================================
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};

//!===========================================================
//! @struct MODEL
//! @brief   : ���f���\����
//!===========================================================
struct MODEL
{
	VERTEX_3D		*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	SUBSET			*SubsetArray;
	unsigned int	SubsetNum;
};


//!===========================================================
//! @class Model
//! @brief   : ���f�������̃N���X
//!===========================================================
class Model
{
public:

	//!-------------------------------------------------------
	//! @fn      : Draw()
	//! @brief   : ���f���̕`�������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �`��ݒ�����ĕ`����s��
	//!-------------------------------------------------------
	void Draw();

	//!-------------------------------------------------------
	//! @fn      : Load(const char *loadFileName)
	//! @brief   : ���f���̃��[�h������
	//! @param   : loadFileName...���[�h����t�@�C���̖��O
	//! @return  : �Ȃ�
	//! @details : �t�@�C���̓ǂݍ���
	//!            ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�𐶐�
	//!            �T�u�Z�b�g�ݒ�
	//!-------------------------------------------------------
	void Load(const char *loadFileName);

	//!-------------------------------------------------------
	//! @fn      : Unload()
	//! @brief   : ���f���̃A�����[�h������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̉��
	//!            ���̑������[�X�������s��
	//!-------------------------------------------------------
	void Unload();

private:

	//!-------------------------------------------------------
	//! @fn         : LoadObj(const char *loadFileName, MODEL *loadModel)
	//! @brief      : ���f���̓ǂݍ���
	//! @param arg1 : loadFileName....���[�h����t�@�C����
	//! @param arg2 : loadModel.......�ǂݍ��񂾃f�[�^���琶���������̂��i�[
	//! @return     : �Ȃ�
	//! @details    : �t�@�C���̓ǂݍ���
	//!               �ǂݍ��񂾃t�@�C�����烂�f���𐶐�
	//!-------------------------------------------------------
	void LoadObj(const char *loadFileName, MODEL *loadModel);

	//!-------------------------------------------------------
	//! @fn         : LoadMaterial(const char *loadFileName, MODEL_MATERIAL **loadMaterialArray, unsigned int *loadMaterialNum)
	//! @brief      : �}�e���A���ǂݍ���
	//! @param arg1 : loadFileName............���[�h����t�@�C����
	//! @param arg2 : loadMaterialArray.......�ǂݍ��񂾃f�[�^����}�e���A����z�u
	//! @param arg3 : loadMaterialNum.........�ǂݍ��񂾃f�[�^����}�e���A�������i�[
	//! @return     : �Ȃ�
	//! @details    : �t�@�C���̓ǂݍ���
	//!               �ǂݍ��񂾃t�@�C������}�e���A���𐶐�
	//!-------------------------------------------------------
	void LoadMaterial(const char *loadFileName, MODEL_MATERIAL **loadMaterialArray, unsigned int *loadMaterialNum);

	//! ���_�o�b�t�@
	ID3D11Buffer*	m_VertexBuffer;

	//! �C���f�b�N�X�o�b�t�@
	ID3D11Buffer*	m_IndexBuffer;

	//! �T�u�Z�b�g�Ɏg�p����ϐ�
	SUBSET*	m_SubsetArray;
	unsigned int	m_SubsetNum;

};