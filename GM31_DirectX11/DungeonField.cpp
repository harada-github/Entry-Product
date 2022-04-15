//!============================================================
//!
//!  @file    : DungeonField.cpp
//!  @brief   : �_���W�������t�B�[���h�N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �_���W�����t�B�[���h�`��̎���
//!             �Q�[���I�u�W�F�N�g�N���X���p��
//!
//!============================================================
#pragma once


//============================================================
//�@�C���N���[�h
//============================================================
#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "Resource.h"
#include "DungeonField.h"
#include "DungeonMapData.h"


//============================================================
//�@�ϐ��錾
//============================================================



//============================================================
//�@�֐�
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : ������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������ƒ��_�o�b�t�@������V�F�[�_�[�̐ݒ�
//!-----------------------------------------------------------
void DungeonField::Init()
{
	//�Z���_�̃f�[�^�ł����݁Z
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-DUNGEON_MAP_DATA_X - 1.0f, 0.0f, DUNGEON_MAP_DATA_Z + 1.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(DUNGEON_MAP_DATA_X - 1.0f, 0.0f, DUNGEON_MAP_DATA_Z + 1.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2((float)DUNGEON_MAP_DATA_X / 4, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-DUNGEON_MAP_DATA_X - 1.0f, 0.0f, -DUNGEON_MAP_DATA_Z + 1.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, (float)DUNGEON_MAP_DATA_Z / 4);

	vertex[3].Position = D3DXVECTOR3(DUNGEON_MAP_DATA_X - 1.0f, 0.0f, -DUNGEON_MAP_DATA_Z + 1.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2((float)DUNGEON_MAP_DATA_X / 4, (float)DUNGEON_MAP_DATA_Z / 4);


	//�Z���_�o�b�t�@�����Z
	// bd�͒��_�̐ݒ�
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;    // �T�C�Y�����߂�
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // �ǂ�����BUFFER�Ȃ̂��������Őݒ�
	bd.CPUAccessFlags = 0;

	// �����l��ݒ肵�Ă�
	// ����͐�قǍ�������_�̃f�[�^�����Ă�
	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	// �����Œ��_�o�b�t�@������Ă�
	// ���̊֐���Index��Vertex������炵��
	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);

	//�Z�e�N�X�`���̓ǂݍ��݁Z
 	texture = Resource::ResourceTextureLoad("Asset/Texture/field2.jpg");

	// �G���[�`�F�b�N
	assert(texture);

	// �V�F�[�_�[�̓ǂݍ���
	Renderer::CreateVertexShader(&vertexShader, &vertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&pixelShader, "vertexLightingPS.cso");

	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : �I������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void DungeonField::Uninit()
{

}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void DungeonField::Update()
{

}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : �`�������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : ���̓��C�A�E�g�ݒ�A�V�F�[�_�[�ݒ�
//!            �}�g���N�X�ݒ�A���_�o�b�t�@�ݒ�
//!            �e�N�X�`���ݒ�A�v���~�e�B�u�g�|���W�ݒ�
//!            �|���S���`��
//!-----------------------------------------------------------
void DungeonField::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(vertexLayout);

	// �V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(vertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(pixelShader, NULL, 0);

	// �}�g���N�X�ݒ�
	D3DXMATRIX World, Scale, Rotate, Trans;
	D3DXMatrixScaling(&Scale, this->scale.x, this->scale.y, this->scale.z);
	D3DXMatrixRotationYawPitchRoll(&Rotate, this->rotation.y, this->rotation.x, this->rotation.z);
	D3DXMatrixTranslation(&Trans, this->position.x, this->position.y, this->position.z);
	World = Scale * Rotate * Trans;
	Renderer::SetWorldMatrix(&World);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);
}
