//!============================================================
//!
//!  @file    : GameScene.cpp
//!  @brief   : ゲームシーンクラスのソースファイル
//!  @author  : 原田 陽央
//!  @details : ゲームの大まかなものはここで行う
//!
//!============================================================
#pragma once


//============================================================
//　インクルード
//============================================================
#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Resource.h"
#include "Camera.h"
#include "Audio.h"
#include "DungeonField.h"
#include "DungeonMap.h"
#include "Model.h"
#include "Sky.h"
#include "Fade.h"
#include "GameScene.h"
#include "ResultClearScene.h"
#include "ResultOverScene.h"
#include "StaminaBar.h"
#include "HitPointBar.h"
#include "DungeonPlayer.h"
#include "DungeonEnemy.h"


//============================================================
//　変数宣言
//============================================================
static Audio* bgm;
bool GameScene::isFade;
int GameScene::resultType;


//============================================================
//　関数
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : 初期化をする
//! @param   : なし
//! @return  : なし
//! @details : オブジェクトの配置などはここで行う
//!-----------------------------------------------------------
void GameScene::Init()
{
	// 変数初期化
	isFade = false;
	resultType = 0;

	// オブジェクトの配置
	// ダンジョンマップ
	AddGameObject<DungeonMap>(OBJECT3D_LAYER);
	AddGameObject<Camera>(CAMERA_LAYER);
	AddGameObject<HitPointBar>(OBJECT2D_LAYER)->SetBarType(0);
	AddGameObject<HitPointBar>(OBJECT2D_LAYER)->SetBarType(1);
	AddGameObject<StaminaBar>(OBJECT2D_LAYER)->SetBarType(0);
	AddGameObject<StaminaBar>(OBJECT2D_LAYER)->SetBarType(1);
	AddGameObject<DungeonField>(OBJECT3D_LAYER);
	AddGameObject<DungeonPlayer>(OBJECT3D_LAYER);

	AddGameObject<DungeonEnemy>(OBJECT3D_LAYER);
	AddGameObject<DungeonEnemy>(OBJECT3D_LAYER);
	AddGameObject<DungeonEnemy>(OBJECT3D_LAYER);
	AddGameObject<DungeonEnemy>(OBJECT3D_LAYER);
	AddGameObject<DungeonEnemy>(OBJECT3D_LAYER);
	
	AddGameObject<Sky>(NO_ZSORT_OBJECT_LAYER);
	AddGameObject<Fade>(OBJECT2D_LAYER);


	// BGMのロード
	bgm = Resource::ResourceAudioLoad("Asset\\Sound\\gm.wav");

	// BGMの再生
	bgm->Play(true);

	// フェードのセット
	Fade::SetFade(1);
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : 終了処理をする
//! @param   : なし
//! @return  : なし
//! @details : シーンの終了処理など
//!-----------------------------------------------------------
void GameScene::Uninit()
{
	bgm->Stop();

	Scene::Uninit();
}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : 更新をする
//! @param   : なし
//! @return  : なし
//! @details : シーンの更新やキー入力など
//!-----------------------------------------------------------
void GameScene::Update()
{
	Scene::Update();

	// フェードが完了したらシーン遷移
	if (isFade && Fade::GetFadeType() == 0)
	{
		if (resultType == 0)
		{
			Manager::SetScene<ResultClearScene>();
		}
		else if (resultType == 1)
		{
			Manager::SetScene<ResultOverScene>();
		}
	}
}


//!-----------------------------------------------------------
//! @fn      : SetResult(int type)
//! @brief   : リザルトシーンの移動セット
//! @param   : type...リザルトのタイプ
//!            0ならゲームクリア画面 1ならゲームオーバー画面
//! @return  : なし
//! @details : リザルトタイプやフェードの設定を入れる
//!            Game::SetResult(0)のように使用する
//!-----------------------------------------------------------
void GameScene::SetResult(int type)
{
	// フェード中ならreturn
	if (isFade)return;

	// リザルトのタイプを設定
	resultType = type;

	// フェードオン
	isFade = true;
	Fade::SetFade(2);
}
