//!============================================================
//!
//!  @file    : DungeonField.cpp
//!  @brief   : ダンジョン内フィールドクラスのソースファイル
//!  @author  : 原田 陽央
//!  @details : ダンジョンフィールド描画の実装
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
#include "DungeonField.h"
#include "DungeonMapData.h"


//============================================================
//　変数宣言
//============================================================



//============================================================
//　関数
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : 初期化をする
//! @param   : なし
//! @return  : なし
//! @details : 初期化と頂点バッファ生成やシェーダーの設定
//!-----------------------------------------------------------
void DungeonField::Init()
{
	//〇頂点のデータ打ち込み〇
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-DUNGEON_MAP_DATA_X - 1.0f, 0.0f, DUNGEON_MAP_DATA_Z + 1.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(DUNGEON_MAP_DATA_X - 1.0f, 0.0f, DUNGEON_MAP_DATA_Z + 1.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2((float)DUNGEON_MAP_DATA_X / 4, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-DUNGEON_MAP_DATA_X - 1.0f, 0.0f, -DUNGEON_MAP_DATA_Z + 1.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, (float)DUNGEON_MAP_DATA_Z / 4);

	vertex[3].Position = D3DXVECTOR3(DUNGEON_MAP_DATA_X - 1.0f, 0.0f, -DUNGEON_MAP_DATA_Z + 1.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2((float)DUNGEON_MAP_DATA_X / 4, (float)DUNGEON_MAP_DATA_Z / 4);


	//〇頂点バッファ生成〇
	// bdは頂点の設定
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;    // サイズを決める
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // どういうBUFFERなのかをここで設定
	bd.CPUAccessFlags = 0;

	// 初期値を設定してる
	// 今回は先ほど作った頂点のデータを入れてる
	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	// ここで頂点バッファを作ってる
	// この関数でIndexもVertexも作れるらしい
	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);

	//〇テクスチャの読み込み〇
 	texture = Resource::ResourceTextureLoad("Asset/Texture/field2.jpg");

	// エラーチェック
	assert(texture);

	// シェーダーの読み込み
	Renderer::CreateVertexShader(&vertexShader, &vertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&pixelShader, "vertexLightingPS.cso");

	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : 終了処理をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void DungeonField::Uninit()
{

}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : 更新をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void DungeonField::Update()
{

}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : 描画をする
//! @param   : なし
//! @return  : なし
//! @details : 入力レイアウト設定、シェーダー設定
//!            マトリクス設定、頂点バッファ設定
//!            テクスチャ設定、プリミティブトポロジ設定
//!            ポリゴン描画
//!-----------------------------------------------------------
void DungeonField::Draw()
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

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);
}
