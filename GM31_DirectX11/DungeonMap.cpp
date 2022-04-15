//!============================================================
//!
//!  @file    : DungeonMap.cpp
//!  @brief   : ダンジョンマップ生成クラスのソースファイル
//!  @author  : 原田 陽央
//!  @details : ダンジョンマップ生成の実装
//!
//!============================================================
#pragma once


//============================================================
//　インクルード
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
//　変数宣言
//============================================================
static Scene* scene = NULL;


//============================================================
//　関数
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : 初期化をする
//! @param   : なし
//! @return  : なし
//! @details : 初期化処理
//!-----------------------------------------------------------
void DungeonMap::Init()
{
	// シーンの情報の取得
	scene = Manager::GetScene();

	// ダンジョンマップのセット
	// マップ
	dungeonMapData.SetMapData();
	// 階段
	dungeonMapData.SetStair();
	// ブロックの配置
	SetBlock();
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : 終了処理をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void DungeonMap::Uninit()
{

}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : 更新をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void DungeonMap::Update()
{
	
}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : 描画をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void DungeonMap::Draw()
{
	
}


//!-----------------------------------------------------------
//! @fn      : SetBlock()
//! @brief   : 描画をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
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
//! @brief      : 中心座標の取得
//! @param arg1 : xNumber...取得したい中心座標のX（横）番号
//! @param arg2 : zNumber...取得したい中心座標のZ（縦）番号
//! @return     : xNumberとzNumberに対応した中心座標
//! @details    : xNumberとzNumberに対応した中心座標のを返す
//!-----------------------------------------------------------
D3DXVECTOR3 DungeonMap::GetCenterPosition(int xNumber, int zNumber) const
{
	return dungeonMapData.GetCenterPosition(xNumber, zNumber);
}


//!-----------------------------------------------------------
//! @fn         : IsMapDataMove(int xNumber, int zNumber) const
//! @brief      : 進むことができるマスかどうかを返す
//! @param arg1 : xNumber...取得したい中心座標のX（横）番号
//! @param arg2 : zNumber...取得したい中心座標のZ（縦）番号
//! @return     : 進むことができるマスかどうか
//! @details    : xNumberとzNumberに対応したマップ情報が
//!               壁の場合はfalseを返す
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
//! @brief   : ゲームクリア画面のセット
//! @param   : なし
//! @return  : なし
//! @details : 
//!-----------------------------------------------------------
void DungeonMap::SetGameClear()
{
	// ゲームオーバー画面へ
	GameScene::SetResult(0);
}


//!-----------------------------------------------------------
//! @fn      : SetGameOver()
//! @brief   : ゲームオーバー画面のセット
//! @param   : なし
//! @return  : なし
//! @details : 
//!-----------------------------------------------------------
void DungeonMap::SetGameOver()
{
	// ゲームオーバー画面へ
	GameScene::SetResult(1);
}
