//!============================================================
//!
//!  @file    : GameObject.h
//!  @brief   : ゲームオブジェクトクラスのヘッダーファイル
//!  @author  : 原田 陽央
//!  @details : ゲームオブジェクトクラスの実装
//!             ゲームで使用するオブジェクトクラスの継承元となるクラス
//!             仮想クラスとして実装
//!
//!============================================================
#pragma once


//!===========================================================
//! @class GameObject
//! @brief   : ゲームオブジェクトクラス
//!===========================================================
class GameObject
{
public:

	//!-------------------------------------------------------
	//! @fn      : GameObject()
	//! @brief   : コンストラクタ
	//! @param   : なし
	//! @return  : なし
	//! @details : 実装内容なし
	//!-------------------------------------------------------
	GameObject() {}

	//!-------------------------------------------------------
	//! @fn      : ~GameObject()
	//! @brief   : デストラクタ
	//! @param   : なし
	//! @return  : なし
	//! @details : シェーダーやテクスチャの設定に使用する変数の解放
	//!-------------------------------------------------------
	~GameObject() {} 

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : 初期化をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 純粋仮想関数
	//!-------------------------------------------------------
	virtual void Init() = 0;

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : 終了処理をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 純粋仮想関数
	//!-------------------------------------------------------
	virtual void Uninit() = 0;

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : 更新をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 純粋仮想関数
	//!-------------------------------------------------------
	virtual void Update() = 0;

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : 描画をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 純粋仮想関数
	//!-------------------------------------------------------
	virtual void Draw() = 0;

	//!-------------------------------------------------------
	//! @fn      : GetPosition()
	//! @brief   : ゲームオブジェクトの座標の取得
	//! @param   : なし
	//! @return  : ゲームオブジェクトの座標
	//! @details : ゲームオブジェクトの座標を返す
	//!-------------------------------------------------------
	D3DXVECTOR3 GetPosition()
	{
		return position;
	}


	//!-------------------------------------------------------
	//! @fn      : GetObbX()
	//! @brief   : ゲームオブジェクトのOBBのX座標の取得
	//! @param   : なし
	//! @return  : ゲームオブジェクトのOBBのX座標
	//! @details : ゲームオブジェクトのOBBのX座標を返す
	//!-------------------------------------------------------
	D3DXVECTOR3 GetObbX()
	{
		D3DXMATRIX obbRot, obbScale, obbWorld;
		D3DXMatrixScaling(&obbScale, scale.x, scale.y, scale.z);
		D3DXMatrixRotationYawPitchRoll(&obbRot, rotation.y, rotation.x, rotation.z);
		obbWorld = obbScale * obbRot;

		D3DXVECTOR3 vx;
		vx.x = obbWorld._11;
		vx.y = obbWorld._12;
		vx.z = obbWorld._13;

		return vx * 0.5f;
	}


	//!-------------------------------------------------------
	//! @fn      : GetObbZ()
	//! @brief   : ゲームオブジェクトのOBBのZ座標の取得
	//! @param   : なし
	//! @return  : ゲームオブジェクトのOBBのZ座標
	//! @details : ゲームオブジェクトのOBBのZ座標を返す
	//!-------------------------------------------------------
	D3DXVECTOR3 GetObbZ()
	{
		D3DXMATRIX obbRot, obbScale, obbWorld;
		D3DXMatrixScaling(&obbScale, scale.x, scale.y, scale.z);
		D3DXMatrixRotationYawPitchRoll(&obbRot, rotation.y, rotation.x, rotation.z);
		obbWorld = obbScale * obbRot;

		D3DXVECTOR3 vz;
		vz.x = obbWorld._31;
		vz.y = obbWorld._32;
		vz.z = obbWorld._33;

		return vz * 0.5f;
	}


	//!-------------------------------------------------------
	//! @fn      : SetPosition()
	//! @brief   : ゲームオブジェクトの座標の取得
	//! @param   : setPosition...設定したい座標
	//! @return  : なし
	//! @details : ゲームオブジェクトの座標を設定
	//!-------------------------------------------------------
	void SetPosition(D3DXVECTOR3 setPosition)
	{
		position = setPosition;
	}

	//!-------------------------------------------------------
	//! @fn      : SetDestroy()
	//! @brief   : ゲームオブジェクトの消去予約
	//! @param   : なし
	//! @return  : なし
	//! @details : destroy を true にしてオブジェクト解放の予約をする
	//!-------------------------------------------------------
	void SetDestroy()
	{
		destroy = true;
	}

	//!-------------------------------------------------------
	//! @fn      : Destroy()
	//! @brief   : ゲームオブジェクトの消去予約
	//! @param   : なし
	//! @return  : ゲームオブジェクトを解放できたかどうか
	//! @details : destroy が true ならゲームオブジェクトを解放する
	//!-------------------------------------------------------
	bool Destroy()
	{
		if (destroy)
		{
			// 解放処理
			//if (texture != NULL) texture->Release();
			if (vertexBuffer != NULL) vertexBuffer->Release();
			if (indexBuffer != NULL) indexBuffer->Release();

			if (vertexLayout != NULL) vertexLayout->Release();
			if (vertexShader != NULL) vertexShader->Release();
			if (pixelShader != NULL) pixelShader->Release();

			// 終了処理
			Uninit();

			// オブジェクトの解放
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}


protected:

	//! オブジェクトの座標
	D3DXVECTOR3 position;
	//! オブジェクトの回転
	D3DXVECTOR3 rotation;
	//! オブジェクトの大きさ
	D3DXVECTOR3 scale;

	bool active;
	//! オブジェクトの解放予約用
	bool destroy = false;

	// 頂点シェーダー
	ID3D11VertexShader* vertexShader;  
	// ピクセルシェーダー
	ID3D11PixelShader*  pixelShader;   
	// 頂点のレイアウト
	ID3D11InputLayout*  vertexLayout;  

	// 頂点データ
	ID3D11Buffer*              vertexBuffer = NULL;  
	// インデックスデータ
	ID3D11Buffer*              indexBuffer = NULL;   
	// テクスチャデータ
	ID3D11ShaderResourceView*  texture = NULL;       
};