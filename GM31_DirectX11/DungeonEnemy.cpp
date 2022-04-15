//!============================================================
//!
//!  @file    : DungeonEnemy.cpp
//!  @brief   : エネミークラスのソースファイル
//!  @author  : 原田 陽央
//!  @details : エネミークラスの実装
//!             ゲームオブジェクトクラスを継承
//!
//!============================================================
#pragma once


//============================================================
//　インクルード
//============================================================
#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "Scene.h"
#include "GameScene.h"
#include "Resource.h"
#include "Keylogger.h"
#include "Camera.h"
#include "DungeonEnemy.h"
#include "DungeonMap.h"
#include "Block.h"
#include "Stair.h"


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
//!            アニメーションモデルの生成
//!            シェーダーの設定
//!            シーンの情報の取得
//!            使用するオーディオのロード
//!-----------------------------------------------------------
void DungeonEnemy::Init()
{
	// シーンの情報の取得
	scene = Manager::GetScene();

	// ダンジョンマップの取得
	dungeonMap = scene->GetGameObject<DungeonMap>(OBJECT3D_LAYER);

	// 変数初期化
	xMapNumber = xPreMapNumber = 0;
	zMapNumber = zPreMapNumber = 0;

	// ステータス初期化
	hitPoint = 100.0f;

	// プレイヤーの位置をランダムに設定
	// 橋の壁を考慮した乱数を生成
	int mapDataX = (rand() % DUNGEON_MAP_DATA_X - 2) + 1;
	int mapDataZ = (rand() % DUNGEON_MAP_DATA_Z - 2) + 1;

	// 生成した乱数に対応した位置がプレイヤーを設定できる場所になるまで、乱数を生成する
	while (!dungeonMap->IsMapDataMove(mapDataX, mapDataZ))
	{
		mapDataX = (rand() % DUNGEON_MAP_DATA_X - 2) + 1;
		mapDataZ = (rand() % DUNGEON_MAP_DATA_Z - 2) + 1;
	}

	// 変数初期化
	xMapNumber = xPreMapNumber = mapDataX;
	zMapNumber = zPreMapNumber = mapDataZ;


	// 設定する位置を返す
	position = dungeonMap->GetCenterPosition(mapDataX, mapDataZ);

	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(0.02f, 0.02f, 0.02f);
	move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	isMove = false;
	aniFrame = 0;
	aniType = 1;

	// シェーダーの生成
	Renderer::CreateVertexShader(&vertexShader, &vertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&pixelShader, "vertexLightingPS.cso");

	// モデルの生成
	aniModel = Resource::ResourceAnimationModelLoad("Asset\\Model\\enemy\\Idle5.fbx");
	aniModel->LoadAnimation("Asset\\Model\\enemy\\Idle5.fbx", "Idle");
	aniModel->LoadAnimation("Asset\\Model\\enemy\\Mutant Walking.fbx", "Walking");
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : 終了処理をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void DungeonEnemy::Uninit()
{

}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : 更新をする
//! @param   : なし
//! @return  : なし
//! @details : キー入力での移動
//!            他オブジェクトとの当たり判定
//!            アニメーションモデルの更新
//!-----------------------------------------------------------
void DungeonEnemy::Update()
{
	// 移動している間の処理
	if (isMove)
	{
		// 移動フレームを更新
		moveFrame++;

		// 座標を更新
		position += move;

		// アニメーションの設定
		aniType = 2;
	}
	if (moveFrame >= moveFrameMax)
	{
		// 移動後の処理
		AfterMoveProcess();
	}
	else
	{
		aniType = 1;
	}


	// アニメーションフレームの更新
	aniFrame++;

#ifndef _DEBUG

	// リリース時のみアニメーション
	switch (aniType)
	{
	case 0:

		break;

	case 1:
		aniModel->Update("Idle", aniFrame);
		break;

	case 2:
		aniModel->Update("Walking", aniFrame);
		break;

	case 3:
		aniModel->Update("Attack", aniFrame);
		break;

	case 4:
		aniModel->Update("Down", aniFrame);
		break;

	default:
		break;
	}

#endif

}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : 描画をする
//! @param   : なし
//! @return  : なし
//! @details : シェーダーの設定
//!            マトリクスの設定
//!            モデルの描画
//!-----------------------------------------------------------
void DungeonEnemy::Draw()
{
	// 視錐台カリング
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(0);
	
	if (!camera->CheckView(position))
	{
		return;
	}

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(vertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(vertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(pixelShader, NULL, 0);

	// マトリクス設定
	D3DXMATRIX World, Scale, Rotate, Trans;
	D3DXMatrixScaling(&Scale, this->scale.x, this->scale.y, this->scale.z);
	D3DXMatrixRotationYawPitchRoll(&Rotate, this->rotation.y, this->rotation.x, this->rotation.z);
	D3DXMatrixTranslation(&Trans, this->position.x, this->position.y, this->position.z);
	World = Scale * Rotate * Trans;
	Renderer::SetWorldMatrix(&World);

	// モデルの描画
	aniModel->Draw();
}



//!-----------------------------------------------------------
//! @fn      : SetMoveVector(int type)
//! @brief   : 移動方向のセット
//! @param   : type...移動したい方向のタイプ
//! @return  : なし
//! @details : 移動したい方向の設定の実装
//!            type が0なら前、1なら後ろ
//!            2なら右、3なら左
//!            4なら右前、5なら左前
//!            6なら右後、7なら左後方向に設定
//!-----------------------------------------------------------
void DungeonEnemy::SetMoveVector(int type)
{
	// 移動中ならreturn
	if (isMove)
	{
		return;
	}

	// 前
	xPreMapNumber = xMapNumber;
	zPreMapNumber = zMapNumber;


	switch (type)
	{
		// 前移動
	case 0:
		if (zMapNumber < DUNGEON_MAP_DATA_Z - 1)
		{
			zMapNumber--;
			rotation = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
		}
		break;

		// 後移動
	case 1:
		if (zMapNumber > 0)
		{
			zMapNumber++;
			rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		break;

		// 右移動
	case 2:
		if (xMapNumber < DUNGEON_MAP_DATA_X - 1)
		{
			xMapNumber++;
			rotation = D3DXVECTOR3(0.0f, 4.71f, 0.0f);
		}
		break;

		// 左移動
	case 3:
		if (xMapNumber > 0)
		{
			xMapNumber--;
			rotation = D3DXVECTOR3(0.0f, 1.57f, 0.0f);
		}
		break;

		// 右前移動
	case 4:
		if (xMapNumber < DUNGEON_MAP_DATA_X - 1 && zMapNumber < DUNGEON_MAP_DATA_Z - 1)
		{
			xMapNumber++;
			zMapNumber--;
			rotation = D3DXVECTOR3(0.0f, 3.925f, 0.0f);
		}
		break;

		// 左前移動
	case 5:
		if (xMapNumber > 0 && zMapNumber < DUNGEON_MAP_DATA_Z - 1)
		{
			xMapNumber--;
			zMapNumber--;
			rotation = D3DXVECTOR3(0.0f, 2.355f, 0.0f);
		}
		break;

		// 右後移動
	case 6:
		if (xMapNumber < DUNGEON_MAP_DATA_X - 1 && zMapNumber > 0)
		{
			xMapNumber++;
			zMapNumber++;
			rotation = D3DXVECTOR3(0.0f, 5.495f, 0.0f);
		}
		break;

		// 左後移動
	case 7:
		if (xMapNumber > 0 && zMapNumber > 0)
		{
			xMapNumber--;
			zMapNumber++;
			rotation = D3DXVECTOR3(0.0f, 0.785f, 0.0f);
		}
		break;

	default:
		break;
	}


	// 進みたいマスが壁ならreturn
	if (!dungeonMap->IsMapDataMove(xMapNumber, zMapNumber))
	{
		xMapNumber = xPreMapNumber;
		zMapNumber = zPreMapNumber;
		return;
	}

	// 変数の調整
	move = (dungeonMap->GetCenterPosition(xMapNumber, zMapNumber) - dungeonMap->GetCenterPosition(xPreMapNumber, zPreMapNumber)) / moveFrameMax;
	aniType = 2;
	isMove = true;

}


//!-----------------------------------------------------------
//! @fn      : GetHitPoint()
//! @brief   : プレイヤーのヒットポイントを取得する
//! @param   : なし
//! @return  : なし
//! @details : 
//!-----------------------------------------------------------
float DungeonEnemy::GetHitPoint()
{
	return hitPoint;
}


//!-----------------------------------------------------------
//! @fn      : AfterMoveProcess()
//! @brief   : 次のマスへ移動した後の処理
//! @param   : なし
//! @return  : なし
//! @details : 
//!-----------------------------------------------------------
void DungeonEnemy::AfterMoveProcess()
{
	// 移動に使用した変数のリセット
	isMove = false;
	moveFrame = 0;

	// プレイヤーの座標をマップの座標に合わせて調整
	position = dungeonMap->GetCenterPosition(xMapNumber, zMapNumber);

	// 前座標の保存
	prePosition = position;

	// プレイヤーのヒットポイントを減らす
	hitPoint -= 0.5f;
}
