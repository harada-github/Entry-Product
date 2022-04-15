//!============================================================
//!
//!  @file    : DungeonMap.cpp
//!  @brief   : �_���W�����}�b�v�����N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �_���W�����}�b�v�����̎���
//!
//!============================================================
#pragma once


//============================================================
//�@�C���N���[�h
//============================================================
#include "Main.h"
#include "Manager.h"
#include "Scene.h"
#include "GameScene.h"
#include "Renderer.h"
#include "Resource.h"
#include "DungeonMap.h"
#include "Block.h"
#include "Stair.h"
#include "DungeonPlayer.h"


//============================================================
//�@�ϐ��錾
//============================================================
static Scene* scene = NULL;


//============================================================
//�@�֐�
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : ������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : ����������
//!-----------------------------------------------------------
void DungeonMap::Init()
{
	// �V�[���̏��̎擾
	scene = Manager::GetScene();

	// �_���W�����}�b�v�̃Z�b�g
	// �}�b�v
	dungeonMapData.SetMapData();
	// �K�i
	dungeonMapData.SetStair();
	// �u���b�N�̔z�u
	SetBlock();
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : �I������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void DungeonMap::Uninit()
{

}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void DungeonMap::Update()
{
	
}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : �`�������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void DungeonMap::Draw()
{
	
}


//!-----------------------------------------------------------
//! @fn      : SetBlock()
//! @brief   : �`�������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void DungeonMap::SetBlock()
{
	for (int j = 0; j < DUNGEON_MAP_DATA_Z; j++)
	{
		for (int i = 0; i < DUNGEON_MAP_DATA_X; i++)
		{
			if (dungeonMapData.GetMapDataNumber(i, j) == MAP_WALL)
			{
				scene->AddGameObject<Block>(OBJECT3D_LAYER)->SetPosition(dungeonMapData.GetCenterPosition(i, j));
			}

			if (dungeonMapData.GetMapDataNumber(i, j) == MAP_STAIR)
			{
				scene->AddGameObject<Stair>(OBJECT3D_LAYER)->SetPosition(dungeonMapData.GetCenterPosition(i, j));
			}
		}
	}
}


//!-----------------------------------------------------------
//! @fn         : GetCenterPosition(int xNumber, int zNumber) const
//! @brief      : ���S���W�̎擾
//! @param arg1 : xNumber...�擾���������S���W��X�i���j�ԍ�
//! @param arg2 : zNumber...�擾���������S���W��Z�i�c�j�ԍ�
//! @return     : xNumber��zNumber�ɑΉ��������S���W
//! @details    : xNumber��zNumber�ɑΉ��������S���W�̂�Ԃ�
//!-----------------------------------------------------------
D3DXVECTOR3 DungeonMap::GetCenterPosition(int xNumber, int zNumber) const
{
	return dungeonMapData.GetCenterPosition(xNumber, zNumber);
}


//!-----------------------------------------------------------
//! @fn         : IsMapDataMove(int xNumber, int zNumber) const
//! @brief      : �i�ނ��Ƃ��ł���}�X���ǂ�����Ԃ�
//! @param arg1 : xNumber...�擾���������S���W��X�i���j�ԍ�
//! @param arg2 : zNumber...�擾���������S���W��Z�i�c�j�ԍ�
//! @return     : �i�ނ��Ƃ��ł���}�X���ǂ���
//! @details    : xNumber��zNumber�ɑΉ������}�b�v���
//!               �ǂ̏ꍇ��false��Ԃ�
//!-----------------------------------------------------------
bool DungeonMap::IsMapDataMove(int xNumber, int zNumber)
{
	if (dungeonMapData.GetMapDataNumber(xNumber, zNumber) == MAP_WALL)
	{
		return false;
	}

	return true;
}


//!-----------------------------------------------------------
//! @fn      : SetGameClear()
//! @brief   : �Q�[���N���A��ʂ̃Z�b�g
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : 
//!-----------------------------------------------------------
void DungeonMap::SetGameClear()
{
	// �Q�[���I�[�o�[��ʂ�
	GameScene::SetResult(0);
}


//!-----------------------------------------------------------
//! @fn      : SetGameOver()
//! @brief   : �Q�[���I�[�o�[��ʂ̃Z�b�g
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : 
//!-----------------------------------------------------------
void DungeonMap::SetGameOver()
{
	// �Q�[���I�[�o�[��ʂ�
	GameScene::SetResult(1);
}
