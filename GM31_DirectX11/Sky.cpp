//!============================================================
//!
//!  @file    : Sky.cpp
//!  @brief   : スカイドームクラスのソースファイル
//!  @author  : 原田 陽央
//!  @details : スカイドーム実装のクラス
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
#include "Model.h"
#include "Sky.h"


//============================================================
//　変数宣言
//============================================================
Model* Sky::model;


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
//!            モデルの内側に画像を張りオブジェクトを大きく見せることで表現
//!-----------------------------------------------------------
void Sky::Init()
{
	position = D3DXVECTOR3(0.0f, 0.0f, -6.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale    = D3DXVECTOR3(100.0f, 100.0f, 100.0f);

	// シェーダーの生成
	Renderer::CreateVertexShader(&vertexShader, &vertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&pixelShader, "unlitTexturePS.cso");

	// モデルの生成
	model = Resource::ResourceModelLoad("Asset\\Model\\sky\\sky.obj");
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : 終了処理をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void Sky::Uninit()
{
	
}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : 更新をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void Sky::Update()
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
void Sky::Draw()
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
