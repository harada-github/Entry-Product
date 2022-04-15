//!============================================================
//!
//!  @file    : TitleName.cpp
//!  @brief   : タイトル画面のタイトルクラスのソースファイル
//!  @author  : 原田 陽央
//!  @details : タイトル画面のタイトルオブジェクト
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
#include "TitleName.h"


//============================================================
//　関数
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : 初期化をする
//! @param   : なし
//! @return  : なし
//! @details : 変数の初期化
//!            頂点データの打ち込み
//!            テクスチャの読み込み
//!            シェーダーの設定
//!-----------------------------------------------------------
void TitleName::Init()
{
	// 変数の初期化
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	mass = 1.0f;
	tension.x = 0.0f;
	tension.y = 0.0f;
	deltaTime = 0.03f;
	position.x = SCREEN_WIDTH  / 2;
	position.y = SCREEN_HEIGHT / 2 - 300.0f;

	// 頂点のデータ打ち込み
	vertex[0].Position = D3DXVECTOR3(position.x - SCREEN_WIDTH / 5 * 2, position.y - SCREEN_HEIGHT / 5 * 2, 0.0f);
	vertex[0].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(position.x + SCREEN_WIDTH / 5 * 2, position.y - SCREEN_HEIGHT / 5 * 2, 0.0f);
	vertex[1].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(position.x - SCREEN_WIDTH / 5 * 2, position.y + SCREEN_HEIGHT / 5 * 2, 0.0f);
	vertex[2].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(position.x + SCREEN_WIDTH / 5 * 2, position.y + SCREEN_HEIGHT / 5 * 2, 0.0f);
	vertex[3].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	// テクスチャの読み込み
	texture = Resource::ResourceTextureLoad("Asset/Texture/フシギのダンジョン.png");

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
void TitleName::Uninit()
{

}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : 更新をする
//! @param   : なし
//! @return  : なし
//! @details : 張力、重力、抵抗から加速値を求めて
//!            その値から座標を更新する
//!-----------------------------------------------------------
void TitleName::Update()
{
	// 張力
	tension.x = (640.0f - position.x) * 2.0f;
	tension.y = (300.0f - position.y) * 2.0f;

	// 重力
	tension.y += 9.8f * mass;

	// 抵抗
	tension.x -= velocity.x * 0.6f;
	tension.y -= velocity.y * 0.6f;

	// 張力による加速
	velocity.x += (tension.x / mass) * deltaTime;
	velocity.y += (tension.y / mass) * deltaTime;

	// 移動
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;

	// 座標の更新
	vertex[0].Position = D3DXVECTOR3(position.x - SCREEN_WIDTH / 5 * 2, position.y - SCREEN_HEIGHT / 5 * 2, 0.0f);
	vertex[1].Position = D3DXVECTOR3(position.x + SCREEN_WIDTH / 5 * 2, position.y - SCREEN_HEIGHT / 5 * 2, 0.0f);
	vertex[2].Position = D3DXVECTOR3(position.x - SCREEN_WIDTH / 5 * 2, position.y + SCREEN_HEIGHT / 5 * 2, 0.0f);
	vertex[3].Position = D3DXVECTOR3(position.x + SCREEN_WIDTH / 5 * 2, position.y + SCREEN_HEIGHT / 5 * 2, 0.0f);
	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);
}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : 描画をする
//! @param   : なし
//! @return  : なし
//! @details : 継承元のDraw関数の呼び出し
//!-----------------------------------------------------------
void TitleName::Draw()
{
	// 継承元のメソッドを呼び出す
	Polygon2D::Draw();
}
