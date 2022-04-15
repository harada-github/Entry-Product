//!============================================================
//!
//!  @file    : StaminaBar.cpp
//!  @brief   : スタミナのゲージバークラスのソースファイル
//!  @author  : 原田 陽央
//!  @details : スタミナのゲージバーのオブジェクト
//!             ポリゴン2Dクラスを継承
//!
//!============================================================
#pragma once


//============================================================
//　インクルード
//============================================================
#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "Resource.h"
#include "StaminaBar.h"
#include "Scene.h"
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
//! @details : 頂点データの打ち込み
//!            テクスチャの読み込み
//!            シェーダーの設定
//!-----------------------------------------------------------
void StaminaBar::Init()
{
	// シーンの情報の取得
	scene = Manager::GetScene();

	//〇頂点のデータ打ち込み〇
	vertex[0].Position = D3DXVECTOR3(850.0f, 70.0f, 0.0f);
	vertex[0].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(1250.0f, 70.0f, 0.0f);
	vertex[1].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(850.0f, 110.0f, 0.0f);
	vertex[2].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(1250.0f, 110.0f, 0.0f);
	vertex[3].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	// テクスチャの読み込み
	texture = Resource::ResourceTextureLoad("Asset/Texture/bg_white.jpg");

	// エラーチェック
	if (texture == NULL)
	{
		return;
	}
	assert(texture);

	// コンパイル済みのシェーダープログラムをここで読み込む
	Renderer::CreateVertexShader(&vertexShader, &vertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&pixelShader, "unlitTexturePS.cso");

	// 継承元のメソッドを呼び出す
	Polygon2D::Init();
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : 終了処理をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void StaminaBar::Uninit()
{

}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : 更新をする
//! @param   : なし
//! @return  : なし
//! @details : プレイヤーのスタミナを取得して
//!            算出した割合によってゲージの幅を変更する
//!-----------------------------------------------------------
void StaminaBar::Update()
{
	// プレイヤーのスタミナを表示するタイプの場合の処理
	if (barType == 1)
	{
		// プレイヤーの情報を取得
		DungeonPlayer* dungeonPlayer = scene->GetGameObject<DungeonPlayer>(OBJECT3D_LAYER);

		// プレイヤーのスタミナから割合を算出
		float staminaPercent = dungeonPlayer->GetHitPoint() / 100.0f;

		// ゲージバーを更新
		vertex[0].Position = D3DXVECTOR3(850.0f, 70.0f, 0.0f);
		vertex[1].Position = D3DXVECTOR3(850.0f + (staminaPercent * 400.0f), 70.0f, 0.0f);
		vertex[2].Position = D3DXVECTOR3(850.0f, 110.0f, 0.0f);
		vertex[3].Position = D3DXVECTOR3(850.0f + (staminaPercent * 400.0f), 110.0f, 0.0f);

		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f);

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);
	}
}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : 描画をする
//! @param   : なし
//! @return  : なし
//! @details : 継承元のDraw関数の呼び出し
//!-----------------------------------------------------------
void StaminaBar::Draw()
{
	// 継承元のメソッドを呼び出す
	Polygon2D::Draw();
}


//!-----------------------------------------------------------
//! @fn      : SetBarType()
//! @brief   : ゲージバーのタイプの設定
//! @param   : setBarType
//! @return  : なし
//! @details : 引数からゲージバーのタイプの設定
//!-----------------------------------------------------------
void StaminaBar::SetBarType(int setBarType)
{
	barType = setBarType;
}
