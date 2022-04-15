//!============================================================
//!
//!  @file    : Resource.cpp
//!  @brief   : リソースクラスのソースファイル
//!  @author  : 原田 陽央
//!  @details : リソース関連の管理の実装
//!
//!============================================================
#pragma once


//============================================================
//　インクルード
//============================================================
#include "Main.h"
#include "Manager.h"
#include "Renderer.h"
#include "Model.h"
#include "AnimationModel.h"
#include "Resource.h"
#include <stdlib.h>


//============================================================
//　変数宣言
//============================================================
ResourceTextureData* Resource::resourceTextureData;
int Resource::resourceTextureCount;

ResourceModelData* Resource::resourceModelData;
int Resource::resourceModelCount;

ResourceAnimationModelData* Resource::resourceAniModelData;
int Resource::resourceAniModelCount;

ResourceAudioData* Resource::resourceAudioData;
int Resource::resourceAudioCount;


//============================================================
//　関数
//============================================================
//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : 初期化をする
//! @param   : なし
//! @return  : なし
//! @details : 初期化とメモリ確保
//!-----------------------------------------------------------
void Resource::Init()
{
	// 変数の初期化
	resourceTextureCount = 0;
	resourceModelCount = 0;
	resourceAniModelCount = 0;
	resourceAudioCount = 0;

	// データ格納用の変数のメモリ確保
	resourceTextureData  = (ResourceTextureData*)malloc(TEXTURE_MAX * sizeof(ResourceTextureData));
	resourceModelData    = (ResourceModelData*)malloc(MODEL_MAX * sizeof(ResourceModelData));
	resourceAniModelData = (ResourceAnimationModelData*)malloc(ANIMATIONMODEL_MAX * sizeof(ResourceAnimationModelData));
	resourceAudioData    = (ResourceAudioData*)malloc(AUDIO_MAX * sizeof(ResourceAudioData));

	// 使用していない領域の為にidに-1を代入・初期化
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		resourceTextureData[i].textureData = NULL;
		resourceTextureData[i].id = -1;
	}
	for (int i = 0; i < MODEL_MAX; i++)
	{
		resourceModelData[i].modelData = NULL;
		resourceModelData[i].id = -1;
	}
	for (int i = 0; i < ANIMATIONMODEL_MAX; i++)
	{
		resourceAniModelData[i].aniModelData = NULL;
		resourceAniModelData[i].id = -1;
	}
	for (int i = 0; i < AUDIO_MAX; i++)
	{
		resourceAudioData[i].audioData = NULL;
		resourceAudioData[i].id = -1;
	}
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : 終了処理をする
//! @param   : なし
//! @return  : なし
//! @details : データとメモリ解放
//!-----------------------------------------------------------
void Resource::Uninit()
{
	// ロードしたオーディオのデータを解放する
	for (int i = 0; i < AUDIO_MAX; i++)
	{
		if (resourceAudioData[i].id != -1)
		{
			resourceAudioData[i].audioData->Uninit();
			delete resourceAudioData[i].audioData;
		}
	}

	// ロードしたアニメーションモデルのデータを解放する
	for (int i = 0; i < ANIMATIONMODEL_MAX; i++)
	{
		if (resourceAniModelData[i].id != -1)
		{
			delete resourceAniModelData[i].aniModelData;
		}
	}

	// ロードしたモデルのデータを解放する
	for (int i = 0; i < MODEL_MAX; i++)
	{
		if (resourceModelData[i].id != -1)
		{
			delete resourceModelData[i].modelData;
		}
	}

	// ロードしたテクスチャのデータを解放する
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (resourceTextureData[i].id != -1)
		{
			resourceTextureData[i].textureData->Release();
		}
	}

	// データ格納用の変数を解放
	free(resourceAudioData);
	free(resourceAniModelData);
	free(resourceModelData);
	free(resourceTextureData);
}


//!-----------------------------------------------------------
//! @fn      : ResourceTextureLoad(const char* loadFileName)
//! @brief   : テクスチャのロードをする
//! @param   : loadFileName...ロードするファイルの名前
//! @return  : ロード済みまたはロードしたデータを返す
//! @details : テクスチャのロードを実装
//!　          テクスチャをロード済みかどうかチェック
//!　          ロード済みならそのデータを返す
//!　          そうでない場合はロードしてそのデータを返す
//!-----------------------------------------------------------
ID3D11ShaderResourceView* Resource::ResourceTextureLoad(const char* loadFileName)
{
	// 複数ロードしない為の処理
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		// 格納しているデータに同じファイルがあったらtrue
		if (strcmp(resourceTextureData[i].fileName, loadFileName) == 0)
		{
			// ロード済みのテクスチャのデータを返す
			return resourceTextureData[i].textureData;
		}
	}

	// 確保されている場合データにファイル名とidを格納
	strcpy(resourceTextureData[resourceTextureCount].fileName, loadFileName);
	resourceTextureData[resourceTextureCount].id = resourceTextureCount;

	// テクスチャをロード
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(), resourceTextureData[resourceTextureCount].fileName, NULL,
		NULL, &resourceTextureData[resourceTextureCount].textureData, NULL);

	// エラーチェック
	assert(resourceTextureData[resourceTextureCount].textureData);

	// カウントを増やす
	resourceTextureCount++;

	// ロードしたテクスチャのデータを返す
	return resourceTextureData[resourceTextureCount - 1].textureData;
}


//!-----------------------------------------------------------
//! @fn      : ResourceModelLoad(const char* loadFileName)
//! @brief   : モデルのロードをする
//! @param   : loadFileName...ロードするファイルの名前
//! @return  : ロード済みまたはロードしたデータを返す
//! @details : モデルのロードを実装
//!　          モデルをロード済みかどうかチェック
//!　          ロード済みならそのデータを返す
//!　          そうでない場合はロードしてそのデータを返す
//!-----------------------------------------------------------
Model* Resource::ResourceModelLoad(const char* loadFileName)
{
	// 複数ロードしない為の処理
	for (int i = 0; i < MODEL_MAX; i++)
	{
		// 格納しているデータに同じファイルがあったらtrue
		if (strcmp(resourceModelData[i].fileName, loadFileName) == 0)
		{
			// ロード済みのモデルのデータを返す
			return resourceModelData[i].modelData;
		}
	}

	// 確保されている場合データにファイル名とidを格納
	strcpy(resourceModelData[resourceModelCount].fileName, loadFileName);
	resourceModelData[resourceModelCount].id = resourceModelCount;

	// モデルをロード
	resourceModelData[resourceModelCount].modelData = new Model();
	resourceModelData[resourceModelCount].modelData->Load(loadFileName);

	// カウントを増やす
	resourceModelCount++;

	// ロードしたモデルのデータを返す
	return resourceModelData[resourceModelCount - 1].modelData;
}


//!-----------------------------------------------------------
//! @fn      : ResourceAnimationModelLoad(const char* loadFileName)
//! @brief   : アニメーションモデルのロードをする
//! @param   : loadFileName...ロードするファイルの名前
//! @return  : ロード済みまたはロードしたデータを返す
//! @details : アニメーションモデルのロードを実装
//!　          アニメーションモデルをロード済みかどうかチェック
//!　          ロード済みならそのデータを返す
//!　          そうでない場合はロードしてそのデータを返す
//!-----------------------------------------------------------
AnimationModel* Resource::ResourceAnimationModelLoad(const char* loadFileName)
{
	// 複数ロードしない為の処理
	for (int i = 0; i < ANIMATIONMODEL_MAX; i++)
	{
		// 格納しているデータに同じファイルがあったらtrue
		if (strcmp(resourceAniModelData[i].fileName, loadFileName) == 0)
		{
			// ロード済みのモデルのデータを返す
			return resourceAniModelData[i].aniModelData;
		}
	}

	// 確保されている場合データにファイル名とidを格納
	strcpy(resourceAniModelData[resourceAniModelCount].fileName, loadFileName);
	resourceAniModelData[resourceAniModelCount].id = resourceAniModelCount;

	// モデルをロード
	resourceAniModelData[resourceAniModelCount].aniModelData = new AnimationModel();
	resourceAniModelData[resourceAniModelCount].aniModelData->Load(loadFileName);

	// カウントを増やす
	resourceAniModelCount++;

	// ロードしたモデルのデータを返す
	return resourceAniModelData[resourceAniModelCount - 1].aniModelData;
}


//!-----------------------------------------------------------
//! @fn      : ResourceAudioLoad(const char* loadFileName)
//! @brief   : オーディオデータのロードをする
//! @param   : loadFileName...ロードするファイルの名前
//! @return  : ロード済みまたはロードしたデータを返す
//! @details : オーディオデータのロードを実装
//!　          オーディオデータをロード済みかどうかチェック
//!　          ロード済みならそのデータを返す
//!　          そうでない場合はロードしてそのデータを返す
//!-----------------------------------------------------------
Audio* Resource::ResourceAudioLoad(const char* loadFileName)
{
	// 複数ロードしない為の処理
	for (int i = 0; i < AUDIO_MAX; i++)
	{
		// 格納しているデータに同じファイルがあったらtrue
		if (strcmp(resourceAudioData[i].fileName, loadFileName) == 0)
		{
			// ロード済みのオーディオのデータを返す
			return resourceAudioData[i].audioData;
		}
	}

	// 確保されている場合データにファイル名とidを格納
	strcpy(resourceAudioData[resourceAudioCount].fileName, loadFileName);
	resourceAudioData[resourceAudioCount].id = resourceAudioCount;

	// オーディオをロード
	resourceAudioData[resourceAudioCount].audioData = new Audio();
	resourceAudioData[resourceAudioCount].audioData->Load(loadFileName);

	// カウントを増やす
	resourceAudioCount++;

	// ロードしたオーディオのデータを返す
	return resourceAudioData[resourceAudioCount - 1].audioData;
}

