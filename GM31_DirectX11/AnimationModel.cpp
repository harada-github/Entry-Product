//!============================================================
//!
//!  @file    : AnimationModel.cpp
//!  @brief   : �A�j���[�V�������f���N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �A�j���[�V�������f���̃��[�h�A�A�����[�h
//!             �������邽�߂̃{�[���̍쐬
//!
//!============================================================
#pragma once


//============================================================
//�@�C���N���[�h
//============================================================
#include "Main.h"
#include "Renderer.h"
#include "AnimationModel.h"


//============================================================
//�@�֐�
//============================================================
//!-----------------------------------------------------------
//! @fn      : Load(const char *loadFileName)
//! @brief   : ���f���̃��[�h������
//! @param   : loadFileName...���[�h����t�@�C���̖��O
//! @return  : �Ȃ�
//! @details : �t�@�C���̓ǂݍ���
//!            ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�𐶐�
//!            �ό`�㒸�_�f�[�^�ƃ{�[���f�[�^��������
//!            �e�N�X�`���̓ǂݍ���
//!-----------------------------------------------------------
void AnimationModel::Load(const char *loadFileName)
{
	const std::string modelPath(loadFileName);

	// �t�@�C���̓ǂݍ���
	aniAiScene = aiImportFile(loadFileName, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded);
	assert(aniAiScene);

	vertexBuffer = new ID3D11Buffer*[aniAiScene->mNumMeshes];
	indexBuffer = new ID3D11Buffer*[aniAiScene->mNumMeshes];


	// �ό`�㒸�_�z�񐶐�
	deformVertex = new std::vector<DEFORM_VERTEX>[aniAiScene->mNumMeshes];

	// �ċA�I�Ƀ{�[������
	CreateBone(aniAiScene->mRootNode);


	for (unsigned int m = 0; m < aniAiScene->mNumMeshes; m++)
	{
		// DirectX11�ɍ����悤�ɂ���R�[�h
		aiMesh* mesh = aniAiScene->mMeshes[m];

		// ���_�o�b�t�@����
		{
			VERTEX_3D* vertex = new VERTEX_3D[mesh->mNumVertices];

			for (unsigned int v = 0; v < mesh->mNumVertices; v++)
			{
				// �ϊ����ē���Ă���
				vertex[v].Position = D3DXVECTOR3(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z);
				vertex[v].Normal   = D3DXVECTOR3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z);
				vertex[v].TexCoord = D3DXVECTOR2(mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y);
				vertex[v].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			}

			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = sizeof(VERTEX_3D) * mesh->mNumVertices;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = vertex;

			Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer[m]);

			delete[] vertex;
		}

		// �C���f�b�N�X�o�b�t�@����
		{
			unsigned int* index = new unsigned int[mesh->mNumFaces * 3];

			for (unsigned int f = 0; f < mesh->mNumFaces; f++)
			{
				const aiFace* face = &mesh->mFaces[f];

				assert(face->mNumIndices == 3);

				index[f * 3 + 0] = face->mIndices[0];
				index[f * 3 + 1] = face->mIndices[1];
				index[f * 3 + 2] = face->mIndices[2];
			}

			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(unsigned int) * mesh->mNumFaces * 3;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = index;

			Renderer::GetDevice()->CreateBuffer(&bd, &sd, &indexBuffer[m]);

			delete[] index;
		}

		// �ό`�㒸�_�f�[�^������
		for (unsigned int v = 0; v < mesh->mNumVertices; v++)
		{
			DEFORM_VERTEX DeformVertex;
			DeformVertex.Position = mesh->mVertices[v];
			DeformVertex.Normal   = mesh->mNormals[v];
			DeformVertex.BoneNum  = 0;

			for (unsigned int b = 0; b < 4; b++)
			{
				DeformVertex.BoneName[b] = "";
				DeformVertex.BoneWeight[b] = 0.0f;
			}

			deformVertex[m].push_back(DeformVertex);
		}

		// �{�[���f�[�^������
		for (unsigned int b = 0; b < mesh->mNumBones; b++)
		{
			aiBone* Bone = mesh->mBones[b];

			bone[Bone->mName.C_Str()].OffsetMatrix = Bone->mOffsetMatrix;

			// �ό`�㒸�_�Ƀ{�[���f�[�^�i�[
			for (unsigned int w = 0; w < Bone->mNumWeights; w++)
			{
				aiVertexWeight weight = Bone->mWeights[w];

				int num = deformVertex[m][weight.mVertexId].BoneNum;

				deformVertex[m][weight.mVertexId].BoneWeight[num] = weight.mWeight;
				deformVertex[m][weight.mVertexId].BoneName[num]   = Bone->mName.C_Str();
				deformVertex[m][weight.mVertexId].BoneNum++;

				assert(deformVertex[m][weight.mVertexId].BoneNum <= 4);
			}
		}

		// �e�N�X�`���̓ǂݍ���
		{
			for (unsigned int t = 0; t < aniAiScene->mNumMaterials; t++)
			{
				aiString path;

				// �}�e���A������e�N�X�`�������o��
				// �e�N�X�`���̖��O�� path �ɓ���
				if (aniAiScene->mMaterials[t]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
				{
					if (path.data[0] == '*')
					{
						// FBX�t�@�C������ǂݍ���
						if (texture[path.data] == NULL)
						{
							ID3D11ShaderResourceView* srvTexture;
							int id = atoi(&path.data[1]);

							D3DX11CreateShaderResourceViewFromMemory
							(
								Renderer::GetDevice(),
								(const unsigned char*)aniAiScene->mTextures[id]->pcData,
								aniAiScene->mTextures[id]->mWidth,
								NULL, NULL, &srvTexture, NULL
							);

							texture[path.data] = srvTexture;
						}
					}
					else
					{
						// �O���t�@�C������ǂݍ���
					}
				}
				else
				{
					texture[path.data] = NULL;
				}
			}
		}
	}
}


//!-----------------------------------------------------------
//! @fn         : LoadAnimation(const char *animationFileName, const char* animationName)
//! @brief      : �A�j���[�V�����̃��[�h������
//! @param arg1 : animationFileName...���[�h����A�j���[�V�����̃t�@�C����
//! @param arg2 : animationName.......�A�j���[�V������ݒ肷��ۂ̖��O
//! @return     : �Ȃ�
//! @details    : �t�@�C���̓ǂݍ���
//!-----------------------------------------------------------
void AnimationModel::LoadAnimation(const char *animationFileName, const char* animationName)
{
	// �t�@�C���̓ǂݍ���
	animation[animationName] = aiImportFile(animationFileName, aiProcess_ConvertToLeftHanded);
	assert(animation[animationName]);
}


//!-----------------------------------------------------------
//! @fn      : Unload()
//! @brief   :	���f���̃A�����[�h������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : ���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̉��
//!            ���̑������[�X�������s��
//!-----------------------------------------------------------
void AnimationModel::Unload()
{
	for (unsigned int m = 0; m < aniAiScene->mNumMeshes; m++)
	{
		vertexBuffer[m]->Release();
		indexBuffer[m]->Release();
	}

	delete[] vertexBuffer;
	delete[] indexBuffer;

	delete[] deformVertex;

	for (std::pair<const std::string, ID3D11ShaderResourceView*> pair : texture)
	{
		pair.second->Release();
	}


	aiReleaseImport(aniAiScene);

	//for (std::pair<const std::string, const aniAiScene*> pair : animation)
	//{
	//	aiReleaseImport(pair.second);
	//}
}


//!-----------------------------------------------------------
//! @fn         : Update(const char* animationName, int animationFrame)
//! @brief      : ���f���̍X�V����������
//! @param arg1 : animationName....�ݒ肵���A�j���[�V�����̖��O
//! @param arg2 : animationFrame...�X�V����ۂ̃t���[��
//! @details    : �A�j���[�V�����̍X�V
//!               �Đ��������A�j���[�V�����̖��O�ƍĐ����邽�߂̃t���[���������Ɏg�p
//!-----------------------------------------------------------
void AnimationModel::Update(const char* animationName, int animationFrame)
{
	if (!animation[animationName]->HasAnimations()) return;

	// �A�j���[�V�����f�[�^����{�[���}�g���N�X�Z�o
	aiAnimation* Animation = animation[animationName]->mAnimations[0];

	for (unsigned int c = 0; c < Animation->mNumChannels; c++)
	{
		aiNodeAnim* NodeAnim = Animation->mChannels[c];
		BONE* Bone = &bone[NodeAnim->mNodeName.C_Str()];

		int f;
		f = animationFrame % NodeAnim->mNumRotationKeys; // �ȈՎ���
		aiQuaternion rot = NodeAnim->mRotationKeys[f].mValue;

		f = animationFrame % NodeAnim->mNumPositionKeys; // �ȈՎ���
		aiVector3D pos = NodeAnim->mPositionKeys[f].mValue;

		Bone->AnimationMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), rot, pos);
		//Bone->AnimationMatrix = aiMatrix4x4(aiVector3D(1.0f, 1.0f, 1.0f), rot, VECTOR3D());
	}

	// �ċA�I�Ƀ{�[���}�g���N�X���X�V
	UpdateBoneMatrix(aniAiScene->mRootNode, aiMatrix4x4());

	// ���_�ϊ��iCPU�X�L�j���O�j
	for (unsigned int m = 0; m < aniAiScene->mNumMeshes; m++)
	{
		aiMesh* Mesh = aniAiScene->mMeshes[m];

		D3D11_MAPPED_SUBRESOURCE ms;
		Renderer::GetDeviceContext()->Map(vertexBuffer[m], 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);

		VERTEX_3D* Vertex = (VERTEX_3D*)ms.pData;

		for (unsigned int v = 0; v < Mesh->mNumVertices; v++)
		{
			DEFORM_VERTEX* DeformVertex = &deformVertex[m][v];

			aiMatrix4x4 Matrix[4];
			aiMatrix4x4 OutMatrix;
			Matrix[0] = bone[DeformVertex->BoneName[0]].Matrix;
			Matrix[1] = bone[DeformVertex->BoneName[1]].Matrix;
			Matrix[2] = bone[DeformVertex->BoneName[2]].Matrix;
			Matrix[3] = bone[DeformVertex->BoneName[3]].Matrix;

			// �E�F�C�g���l�����ă}�g���N�X�Z�o
			//OutMatrix = Matrix[0] * DeformVertex->BoneWeight[0]
			//          + Matrix[1] * DeformVertex->BoneWeight[1]
			//          + Matrix[2] * DeformVertex->BoneWeight[2]
			//          + Matrix[3] * DeformVertex->BoneWeight[3];
			{
				OutMatrix.a1 = Matrix[0].a1 * DeformVertex->BoneWeight[0]
					         + Matrix[1].a1 * DeformVertex->BoneWeight[1]
					         + Matrix[2].a1 * DeformVertex->BoneWeight[2]
					         + Matrix[3].a1 * DeformVertex->BoneWeight[3];

				OutMatrix.a2 = Matrix[0].a2 * DeformVertex->BoneWeight[0]
			                 + Matrix[1].a2 * DeformVertex->BoneWeight[1]
			                 + Matrix[2].a2 * DeformVertex->BoneWeight[2]
		 	                 + Matrix[3].a2 * DeformVertex->BoneWeight[3];

				OutMatrix.a3 = Matrix[0].a3 * DeformVertex->BoneWeight[0]
					         + Matrix[1].a3 * DeformVertex->BoneWeight[1]
					         + Matrix[2].a3 * DeformVertex->BoneWeight[2]
					         + Matrix[3].a3 * DeformVertex->BoneWeight[3];

				OutMatrix.a4 = Matrix[0].a4 * DeformVertex->BoneWeight[0]
				         	 + Matrix[1].a4 * DeformVertex->BoneWeight[1]
				         	 + Matrix[2].a4 * DeformVertex->BoneWeight[2]
				         	 + Matrix[3].a4 * DeformVertex->BoneWeight[3];


				OutMatrix.b1 = Matrix[0].b1 * DeformVertex->BoneWeight[0]
					         + Matrix[1].b1 * DeformVertex->BoneWeight[1]
					         + Matrix[2].b1 * DeformVertex->BoneWeight[2]
					         + Matrix[3].b1 * DeformVertex->BoneWeight[3];

				OutMatrix.b2 = Matrix[0].b2 * DeformVertex->BoneWeight[0]
					         + Matrix[1].b2 * DeformVertex->BoneWeight[1]
					         + Matrix[2].b2 * DeformVertex->BoneWeight[2]
					         + Matrix[3].b2 * DeformVertex->BoneWeight[3];

				OutMatrix.b3 = Matrix[0].b3 * DeformVertex->BoneWeight[0]
					         + Matrix[1].b3 * DeformVertex->BoneWeight[1]
					         + Matrix[2].b3 * DeformVertex->BoneWeight[2]
					         + Matrix[3].b3 * DeformVertex->BoneWeight[3];

				OutMatrix.b4 = Matrix[0].b4 * DeformVertex->BoneWeight[0]
					         + Matrix[1].b4 * DeformVertex->BoneWeight[1]
					         + Matrix[2].b4 * DeformVertex->BoneWeight[2]
					         + Matrix[3].b4 * DeformVertex->BoneWeight[3];


				OutMatrix.c1 = Matrix[0].c1 * DeformVertex->BoneWeight[0]
					         + Matrix[1].c1 * DeformVertex->BoneWeight[1]
					         + Matrix[2].c1 * DeformVertex->BoneWeight[2]
					         + Matrix[3].c1 * DeformVertex->BoneWeight[3];

				OutMatrix.c2 = Matrix[0].c2 * DeformVertex->BoneWeight[0]
					         + Matrix[1].c2 * DeformVertex->BoneWeight[1]
					         + Matrix[2].c2 * DeformVertex->BoneWeight[2]
					         + Matrix[3].c2 * DeformVertex->BoneWeight[3];

				OutMatrix.c3 = Matrix[0].c3 * DeformVertex->BoneWeight[0]
					         + Matrix[1].c3 * DeformVertex->BoneWeight[1]
					         + Matrix[2].c3 * DeformVertex->BoneWeight[2]
					         + Matrix[3].c3 * DeformVertex->BoneWeight[3];

				OutMatrix.c4 = Matrix[0].c4 * DeformVertex->BoneWeight[0]
					         + Matrix[1].c4 * DeformVertex->BoneWeight[1]
					         + Matrix[2].c4 * DeformVertex->BoneWeight[2]
					         + Matrix[3].c4 * DeformVertex->BoneWeight[3];


				OutMatrix.d1 = Matrix[0].d1 * DeformVertex->BoneWeight[0]
					         + Matrix[1].d1 * DeformVertex->BoneWeight[1]
					         + Matrix[2].d1 * DeformVertex->BoneWeight[2]
					         + Matrix[3].d1 * DeformVertex->BoneWeight[3];

				OutMatrix.d2 = Matrix[0].d2 * DeformVertex->BoneWeight[0]
					         + Matrix[1].d2 * DeformVertex->BoneWeight[1]
					         + Matrix[2].d2 * DeformVertex->BoneWeight[2]
					         + Matrix[3].d2 * DeformVertex->BoneWeight[3];

				OutMatrix.d3 = Matrix[0].d3 * DeformVertex->BoneWeight[0]
					         + Matrix[1].d3 * DeformVertex->BoneWeight[1]
					         + Matrix[2].d3 * DeformVertex->BoneWeight[2]
					         + Matrix[3].d3 * DeformVertex->BoneWeight[3];

				OutMatrix.d4 = Matrix[0].d4 * DeformVertex->BoneWeight[0]
					         + Matrix[1].d4 * DeformVertex->BoneWeight[1]
					         + Matrix[2].d4 * DeformVertex->BoneWeight[2]
					         + Matrix[3].d4 * DeformVertex->BoneWeight[3];
			}

			DeformVertex->Position = Mesh->mVertices[v];
			DeformVertex->Position *= OutMatrix;

			// �@���Ԋҗp�Ɉړ��������폜
			OutMatrix.a4 = 0.0f;
			OutMatrix.b4 = 0.0f;
			OutMatrix.c4 = 0.0f;

			DeformVertex->Normal = Mesh->mNormals[v];
			DeformVertex->Normal *= OutMatrix;

			// ���_�o�b�t�@�֏�������
			Vertex[v].Position.x = DeformVertex->Position.x;
			Vertex[v].Position.y = DeformVertex->Position.y;
			Vertex[v].Position.z = DeformVertex->Position.z;

			Vertex[v].Normal.x = DeformVertex->Normal.x;
			Vertex[v].Normal.y = DeformVertex->Normal.y;
			Vertex[v].Normal.z = DeformVertex->Normal.z;

			Vertex[v].TexCoord.x = Mesh->mTextureCoords[0][v].x;
			Vertex[v].TexCoord.y = Mesh->mTextureCoords[0][v].y;

			Vertex[v].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		}

		Renderer::GetDeviceContext()->Unmap(vertexBuffer[m], 0);
	}
}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : ���f���̕`�������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �`��ݒ�����ĕ`����s��
//!-----------------------------------------------------------
void AnimationModel::Draw()
{
	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �}�e���A���ݒ�
	MATERIAL setMaterial;
	ZeroMemory(&setMaterial, sizeof(setMaterial));
	setMaterial.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	setMaterial.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(setMaterial);

	for (unsigned int m = 0; m < aniAiScene->mNumMeshes; m++)
	{
		aiMesh* mesh = aniAiScene->mMeshes[m];

		aiMaterial* material = aniAiScene->mMaterials[mesh->mMaterialIndex];

		// �e�N�X�`���ݒ�
		aiString path;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &texture[path.data]);

		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer[m], &stride, &offset);

		// �C���f�b�N�X�o�b�t�@�ݒ�
		Renderer::GetDeviceContext()->IASetIndexBuffer(indexBuffer[m], DXGI_FORMAT_R32_UINT, 0);

		// �|���S���`��
		Renderer::GetDeviceContext()->DrawIndexed(mesh->mNumFaces * 3, 0, 0);
	}

}


//!-----------------------------------------------------------
//! @fn      : CreateBone(aiNode* node)
//! @brief   : �{�[���f�[�^�̍쐬������
//! @param   : node...
//! @return  : �Ȃ�
//! @details : �q���Ȃ��ă{�[�����쐬
//!-----------------------------------------------------------
void AnimationModel::CreateBone(aiNode* node)
{
	BONE Bone;

	bone[node->mName.C_Str()] = Bone;

	for (unsigned int n = 0; n < node->mNumChildren; n++)
	{
		CreateBone(node->mChildren[n]);
	}
}


//!-----------------------------------------------------------
//! @fn         : UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix)
//! @brief      : �{�[���}�g���N�X���X�V������
//! @param arg1 : node.....�C���|�[�g�t�@�C���̃��[�g�m�[�h
//! @param arg2 : matrix...�X�V����{�[���}�g���N�X
//! @details    : �}�g���N�X����Z���ă}�g���N�X���X�V
//!-----------------------------------------------------------
void AnimationModel::UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix)
{
	BONE* Bone = &bone[node->mName.C_Str()];

	// �}�g���N�X�̏�Z���Ԃɒ���
	aiMatrix4x4 WorldMatrix;

	WorldMatrix = matrix;
	WorldMatrix *= Bone->AnimationMatrix;

	Bone->Matrix = WorldMatrix;
	Bone->Matrix *= Bone->OffsetMatrix;

	for (unsigned int n = 0; n < node->mNumChildren; n++)
	{
		UpdateBoneMatrix(node->mChildren[n], WorldMatrix);
	}
}