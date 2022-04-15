//!============================================================
//!
//!  @file    : Stair.cpp
//!  @brief   : 階段クラスのソースファイル
//!  @author  : 原田 陽央
//!  @details : 階段クラスの実装
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
#include "Resource.h"
#include "GameScene.h"
#include "Model.h"
#include "Stair.h"


//============================================================
//　変数宣言
//============================================================
// スタティックメンバ変数はcppで再度宣言が必要
Model* Stair::model;


//============================================================
//　関数
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : 初期化をする
//! @param   : なし
//! @return  : なし
//! @details : 初期化処理
//!            モデルの生成
//!            シェーダーの設定
//!-----------------------------------------------------------
void Stair::Init()
{
	// 変数初期化
	position = D3DXVECTOR3(0.0f, 0.0f, 5.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// シェーダーの生成
	Renderer::CreateVertexShader(&vertexShader, &vertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&pixelShader, "vertexLightingPS.cso");

	// モデルの生成
	//model = Resource::ResourceModelLoad("Asset\\Model\\item\\GM31_5.obj");
	model = Resource::ResourceModelLoad("Asset\\Model\\stair\\GM31_6.obj");
	//model = Resource::ResourceModelLoad("Asset\\Model\\riceball\\GM31_7.obj");
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : 終了処理をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void Stair::Uninit()
{
	
}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : 更新をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void Stair::Update()
{
	
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
void Stair::Draw()
{
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
	model->Draw();
}
