//!============================================================
//!
//!  @file    : Manager.h
//!  @brief   : マネージャークラスのヘッダーファイル
//!  @author  : 原田 陽央
//!  @details : マネージャークラスの実装
//!             シーンの管理
//!             ゲームの大まかな管理を行う
//!
//!============================================================
#pragma once


//!===========================================================
//! @class Manager
//! @brief   : マネージャー実装のクラス
//!===========================================================
class Manager
{
public:

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : 初期化をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 初期化処理
	//!-------------------------------------------------------
	static void Init();

	//!-------------------------------------------------------
	//! @fn      : Uninit()
	//! @brief   : 終了処理をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 終了処理
	//!-------------------------------------------------------
	static void Uninit();

	//!-------------------------------------------------------
	//! @fn      : Update()
	//! @brief   : 更新をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 更新処理
	//!-------------------------------------------------------
	static void Update();

	//!-------------------------------------------------------
	//! @fn      : Draw()
	//! @brief   : 描画をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 描画処理
	//!-------------------------------------------------------
	static void Draw();

	//!-------------------------------------------------------
	//! @fn      : GetScene()
	//! @brief   : 現在のシーンを取得する
	//! @param   : なし
	//! @return  : 現在のシーン情報
	//! @details : 現在のシーンを返す
	//!-------------------------------------------------------
	static class Scene* GetScene()
	{
		return scene;
	}

	//!-------------------------------------------------------
	//! @fn      : SetScene()
	//! @brief   : シーンを設定する
	//! @param   : なし
	//! @return  : なし
	//! @details : シーンを設定する（テンプレート関数）
	//!            Manager::SetScene<シーンクラス名>()のように使用する
	//!-------------------------------------------------------
	template <typename T>
	static void SetScene()
	{
		if (scene)
		{
			scene->Uninit();
			delete scene;
		}

		scene = new T();
		scene->Init();
	}

private:

	//! 現在のシーンを格納
	static class Scene* scene;
};