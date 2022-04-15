//!============================================================
//!
//!  @file    : Polygon2D.h
//!  @brief   : ポリゴン2Dオブジェクトクラスのヘッダーファイル
//!  @author  : 原田 陽央
//!  @details : 2Dオブジェクトの継承元となるクラス
//!             ゲームオブジェクトクラスを継承
//!
//!============================================================
#pragma once


//============================================================
//　インクルード
//============================================================
#include "GameObject.h"


//!===========================================================
//! @class Polygon2D
//! @brief   : 継承元のポリゴン2Dオブジェクト実装のクラス
//!===========================================================
class Polygon2D : public GameObject
{
public:

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : 初期化をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 初期化と頂点バッファ生成やシェーダーの設定
	//!-------------------------------------------------------
	virtual void Init()
	{
		//〇頂点のデータ打ち込み〇
		//vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		//vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		//vertex[1].Position = D3DXVECTOR3(200.0f, 0.0f, 0.0f);
		//vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		//vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		//vertex[2].Position = D3DXVECTOR3(0.0f, 200.0f, 0.0f);
		//vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		//vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		//vertex[3].Position = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
		//vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		//vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


		//〇頂点バッファ生成〇
		// bdは頂点の設定
		//D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * 4;    // サイズを決める
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // どういうBUFFERなのかをここで設定
		bd.CPUAccessFlags = 0;

		// 初期値を設定してる
		// 今回は先ほど作った頂点のデータを入れてる
		//D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = vertex;

		// ここで頂点バッファを作ってる
		// この関数でIndexもVertexも作れるらしい
		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &vertexBuffer);

		////〇テクスチャの読み込み〇
		//texture = Resource::ResourceTextureLoad("Asset/Texture/renga.jpg");
		////D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(), "Asset/Texture/renga.jpg", NULL, NULL, &texture, NULL);
		//if (texture == NULL)
		//{
		//	return;
		//}

		//// エラーチェック
		//// デバッグのときは無視されるらしい
		//assert(texture);

		//// コンパイル済みのシェーダープログラムをここで読み込む
		//// ※unlitはLightingしないという意味
		//Renderer::CreateVertexShader(&vertexShader, &vertexLayout, "unlitTextureVS.cso");
		//Renderer::CreatePixelShader(&pixelShader, "unlitTexturePS.cso");
	}

	//!-------------------------------------------------------
	//! @fn      : Uninit()
	//! @brief   : 終了処理をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 実装内容なし
	//!-------------------------------------------------------
	virtual void Uninit() {}

	//!-------------------------------------------------------
	//! @fn      : Update()
	//! @brief   : 更新をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 実装内容なし
	//!-------------------------------------------------------
	virtual void Update() {}

	//!-------------------------------------------------------
	//! @fn      : Draw()
	//! @brief   : 描画をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 入力レイアウト設定、シェーダー設定
	//!            マトリクス設定、頂点バッファ設定
	//!            テクスチャ設定、プリミティブトポロジ設定
	//!            ポリゴン描画
	//!            細かい変更がなければ継承したクラスでこの関数を呼び出す
	//!-------------------------------------------------------
	virtual void Draw() 
	{
		// 入力レイアウト設定
		Renderer::GetDeviceContext()->IASetInputLayout(vertexLayout);

		// シェーダー設定
		Renderer::GetDeviceContext()->VSSetShader(vertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(pixelShader, NULL, 0);

		// マトリクス設定
		Renderer::SetWorldViewProjection2D();

		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		// テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &texture);

		// プリミティブトポロジ設定
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}


protected:
	
	VERTEX_3D vertex[4];
	D3D11_BUFFER_DESC bd{};
	D3D11_SUBRESOURCE_DATA sd{};

private:

};