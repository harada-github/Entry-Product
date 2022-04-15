//!============================================================
//!
//!  @file    : Polygon2D.h
//!  @brief   : �|���S��2D�I�u�W�F�N�g�N���X�̃w�b�_�[�t�@�C��
//!  @author  : ���c �z��
//!  @details : 2D�I�u�W�F�N�g�̌p�����ƂȂ�N���X
//!             �Q�[���I�u�W�F�N�g�N���X���p��
//!
//!============================================================
#pragma once


//============================================================
//�@�C���N���[�h
//============================================================
#include "GameObject.h"


//!===========================================================
//! @class Polygon2D
//! @brief   : �p�����̃|���S��2D�I�u�W�F�N�g�����̃N���X
//!===========================================================
class Polygon2D : public GameObject
{
public:

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : ������������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������ƒ��_�o�b�t�@������V�F�[�_�[�̐ݒ�
	//!-------------------------------------------------------
	virtual void Init()
	{
		//�Z���_�̃f�[�^�ł����݁Z
		//vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		//vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		//vertex[1].Position = D3DXVECTOR3(200.0f, 0.0f, 0.0f);
		//vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		//vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		//vertex[2].Position = D3DXVECTOR3(0.0f, 200.0f, 0.0f);
		//vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		//vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		//vertex[3].Position = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
		//vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		//vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


		//�Z���_�o�b�t�@�����Z
		// bd�͒��_�̐ݒ�
		//D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * 4;    // �T�C�Y�����߂�
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // �ǂ�����BUFFER�Ȃ̂��������Őݒ�
		bd.CPUAccessFlags = 0;

		// �����l��ݒ肵�Ă�
		// ����͐�قǍ�������_�̃f�[�^�����Ă�
		//D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = vertex;

		// �����Œ��_�o�b�t�@������Ă�
		// ���̊֐���Index��Vertex������炵��
		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);

		////�Z�e�N�X�`���̓ǂݍ��݁Z
		//texture = Resource::ResourceTextureLoad("Asset/Texture/renga.jpg");
		////D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(), "Asset/Texture/renga.jpg", NULL, NULL, &texture, NULL);
		//if (texture == NULL)
		//{
		//	return;
		//}

		//// �G���[�`�F�b�N
		//// �f�o�b�O�̂Ƃ��͖��������炵��
		//assert(texture);

		//// �R���p�C���ς݂̃V�F�[�_�[�v���O�����������œǂݍ���
		//// ��unlit��Lighting���Ȃ��Ƃ����Ӗ�
		//Renderer::CreateVertexShader(&vertexShader, &vertexLayout, "unlitTextureVS.cso");
		//Renderer::CreatePixelShader(&pixelShader, "unlitTexturePS.cso");
	}

	//!-------------------------------------------------------
	//! @fn      : Uninit()
	//! @brief   : �I������������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������e�Ȃ�
	//!-------------------------------------------------------
	virtual void Uninit() {}

	//!-------------------------------------------------------
	//! @fn      : Update()
	//! @brief   : �X�V������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������e�Ȃ�
	//!-------------------------------------------------------
	virtual void Update() {}

	//!-------------------------------------------------------
	//! @fn      : Draw()
	//! @brief   : �`�������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : ���̓��C�A�E�g�ݒ�A�V�F�[�_�[�ݒ�
	//!            �}�g���N�X�ݒ�A���_�o�b�t�@�ݒ�
	//!            �e�N�X�`���ݒ�A�v���~�e�B�u�g�|���W�ݒ�
	//!            �|���S���`��
	//!            �ׂ����ύX���Ȃ���Όp�������N���X�ł��̊֐����Ăяo��
	//!-------------------------------------------------------
	virtual void Draw() 
	{
		// ���̓��C�A�E�g�ݒ�
		Renderer::GetDeviceContext()->IASetInputLayout(vertexLayout);

		// �V�F�[�_�[�ݒ�
		Renderer::GetDeviceContext()->VSSetShader(vertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(pixelShader, NULL, 0);

		// �}�g���N�X�ݒ�
		Renderer::SetWorldViewProjection2D();

		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		// �e�N�X�`���ݒ�
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

		// �v���~�e�B�u�g�|���W�ݒ�
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �|���S���`��
		Renderer::GetDeviceContext()->Draw(4, 0);
	}


protected:
	
	VERTEX_3D vertex[4];
	D3D11_BUFFER_DESC bd{};
	D3D11_SUBRESOURCE_DATA sd{};

private:

};