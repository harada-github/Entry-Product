//!============================================================
//!
//!  @file    : Block.cpp
//!  @brief   : ブロッククラスのソースファイル
//!  @author  : 原田 陽央
//!  @details : ブロックの実装
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
#include "Scene.h"
#include "Camera.h"
#include "Model.h"
#include "Block.h"


//============================================================
//　変数宣言
//============================================================
Model* Block::model;


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
void Block::Init()
{
	// 変数初期化
	position = D3DXVECTOR3(0.0f, 0.0f, 5.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 0.5f, 1.0f);

	isDraw = false;
	
	// シェーダーの生成
	Renderer::CreateVertexShader(&vertexShader, &vertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&pixelShader, "vertexLightingPS.cso");

	// モデルの生成
	model = Resource::ResourceModelLoad("Asset\\Model\\block\\GM31_4.obj");
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : 終了処理をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void Block::Uninit()
{
	
}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : 更新をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void Block::Update()
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
void Block::Draw()
{
	// 視錐台カリング
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(CAMERA_LAYER);
	
	if (!camera->CheckView(position))
	{
		return;
	}

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


//!-----------------------------------------------------------
//! @fn      : SetIsDraw(bool setIsDraw)
//! @brief   : 描画をするか銅貨を変更
//! @param   : setIsDraw...trueまたはfalse
//! @return  : なし
//! @details : 引数が true なら描画を有効
//!                   false なら描画を無効   
//!-----------------------------------------------------------
void Block::SetIsDraw(bool setIsDraw)
{
	isDraw = setIsDraw;
}
