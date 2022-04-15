//!============================================================
//!
//!  @file    : HitPointBar.h
//!  @brief   : ヒットポイントのゲージバークラスのヘッダーファイル
//!  @author  : 原田 陽央
//!  @details : ヒットポイントのゲージバーのオブジェクト
//!             ポリゴン2Dクラスを継承
//!
//!============================================================
#pragma once


//============================================================
//　インクルード
//============================================================
#include "Polygon2D.h"


//!===========================================================
//! @class HitPointBar
//! @brief   : ヒットポイントのゲージバー実装のクラス
//!===========================================================
class HitPointBar : public Polygon2D
{
public:

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : 初期化をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 頂点データの打ち込み
	//!            テクスチャの読み込み
	//!            シェーダーの設定
	//!-------------------------------------------------------
	void Init();

	//!-------------------------------------------------------
	//! @fn      : Uninit()
	//! @brief   : 終了処理をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 実装内容なし
	//!-------------------------------------------------------
	void Uninit();

	//!-------------------------------------------------------
	//! @fn      : Update()
	//! @brief   : 更新をする
	//! @param   : なし
	//! @return  : なし
	//! @details : プレイヤーのヒットポイントを取得して
	//!            算出した割合によってゲージの幅を変更する
	//!-------------------------------------------------------
	void Update();

	//!-------------------------------------------------------
	//! @fn      : Draw()
	//! @brief   : 描画をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 継承元のDraw関数の呼び出し
	//!-------------------------------------------------------
	void Draw();

	//!-------------------------------------------------------
	//! @fn      : SetBarType()
	//! @brief   : ゲージバーのタイプの設定
	//! @param   : setBarType
	//! @return  : なし
	//! @details : 引数からゲージバーのタイプの設定
	//!-------------------------------------------------------
	void SetBarType(int setBarType);

private:

	//! バーのタイプ（現在は一種類のみ）
	int barType;

};