//!============================================================
//!
//!  @file    : Manager.cpp
//!  @brief   : マネージャークラスのソースファイル
//!  @author  : 原田 陽央
//!  @details : マネージャークラスの実装
//!             シーンの管理
//!             ゲームの大まかな管理を行う
//!
//!============================================================
#pragma once
#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "Resource.h"
#include "Keyboard.h"
#include "Keylogger.h"
#include "Audio.h"
#include "Scene.h"
#include "GameScene.h"
#include "TitleScene.h"



//============================================================
//　変数宣言
//============================================================
Scene* Manager::scene = NULL;


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
void Manager::Init()
{
	// レンダラーの初期化
	Renderer::Init();

	// キーボードの初期化
	Keyboard_Initialize();

	// キーローガーの初期化
	Keylogger_Initialize();

	// オーディオの初期化
	Audio::InitMaster();

	// リソースの初期化
	Resource::Init();

	// シーンの初期化
	scene = new TitleScene();
	scene->Init();
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : 終了処理をする
//! @param   : なし
//! @return  : なし
//! @details : 終了処理
//!-----------------------------------------------------------
void Manager::Uninit()
{
	// シーンの終了
	scene->Uninit();
	delete scene;

	// リソースの終了
	Resource::Uninit();

	// オーディオの終了
	Audio::UninitMaster();

	// キーロガーキーの終了処理
	Keylogger_Finalize();

	// レンダラーの終了
	Renderer::Uninit();
}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : 更新をする
//! @param   : なし
//! @return  : なし
//! @details : 更新処理
//!-----------------------------------------------------------
void Manager::Update()
{
	// キーロガーキーの更新
	Keylogger_Update();

	// シーンの更新
	scene->Update();
}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : 描画をする
//! @param   : なし
//! @return  : なし
//! @details : 描画処理
//!-----------------------------------------------------------
void Manager::Draw()
{
	Renderer::Begin();

	// シーンの描画
	scene->Draw();

	Renderer::End();
}
