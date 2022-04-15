//!============================================================
//!
//!  @file    : Camera.cpp
//!  @brief   : カメラクラスのソースファイル
//!  @author  : 原田 陽央
//!  @details : カメラの実装
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
#include "Keylogger.h"
#include "GameScene.h"
#include "Model.h"
#include "DungeonPlayer.h"
#include "Camera.h"


//============================================================
//　関数
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : 初期化をする
//! @param   : なし
//! @return  : なし
//! @details : 初期化とベクトルの正規化
//!-----------------------------------------------------------
void Camera::Init()
{
	// 変数の初期化
	position      = D3DXVECTOR3(0.0f, 10.0f, -13.0f);
	vecFront      = D3DXVECTOR3(0.0f, -0.5f,   1.0f);
	vecSide       = D3DXVECTOR3(1.0f,  0.0f,   0.0f);
	vecUp         = D3DXVECTOR3(0.0f,  1.0f,   0.0f);
	target        = D3DXVECTOR3(0.0f,  0.0f,   0.0f);
	vecTemp       = D3DXVECTOR3(0.0f,  0.0f,   0.0f);
	vecPlayerView = D3DXVECTOR3(0.0f, 8.0f, -5.0f);

	player = nullptr;

	moveSpeed   = 0.3f;
	rotateSpeed = 0.02f;

	rotateAt = false;

	cameraType = CAMERA_Dungeon_PLAYER;

	// 前方向ベクトルと右方向ベクトルと直角になる上方向ベクトルを算出
	D3DXVec3Cross(&vecUp, &vecFront, &vecSide);

	// 各ベクトルを正規化（長さ１に）する
	D3DXVec3Normalize(&vecFront, &vecFront);
	D3DXVec3Normalize(&vecSide, &vecSide);
	D3DXVec3Normalize(&vecUp, &vecUp);

	D3DXMatrixIdentity(&viewMatrix);

	// カメラの初期位置をなおす
	target = position + vecFront;
	D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &vecUp);
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : 終了処理をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void Camera::Uninit()
{

}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : 更新をする
//! @param   : なし
//! @return  : なし
//! @details : キー入力によるカメラのタイプの変更
//!            キー入力によるカメラの移動
//!            タイプによって実装の変更
//!-----------------------------------------------------------
void Camera::Update()
{
#ifdef _DEBUG
	// デバッグ時カメラのタイプを変更可能
	// カメラのタイプを変化
	if (Keylogger_Trigger(KL_0))
	{
		cameraType = CAMERA_DEBUG;
	}
	else if (Keylogger_Trigger(KL_1))
	{
		cameraType = CAMERA_FIXED;
	}
	else if (Keylogger_Trigger(KL_2))
	{
		cameraType = CAMERA_PLAYER;
	}
	else if (Keylogger_Trigger(KL_3))
	{
		cameraType = CAMERA_Dungeon_PLAYER;
	}

#endif

	switch (cameraType)
	{
	case CAMERA_DEBUG:
	// CAMERA_DEBUG時のカメラ制御
	    // 前
		if (Keylogger_Press(KL_W))
		{
			CameraKeyInput(KL_W);
		}
		// 後ろ
		if (Keylogger_Press(KL_S))
		{
			CameraKeyInput(KL_S);
		}
		// 右
		if (Keylogger_Press(KL_D))
		{
			CameraKeyInput(KL_D);
		}
		// 左
		if (Keylogger_Press(KL_A))
		{
			CameraKeyInput(KL_A);
		}
		// 上
		if (Keylogger_Press(KL_E))
		{
			CameraKeyInput(KL_E);
		}
		// 下
		if (Keylogger_Press(KL_Q))
		{
			CameraKeyInput(KL_Q);
		}
		// 右回転
		if (Keylogger_Press(KL_TURN_RIGHT))
		{
			CameraKeyInput(KL_TURN_RIGHT);
		}
		// 左回転
		if (Keylogger_Press(KL_TURN_LEFT))
		{
			CameraKeyInput(KL_TURN_LEFT);
		}
		// 注視点回転オンオフ
		if (Keylogger_Press(KL_LEFTSHIFT))
		{
			rotateAt = true;
		}
		else
		{
			rotateAt = false;
		}

		// 注視点を算出する
		target = position + vecFront;

		// ビュー行列の作成
		D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &vecUp);

		break;


	case CAMERA_FIXED:
		// CAMERA_FIXED時のカメラ制御
		// 変数の初期化
		position = D3DXVECTOR3(0.0f, 80.0f, 0.0f);

		// 注視点の設定
		target   = D3DXVECTOR3(0.0f,  0.0f, 0.0f);

		// ビュー行列の作成
		D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &vecUp);

		break;


	case CAMERA_PLAYER:
	   
		break;

	case CAMERA_Dungeon_PLAYER:
		// CAMERA_Dungeon_PLAYER時のカメラ制御
		player = Manager::GetScene()->GetGameObject<DungeonPlayer>(OBJECT3D_LAYER);
		target = player->GetPosition();

		// 注視点からポジションを算出
		position = target + vecPlayerView;

		// ビュー行列の作成
		D3DXMatrixLookAtLH(&viewMatrix, &position, &target, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		break;

	default:
		break;
	}
}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : 描画をする
//! @param   : なし
//! @return  : なし
//! @details : ビューマトリクス設定
//!            プロジェクションマトリクス設定
//!            ニアとファーの値の設定
//!-----------------------------------------------------------
void Camera::Draw()
{
	// ビューマトリクス設定
	Renderer::SetViewMatrix(&viewMatrix);

	// 最後二つはニアとファーの値
	if (cameraType == CAMERA_Dungeon_PLAYER)
	{
		D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 500.0f);
	}
	else
	{
		D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
	}
	
	Renderer::SetProjectionMatrix(&projectionMatrix);

}


//!-----------------------------------------------------------
//! @fn      : Camera_GetViewMatrix()
//! @brief   : カメラのビュー行列の取得
//! @param   : なし
//! @return  : カメラのビュー行列
//! @details : カメラのビュー行列を返す
//!-----------------------------------------------------------
D3DXMATRIX Camera::Camera_GetViewMatrix() const
{
	return viewMatrix;
}


//!-----------------------------------------------------------
//! @fn      : CheckView(D3DXVECTOR3 objectPosition)
//! @brief   : 視錐台カリングの実装
//! @param   : objectPosition...チェックしたいオブジェクトの座標
//! @return  : 設定した視錐台の範囲内にオブジェクトがあるかどうか
//! @details : 変数に指定したオブジェクト座標が
//!            視錐台の範囲内にあるかをチェックして
//!            存在する場合には true を返す
//!-----------------------------------------------------------
bool Camera::CheckView(D3DXVECTOR3 objectPosition)
{
	// 変数を用意
	D3DXMATRIX vp, invvp;
	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];
	D3DXVECTOR3 v, v1, v2, n[4];

	vp = viewMatrix * projectionMatrix;

	D3DXMatrixInverse(&invvp, NULL, &vp);

	// 視錐台の奥の頂点を生成
	if (cameraType == CAMERA_Dungeon_PLAYER)
	{
		vpos[0] = D3DXVECTOR3(-1.2f,  1.2f, 1.0f);
		vpos[1] = D3DXVECTOR3( 1.2f,  1.2f, 1.0f);
		vpos[2] = D3DXVECTOR3( 1.2f, -1.3f, 1.0f);
		vpos[3] = D3DXVECTOR3(-1.2f, -1.3f, 1.0f);
	}
	else
	{
		vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
		vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		vpos[2] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
		vpos[3] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	}
	

	// 変換
	for (int i = 0; i < 4; i++)
	{
		D3DXVec3TransformCoord(&wpos[i], &vpos[i], &invvp);
	}

	// 対象のオブジェクトとカメラのポジションの差分を保存
	v = objectPosition - position;

	// 判定の計算 視錐台の外の場合はfalseを返す
	for (int i = 0; i < 4; i++)
	{
		// 視錐台の上の面の情報から n の配列に格納していく
		if (i == 3)
		{
			// i が３のときのみの処理
			v1 = wpos[0] - position;
		}
		else
		{
			v1 = wpos[i + 1] - position;
		}

		v2 = wpos[i] - position;

		// 外積を計算
		D3DXVec3Cross(&n[i], &v1, &v2);

		// 結果の符号がマイナスの場合はfalseを返す
		if (D3DXVec3Dot(&n[i], &v) < 0.0f)
		{
			return false;
		}
	}

	return true;
}


//!-----------------------------------------------------------
//! @fn      : CheckOnlyCameraMove()
//! @brief   : カメラのみが可動できるカメラタイプかどうかのチェック
//! @param   : なし
//! @return  : カメラのみが可動できる状態かどうか
//! @details : カメラのみが可動できるカメラタイプかどうかを
//!            チェックしてその可否を返す
//!            カメラのみが動けるタイプの場合は true
//!            カメラが動けないタイプの場合は　 false
//!-----------------------------------------------------------
bool Camera::CheckOnlyCameraMove()
{
	if (cameraType == CAMERA_DEBUG)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//!-----------------------------------------------------------
//! @fn      : CameraKeyInput(KeyloggerKey keyType)
//! @brief   : キー入力の際のカメラ制御
//! @param   : keyType...入力されたキーのタイプ
//! @return  : なし
//! @details : 前後左右上下の移動と回転の実装
//!            押されたキーに対しての移動や回転を行う
//!-----------------------------------------------------------
void Camera::CameraKeyInput(KeyloggerKey keyType)
{
	//if (cameraType != CAMERA_DEBUG) return;

	// WまたはSが押されたとき（前後）
	if (keyType == KL_W || keyType == KL_S)
	{
		// 移動方向以外を０にして正規化
		vecTemp = vecFront;
		vecTemp.y = 0.0f;
		D3DXVec3Normalize(&vecTemp, &vecTemp);

		// 座標更新
		keyType == KL_W ?  position += (vecTemp * moveSpeed) : position -= (vecTemp * moveSpeed);
	}

	// DまたはAが押されたとき（左右）
	if (keyType == KL_D || keyType == KL_A)
	{
		// 移動方向以外を０にして正規化
		vecTemp = vecSide;
		D3DXVec3Normalize(&vecTemp, &vecTemp);

		// 座標更新
		keyType == KL_D ? position += (vecTemp * moveSpeed) : position -= (vecTemp * moveSpeed);
	}

	// EまたはQが押されたとき（上下）
	if (keyType == KL_E || keyType == KL_Q)
	{
		// 移動方向以外を０にして正規化
		vecTemp = vecUp;
		vecTemp.x = 0.0f;
		vecTemp.z = 0.0f;
		D3DXVec3Normalize(&vecTemp, &vecTemp);

		// 座標更新
		keyType == KL_E ? position += (vecTemp * moveSpeed) : position -= (vecTemp * moveSpeed);
	}

	// →または←が押されたとき（回転）
	if (keyType == KL_TURN_RIGHT || keyType == KL_TURN_LEFT)
	{
		// 右と左で変化
		keyType == KL_TURN_RIGHT ? D3DXMatrixRotationY(&mtxTempR, rotateSpeed) : D3DXMatrixRotationY(&mtxTempR, -rotateSpeed);

		// それぞれのベクトルを回転
		D3DXVec3TransformNormal(&vecFront, &vecFront, &mtxTempR);
		D3DXVec3TransformNormal(&vecSide, &vecSide, &mtxTempR);
		D3DXVec3TransformNormal(&vecUp, &vecUp, &mtxTempR);

	}
}
