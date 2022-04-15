//!============================================================
//!
//!  @file    : Scene.h
//!  @brief   : シーンクラスのヘッダーファイル
//!  @author  : 原田 陽央
//!  @details : タイトルシーンやゲームシーンの継承元のクラス
//!             ゲームオブジェクトの管理を行う
//!
//!============================================================
#pragma once


//============================================================
//　インクルード
//============================================================
#include <list>
#include <vector>
#include <typeinfo>
#include "GameObject.h"
#include "Camera.h"


//!===========================================================
//! @enum Layer
//! @brief   : レイヤー列挙体
//!===========================================================
enum Layer
{
	CAMERA_LAYER,          // カメラ
	NO_ZSORT_OBJECT_LAYER, // Zソートをしない3Dオブジェクト
	OBJECT3D_LAYER,        // 3Dオブジェクト
	OBJECT2D_LAYER,        // 2Dオブジェクト
	LAYER_COUNT            // レイヤー数
};


//!===========================================================
//! @class Scene
//! @brief   : 継承元のシーンクラス
//!===========================================================
class Scene
{
public:

	//!-------------------------------------------------------
	//! @fn      : Scene()
	//! @brief   : コンストラクタ
	//! @param   : なし
	//! @return  : なし
	//! @details : 実装内容なし
	//!-------------------------------------------------------
	Scene(){}

	//!-------------------------------------------------------
	//! @fn      : ~Scene()
	//! @brief   : デストラクタ
	//! @param   : なし
	//! @return  : なし
	//! @details : 純粋仮想関数
	//!-------------------------------------------------------
	virtual ~Scene(){}

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : 初期化をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 純粋仮想関数
	//!-------------------------------------------------------
	virtual void Init() = 0;

	//!-------------------------------------------------------
	//! @fn      : Uninit()
	//! @brief   : 終了処理をする
	//! @param   : なし
	//! @return  : なし
	//! @details : オブジェクトの解放とリストのクリアを行う
	//!-------------------------------------------------------
	virtual void Uninit()
	{
		for (int i = 0; i < LAYER_COUNT; i++)
		{
			for (GameObject* object : gameObject[i])
			{
				object->Uninit();
				delete object;
			}

			// リストのクリア
			gameObject[i].clear();
		}
	}

	//!-------------------------------------------------------
	//! @fn      : Update()
	//! @brief   : 更新処理をする
	//! @param   : なし
	//! @return  : なし
	//! @details : オブジェクトの更新処理と解放予約したオブジェクトの解放をする
	//!-------------------------------------------------------
	virtual void Update()
	{
		for (int i = 0; i < LAYER_COUNT; i++)
		{
			// 範囲forループ
			for (GameObject* object : gameObject[i])
			{
				object->Update();
			}

			// ラムダ式
			gameObject[i].remove_if([](GameObject* object) {return object->Destroy(); });
		}
	}

	//!-------------------------------------------------------
	//! @fn      : Draw()
	//! @brief   : 描画処理をする
	//! @param   : なし
	//! @return  : なし
	//! @details : オブジェクトの描画処理
	//!-------------------------------------------------------
	virtual void Draw()
	{
		// Zソート（カメラの座標を基準にして近い順にオブジェクトをソート）
		gameObject[OBJECT3D_LAYER].sort
		(
			[this](GameObject* object1, GameObject* object2)
			{
				// カメラオブジェクトを保持
				GameObject* cameraObject = GetGameObject<Camera>(CAMERA_LAYER);

				// object1 と cameraObject との差を計算
				float o1XDis = cameraObject->GetPosition().x - object1->GetPosition().x;
				float o1YDis = cameraObject->GetPosition().y - object1->GetPosition().y;
				float o1ZDis = cameraObject->GetPosition().z - object1->GetPosition().z;

				// object2 と cameraObject との差を計算
				float o2XDis = cameraObject->GetPosition().x - object2->GetPosition().x;
				float o2YDis = cameraObject->GetPosition().y - object2->GetPosition().y;
				float o2ZDis = cameraObject->GetPosition().z - object2->GetPosition().z;

				// それぞれの座標の二乗を比較して
				// object1の方がcameraObjectに近い場合 true を返す
				return (o1XDis * o1XDis + o1YDis * o1YDis + o1ZDis * o1ZDis) > (o2XDis * o2XDis + o2YDis * o2YDis + o2ZDis * o2ZDis);
			}
		);

		// 描画
		for (int i = 0; i < LAYER_COUNT; i++)
		{
			for (GameObject* object : gameObject[i])
			{
				object->Draw();
			}
		}
	}

	//!-------------------------------------------------------
	//! @fn      : AddGameObject(int Layer)
	//! @brief   : オブジェクトの追加をする
	//! @param   : Layer...レイヤーの番号
	//!            0はカメラ、1は3Dオブジェクト、2は2Dオブジェクト
	//! @return  : 追加したゲームオブジェクト
	//! @details : オブジェクトの追加処理（テンプレート関数）
	//!-------------------------------------------------------
	template <typename T>
	T* AddGameObject(int Layer)
	{
		T* addGameObject = new T();
		addGameObject->Init();
		gameObject[Layer].push_back(addGameObject);

		return addGameObject;
	}

	//!-------------------------------------------------------
	//! @fn      : GetGameObject(int Layer)
	//! @brief   : 単体のオブジェクトの情報を取得する
	//! @param   : Layer...レイヤーの番号
	//!            0はカメラ、1は3Dオブジェクト、2は2Dオブジェクト
	//! @return  : 取得したオブジェクト、取得できない場合はNULLを返す
	//! @details : 単体オブジェクトの情報取得（テンプレート関数）
	//!-------------------------------------------------------
	template <typename T>
	T* GetGameObject(int Layer)
	{
		for (GameObject* object : gameObject[Layer])
		{
			if (typeid(*object) == typeid(T)) // 型を調べる（RTTI動的型情報）
			{
				return (T*)object;
			}
		}

		return NULL;
	}

	//!-------------------------------------------------------
	//! @fn      : GetGameObjects(int Layer)
	//! @brief   : 複数のオブジェクトの情報を取得する
	//! @param   : Layer...レイヤーの番号
	//!            0はカメラ、1は3Dオブジェクト、2は2Dオブジェクト
	//! @return  : 取得したオブジェクト
	//! @details : 複数オブジェクトの情報取得（テンプレート関数）
	//!-------------------------------------------------------
	template <typename T>
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*> objects; // STLの配列
		for (GameObject* object : gameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}

		return objects;
	}

protected:

	//! ゲームオブジェクトを格納するリストの変数（STLのリスト構造）
	std::list<GameObject*> gameObject[LAYER_COUNT];
};
