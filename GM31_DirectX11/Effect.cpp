//!============================================================
//!
//!  @file    : Effect.cpp
//!  @brief   : �G�t�F�N�g�N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �G�t�F�N�g�`������̃N���X
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
#include "GameScene.h"
#include "Camera.h"
#include "Effect.h"


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
void Effect::Init()
{
	//�Z���_�̃f�[�^�ł����݁Z
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(0.25f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 0.25f);

	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(0.25f, 0.25f);


	//�Z���_�o�b�t�@�����Z
	// bd�͒��_�̐ݒ�
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;    // �T�C�Y�����߂�
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // �ǂ�����BUFFER�Ȃ̂��������Őݒ�
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	// �����l��ݒ肵�Ă�
	// ����͐�قǍ�������_�̃f�[�^�����Ă�
	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	// �����Œ��_�o�b�t�@������Ă�
	// ���̊֐���Index��Vertex������炵��
	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);

	//�Z�e�N�X�`���̓ǂݍ��݁Z
	texture = Resource::ResourceTextureLoad("Asset/Texture/exp.png");

	// �G���[�`�F�b�N
	assert(texture);

	// �V�F�[�_�[�̓ǂݍ���
	Renderer::CreateVertexShader(&vertexShader, &vertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&pixelShader, "unlitTexturePS.cso");

	position = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale    = D3DXVECTOR3(3.0f, 3.0f, 3.0f);

	frame = 30;
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : �I������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void Effect::Uninit()
{

}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : frame�̍X�V
//!            ���̃t���[�����𒴂�����I�u�W�F�N�g������
//!-----------------------------------------------------------
void Effect::Update()
{
	//frame++;

	if (frame >= 64)
	{
		frame = 0;

		SetDestroy();
		return;
	}
}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : �`�������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �e�N�X�`���̍��W���Z�o
//!            ���̓��C�A�E�g�ݒ�A�V�F�[�_�[�ݒ�
//!            �}�g���N�X�ݒ�A���_�o�b�t�@�ݒ�
//!            �e�N�X�`���ݒ�A�v���~�e�B�u�g�|���W�ݒ�
//!            �|���S���`��A�r���{�[�h�̐ݒ�
//!-----------------------------------------------------------
void Effect::Draw()
{
	// �e�N�X�`�����W�Z�o
	float tex_x = frame / 8 % 4 * 0.25f;
	float tex_y = frame / 8 / 4 * 0.25f;

	// ���_�f�[�^��������
	D3D11_MAPPED_SUBRESOURCE msr;

	// Map���g���ď����ł���o�b�t�@���擾
	// �l�������Ƃ��Ă�LockUnlock�Ǝ��Ă���
	Renderer::GetDeviceContext()->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(tex_x, tex_y);

	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(tex_x + 0.25f, tex_y);

	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(tex_x, tex_y + 0.25f);

	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(tex_x + 0.25f, tex_y + 0.25f);

	Renderer::GetDeviceContext()->Unmap(vertexBuffer, 0);


	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(vertexLayout);

	// �V�F�[�_�[�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(vertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(pixelShader, NULL, 0);

	// �V�[���̏����擾
	Scene* scene = Manager::GetScene();

	// �J�����̏����擾
	Camera* camera = scene->GetGameObject<Camera>(0);

	// �J�����̃r���[�}�g���N�X�擾
	D3DXMATRIX view = camera->Camera_GetViewMatrix();

	// �r���[�̋t�s��
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view); // �t�s��
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	// �}�g���N�X�ݒ�
	D3DXMATRIX World, Scale, Rotate, Trans;
	D3DXMatrixScaling(&Scale, this->scale.x, this->scale.y, this->scale.z);
	//D3DXMatrixRotationYawPitchRoll(&Rotate, this->rotation.y, this->rotation.x, this->rotation.z);
	D3DXMatrixTranslation(&Trans, this->position.x, this->position.y, this->position.z);
	//World = Scale * Rotate * Trans;
	World = Scale * invView * Trans;
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
