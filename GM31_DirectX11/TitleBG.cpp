//!============================================================
//!
//!  @file    : TitleBG.cpp
//!  @brief   : タイトル画面の背景オブジェクトクラスのソースファイル
//!  @author  : 原田 陽央
//!  @details : タイトル画面の背景オブジェクト
//!             ポリゴン2Dクラスクラスを継承
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
#include "TitleBG.h"


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
void TitleBG::Init()
{
	//〇頂点のデータ打ち込み〇
	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	vertex[1].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	vertex[2].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	vertex[3].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	//〇テクスチャの読み込み〇
	texture = Resource::ResourceTextureLoad("Asset/Texture/TitleBG.png");

	// エラーチェック
	if (texture == NULL)
	{
		return;
	}

	assert(texture);

	//〇コンパイル済みシェーダープログラムの読み込み〇
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
void TitleBG::Uninit()
{
	
}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : 更新をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void TitleBG::Update()
{

}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : 描画をする
//! @param   : なし
//! @return  : なし
//! @details : 継承元のDraw関数の呼び出し
//!-----------------------------------------------------------
void TitleBG::Draw()
{
	// 継承元のメソッドを呼び出す
	Polygon2D::Draw();
}
