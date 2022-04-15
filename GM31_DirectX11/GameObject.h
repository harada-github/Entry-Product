//!============================================================
//!
//!  @file    : GameObject.h
//!  @brief   : �Q�[���I�u�W�F�N�g�N���X�̃w�b�_�[�t�@�C��
//!  @author  : ���c �z��
//!  @details : �Q�[���I�u�W�F�N�g�N���X�̎���
//!             �Q�[���Ŏg�p����I�u�W�F�N�g�N���X�̌p�����ƂȂ�N���X
//!             ���z�N���X�Ƃ��Ď���
//!
//!============================================================
#pragma once


//!===========================================================
//! @class GameObject
//! @brief   : �Q�[���I�u�W�F�N�g�N���X
//!===========================================================
class GameObject
{
public:

	//!-------------------------------------------------------
	//! @fn      : GameObject()
	//! @brief   : �R���X�g���N�^
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������e�Ȃ�
	//!-------------------------------------------------------
	GameObject() {}

	//!-------------------------------------------------------
	//! @fn      : ~GameObject()
	//! @brief   : �f�X�g���N�^
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �V�F�[�_�[��e�N�X�`���̐ݒ�Ɏg�p����ϐ��̉��
	//!-------------------------------------------------------
	~GameObject() {} 

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : ������������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������z�֐�
	//!-------------------------------------------------------
	virtual void Init() = 0;

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : �I������������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������z�֐�
	//!-------------------------------------------------------
	virtual void Uninit() = 0;

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : �X�V������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������z�֐�
	//!-------------------------------------------------------
	virtual void Update() = 0;

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : �`�������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������z�֐�
	//!-------------------------------------------------------
	virtual void Draw() = 0;

	//!-------------------------------------------------------
	//! @fn      : GetPosition()
	//! @brief   : �Q�[���I�u�W�F�N�g�̍��W�̎擾
	//! @param   : �Ȃ�
	//! @return  : �Q�[���I�u�W�F�N�g�̍��W
	//! @details : �Q�[���I�u�W�F�N�g�̍��W��Ԃ�
	//!-------------------------------------------------------
	D3DXVECTOR3 GetPosition()
	{
		return position;
	}


	//!-------------------------------------------------------
	//! @fn      : GetObbX()
	//! @brief   : �Q�[���I�u�W�F�N�g��OBB��X���W�̎擾
	//! @param   : �Ȃ�
	//! @return  : �Q�[���I�u�W�F�N�g��OBB��X���W
	//! @details : �Q�[���I�u�W�F�N�g��OBB��X���W��Ԃ�
	//!-------------------------------------------------------
	D3DXVECTOR3 GetObbX()
	{
		D3DXMATRIX obbRot, obbScale, obbWorld;
		D3DXMatrixScaling(&obbScale, scale.x, scale.y, scale.z);
		D3DXMatrixRotationYawPitchRoll(&obbRot, rotation.y, rotation.x, rotation.z);
		obbWorld = obbScale * obbRot;

		D3DXVECTOR3 vx;
		vx.x = obbWorld._11;
		vx.y = obbWorld._12;
		vx.z = obbWorld._13;

		return vx * 0.5f;
	}


	//!-------------------------------------------------------
	//! @fn      : GetObbZ()
	//! @brief   : �Q�[���I�u�W�F�N�g��OBB��Z���W�̎擾
	//! @param   : �Ȃ�
	//! @return  : �Q�[���I�u�W�F�N�g��OBB��Z���W
	//! @details : �Q�[���I�u�W�F�N�g��OBB��Z���W��Ԃ�
	//!-------------------------------------------------------
	D3DXVECTOR3 GetObbZ()
	{
		D3DXMATRIX obbRot, obbScale, obbWorld;
		D3DXMatrixScaling(&obbScale, scale.x, scale.y, scale.z);
		D3DXMatrixRotationYawPitchRoll(&obbRot, rotation.y, rotation.x, rotation.z);
		obbWorld = obbScale * obbRot;

		D3DXVECTOR3 vz;
		vz.x = obbWorld._31;
		vz.y = obbWorld._32;
		vz.z = obbWorld._33;

		return vz * 0.5f;
	}


	//!-------------------------------------------------------
	//! @fn      : SetPosition()
	//! @brief   : �Q�[���I�u�W�F�N�g�̍��W�̎擾
	//! @param   : setPosition...�ݒ肵�������W
	//! @return  : �Ȃ�
	//! @details : �Q�[���I�u�W�F�N�g�̍��W��ݒ�
	//!-------------------------------------------------------
	void SetPosition(D3DXVECTOR3 setPosition)
	{
		position = setPosition;
	}

	//!-------------------------------------------------------
	//! @fn      : SetDestroy()
	//! @brief   : �Q�[���I�u�W�F�N�g�̏����\��
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : destroy �� true �ɂ��ăI�u�W�F�N�g����̗\�������
	//!-------------------------------------------------------
	void SetDestroy()
	{
		destroy = true;
	}

	//!-------------------------------------------------------
	//! @fn      : Destroy()
	//! @brief   : �Q�[���I�u�W�F�N�g�̏����\��
	//! @param   : �Ȃ�
	//! @return  : �Q�[���I�u�W�F�N�g������ł������ǂ���
	//! @details : destroy �� true �Ȃ�Q�[���I�u�W�F�N�g���������
	//!-------------------------------------------------------
	bool Destroy()
	{
		if (destroy)
		{
			// �������
			//if (texture != NULL) texture->Release();
			if (vertexBuffer != NULL) vertexBuffer->Release();
			if (indexBuffer != NULL) indexBuffer->Release();

			if (vertexLayout != NULL) vertexLayout->Release();
			if (vertexShader != NULL) vertexShader->Release();
			if (pixelShader != NULL) pixelShader->Release();

			// �I������
			Uninit();

			// �I�u�W�F�N�g�̉��
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}


protected:

	//! �I�u�W�F�N�g�̍��W
	D3DXVECTOR3 position;
	//! �I�u�W�F�N�g�̉�]
	D3DXVECTOR3 rotation;
	//! �I�u�W�F�N�g�̑傫��
	D3DXVECTOR3 scale;

	bool active;
	//! �I�u�W�F�N�g�̉���\��p
	bool destroy = false;

	// ���_�V�F�[�_�[
	ID3D11VertexShader* vertexShader;  
	// �s�N�Z���V�F�[�_�[
	ID3D11PixelShader*  pixelShader;   
	// ���_�̃��C�A�E�g
	ID3D11InputLayout*  vertexLayout;  

	// ���_�f�[�^
	ID3D11Buffer*              vertexBuffer = NULL;  
	// �C���f�b�N�X�f�[�^
	ID3D11Buffer*              indexBuffer = NULL;   
	// �e�N�X�`���f�[�^
	ID3D11ShaderResourceView*  texture = NULL;       
};