//!============================================================
//!
//!  @file    : Model.h
//!  @brief   : モデルクラスのヘッダーファイル
//!  @author  : 学校配布のファイル
//!  @details : モデルの実装
//!             アニメーションを使用しないオブジェクトはこのクラスを使用
//!
//!============================================================
#pragma once


//!===========================================================
//! @struct MODEL_MATERIAL
//! @brief   : マテリアル構造体
//!===========================================================
struct MODEL_MATERIAL
{
	char						Name[256];
	MATERIAL					Material;
	char						TextureName[256];
	ID3D11ShaderResourceView*	Texture;
};

//!===========================================================
//! @struct SUBSET
//! @brief   : 描画サブセット構造体
//!===========================================================
struct SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	MODEL_MATERIAL	Material;
};

//!===========================================================
//! @struct MODEL
//! @brief   : モデル構造体
//!===========================================================
struct MODEL
{
	VERTEX_3D		*VertexArray;
	unsigned int	VertexNum;

	unsigned int	*IndexArray;
	unsigned int	IndexNum;

	SUBSET			*SubsetArray;
	unsigned int	SubsetNum;
};


//!===========================================================
//! @class Model
//! @brief   : モデル実装のクラス
//!===========================================================
class Model
{
public:

	//!-------------------------------------------------------
	//! @fn      : Draw()
	//! @brief   : モデルの描画をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 描画設定をして描画を行う
	//!-------------------------------------------------------
	void Draw();

	//!-------------------------------------------------------
	//! @fn      : Load(const char *loadFileName)
	//! @brief   : モデルのロードをする
	//! @param   : loadFileName...ロードするファイルの名前
	//! @return  : なし
	//! @details : ファイルの読み込み
	//!            頂点バッファとインデックスバッファを生成
	//!            サブセット設定
	//!-------------------------------------------------------
	void Load(const char *loadFileName);

	//!-------------------------------------------------------
	//! @fn      : Unload()
	//! @brief   : モデルのアンロードをする
	//! @param   : なし
	//! @return  : なし
	//! @details : 頂点バッファとインデックスバッファの解放
	//!            その他リリース処理を行う
	//!-------------------------------------------------------
	void Unload();

private:

	//!-------------------------------------------------------
	//! @fn         : LoadObj(const char *loadFileName, MODEL *loadModel)
	//! @brief      : モデルの読み込み
	//! @param arg1 : loadFileName....ロードするファイル名
	//! @param arg2 : loadModel.......読み込んだデータから生成したものを格納
	//! @return     : なし
	//! @details    : ファイルの読み込み
	//!               読み込んだファイルからモデルを生成
	//!-------------------------------------------------------
	void LoadObj(const char *loadFileName, MODEL *loadModel);

	//!-------------------------------------------------------
	//! @fn         : LoadMaterial(const char *loadFileName, MODEL_MATERIAL **loadMaterialArray, unsigned int *loadMaterialNum)
	//! @brief      : マテリアル読み込み
	//! @param arg1 : loadFileName............ロードするファイル名
	//! @param arg2 : loadMaterialArray.......読み込んだデータからマテリアルを配置
	//! @param arg3 : loadMaterialNum.........読み込んだデータからマテリアル数を格納
	//! @return     : なし
	//! @details    : ファイルの読み込み
	//!               読み込んだファイルからマテリアルを生成
	//!-------------------------------------------------------
	void LoadMaterial(const char *loadFileName, MODEL_MATERIAL **loadMaterialArray, unsigned int *loadMaterialNum);

	//! 頂点バッファ
	ID3D11Buffer*	m_VertexBuffer;

	//! インデックスバッファ
	ID3D11Buffer*	m_IndexBuffer;

	//! サブセットに使用する変数
	SUBSET*	m_SubsetArray;
	unsigned int	m_SubsetNum;

};