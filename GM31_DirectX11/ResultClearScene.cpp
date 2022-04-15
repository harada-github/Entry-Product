//!============================================================
//!
//!  @file    : ResultClearScene.cpp
//!  @brief   : リザルトクリアシーンクラスのソースファイル
//!  @author  : 原田 陽央
//!  @details : ゲームクリア画面の設定はここで行う
//!
//!============================================================
#pragma once


//============================================================
//　インクルード
//============================================================
#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "Keylogger.h"
#include "GameObject.h"
#include "Resource.h"
#include "ResultClearBG.h"
#include "Fade.h"
#include "ResultClearScene.h"
#include "TitleScene.h"


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
void ResultClearScene::Init()
{
	AddGameObject<ResultClearBG>(OBJECT2D_LAYER);
	AddGameObject<Fade>(OBJECT2D_LAYER);

	// フェードのセット
	Fade::SetFade(1);

	// 変数初期化
	isFade = false;
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : 終了処理をする
//! @param   : なし
//! @return  : なし
//! @details : シーンの終了処理など
//!-----------------------------------------------------------
void ResultClearScene::Uninit()
{
	// 継承元のメソッドの呼び出し
	Scene::Uninit();
}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : 更新をする
//! @param   : なし
//! @return  : なし
//! @details : シーンの更新やキー入力など
//!-----------------------------------------------------------
void ResultClearScene::Update()
{
	// 継承元のメソッドの呼び出し
	Scene::Update();

	// キー入力
	if (Keylogger_Trigger(KL_SPACE) && !isFade)
	{
		// フェードセット
		isFade = true;
		Fade::SetFade(2);
	}

	// フェードが完了したらシーン遷移
	if (isFade && Fade::GetFadeType() == 0)
	{
		Manager::SetScene<TitleScene>();
	}
}

