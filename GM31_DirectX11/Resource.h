//!============================================================
//!
//!  @file    : Resource.h
//!  @brief   : リソースクラスのヘッダーファイル
//!  @author  : 原田 陽央
//!  @details : リソース関連の管理の実装
//!
//!============================================================
#pragma once


//============================================================
//　インクルード
//============================================================
#include "Model.h"
#include "AnimationModel.h"
#include "Audio.h"


//!===========================================================
//! @def TEXTURE_MAX
//! @brief   : テクスチャ最大管理数
//!
//! @def MODEL_MAX
//! @brief   : モデル最大管理数
//!
//! @def ANIMATIONMODEL_MAX
//! @brief   : アニメーションモデル最大管理数
//!
//! @def AUDIO_MAX
//! @brief   : オーディオ最大管理数
//!===========================================================
#define TEXTURE_MAX          (10)
#define MODEL_MAX            (10)
#define ANIMATIONMODEL_MAX   (10)
#define AUDIO_MAX            (10)


//!===========================================================
//! @struct ResourceTextureData
//! @brief   : テクスチャデータ管理構造体
//!===========================================================
struct ResourceTextureData
{
	ID3D11ShaderResourceView* textureData;
	char fileName[256];
	int id;
};

//!===========================================================
//! @struct ResourceModelData
//! @brief   : モデルデータ管理構造体
//!===========================================================
struct ResourceModelData
{
	Model* modelData;
	char fileName[256];
	int id;
};

//!===========================================================
//! @struct ResourceAnimationModelData
//! @brief   : アニメーションモデルデータ管理構造体
//!===========================================================
struct ResourceAnimationModelData
{
	AnimationModel* aniModelData;
	char fileName[256];
	int id;
};


//!===========================================================
//! @struct ResourceAudioData
//! @brief   : オーディオデータ管理構造体
//!===========================================================
struct ResourceAudioData
{
	Audio* audioData;
	char fileName[256];
	int id;
};



//!===========================================================
//! @class Resource
//! @brief   : リソース関連の管理の実装のクラス
//!===========================================================
class Resource
{
public:

	//!-------------------------------------------------------
	//! @fn      : Resource()
	//! @brief   : コンストラクタ
	//! @param   : なし
	//! @return  : なし
	//! @details : 実装内容なし
	//!-------------------------------------------------------
	Resource(){}

	//!-------------------------------------------------------
	//! @fn      : ~Resource()
	//! @brief   : デストラクタ
	//! @param   : なし
	//! @return  : なし
	//! @details : 実装内容なし
	//!-------------------------------------------------------
	~Resource(){}

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : 初期化をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 初期化とメモリ確保
	//!-------------------------------------------------------
	static void Init();

	//!-------------------------------------------------------
	//! @fn      : Uninit()
	//! @brief   : 終了処理をする
	//! @param   : なし
	//! @return  : なし
	//! @details : データとメモリ解放
	//!-------------------------------------------------------
	static void Uninit();

	//!-------------------------------------------------------
	//! @fn      : ResourceTextureLoad(const char* loadFileName)
	//! @brief   : テクスチャのロードをする
	//! @param   : loadFileName...ロードするファイルの名前
	//! @return  : ロード済みまたはロードしたデータを返す
	//! @details : テクスチャのロードを実装
	//!　          テクスチャをロード済みかどうかチェック
    //!　          ロード済みならそのデータを返す
    //!　          そうでない場合はロードしてそのデータを返す
	//!-------------------------------------------------------
	static ID3D11ShaderResourceView* ResourceTextureLoad(const char* loadFileName);

	//!-------------------------------------------------------
	//! @fn      : ResourceModelLoad(const char* loadFileName)
	//! @brief   : モデルのロードをする
	//! @param   : loadFileName...ロードするファイルの名前
	//! @return  : ロード済みまたはロードしたデータを返す
	//! @details : モデルのロードを実装
	//!　          モデルをロード済みかどうかチェック
	//!　          ロード済みならそのデータを返す
	//!　          そうでない場合はロードしてそのデータを返す
	//!-------------------------------------------------------
	static Model* ResourceModelLoad(const char* loadFileName);

	//!-------------------------------------------------------
	//! @fn      : ResourceAnimationModelLoad(const char* loadFileName)
	//! @brief   : アニメーションモデルのロードをする
	//! @param   : loadFileName...ロードするファイルの名前
	//! @return  : ロード済みまたはロードしたデータを返す
	//! @details : アニメーションモデルのロードを実装
	//!　          アニメーションモデルをロード済みかどうかチェック
	//!　          ロード済みならそのデータを返す
	//!　          そうでない場合はロードしてそのデータを返す
	//!-------------------------------------------------------
	static AnimationModel* ResourceAnimationModelLoad(const char* loadFileName);

	//!-------------------------------------------------------
	//! @fn      : ResourceAudioLoad(const char* loadFileName)
	//! @brief   : オーディオデータのロードをする
	//! @param   : loadFileName...ロードするファイルの名前
	//! @return  : ロード済みまたはロードしたデータを返す
	//! @details : オーディオデータのロードを実装
	//!　          オーディオデータをロード済みかどうかチェック
	//!　          ロード済みならそのデータを返す
	//!　          そうでない場合はロードしてそのデータを返す
	//!-------------------------------------------------------
	static Audio* ResourceAudioLoad(const char* loadFileName);

private:

	//! テクスチャデータ関連変数
	static ResourceTextureData*  resourceTextureData;
	static int resourceTextureCount;

	//! モデルデータ関連変数
	static ResourceModelData* resourceModelData;
	static int resourceModelCount;

	//! アニメーションモデルデータ関連変数
	static ResourceAnimationModelData* resourceAniModelData;
	static int resourceAniModelCount;

	//! オーディオデータ関連変数
	static ResourceAudioData* resourceAudioData;
	static int resourceAudioCount;

};