//!============================================================
//!
//!  @file    : Fade.cpp
//!  @brief   : フェードクラスのソースファイル
//!  @author  : 原田 陽央
//!  @details : 画面のフェードを行うフェードオブジェクトの実装
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
#include "Fade.h"


//============================================================
//　変数宣言
//============================================================
int Fade::fadeType;
float Fade::fadeAlpha;


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
void Fade::Init()
{
	// 変数初期化
	fadeType = 0;
	fadeAlpha = 0.0f;

	// 頂点のデータ打ち込み
	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	vertex[1].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	vertex[2].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	vertex[3].Normal   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
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
void Fade::Uninit()
{
	
}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : 更新をする
//! @param   : なし
//! @return  : なし
//! @details : アルファの値を変化させて
//!            フェードイン・アウトの実装を行う
//!-----------------------------------------------------------
void Fade::Update()
{
	if (fadeType == 0)
	{

	}
	else if (fadeType == 1)
	{
		fadeAlpha -= 0.01f;

		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);
	}
	else if (fadeType == 2)
	{
		fadeAlpha += 0.01f;

		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, fadeAlpha);
		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);
	}

	if (fadeAlpha >= 1.05f || fadeAlpha <= -0.05f)
	{
		fadeType = 0;
	}
}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : 描画をする
//! @param   : なし
//! @return  : なし
//! @details : @details : 継承元のDraw関数の呼び出し
//!-----------------------------------------------------------
void Fade::Draw()
{
	// 継承元のメソッドを呼び出す
	Polygon2D::Draw();
}


//!-----------------------------------------------------------
//! @fn      : SetFade(int type)
//! @brief   : フェードのセット
//! @param   : type.....フェードのタイプ
//! @return  : なし
//! @details : 外部的にフェードのセットする際に使用
//!            画面が白くなる、白い状態から通常の画面になるフェード
//!            type が1ならフェードイン、2ならフェードアウト
//!-----------------------------------------------------------
void Fade::SetFade(int type)
{
	fadeType = type;

	if (fadeType == 0)
	{
		
	}
	else if (fadeType == 1)
	{
		fadeAlpha = 1.0f;
	}
	else if (fadeType == 2)
	{
		fadeAlpha = 0.0f;
	}
}


//!-----------------------------------------------------------
//! @fn      : GetFadeType()
//! @brief   : フェードのタイプの取得
//! @param   : なし
//! @return  : type（現在のフェードのタイプ）
//! @details : 現在のフェードのタイプを取得する
//!-----------------------------------------------------------
int Fade::GetFadeType()
{
	return fadeType;
}
