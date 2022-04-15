//!============================================================
//!
//!  @file    : AnimationModel.h
//!  @brief   : アニメーションモデルクラスのヘッダーファイル
//!  @author  : 原田 陽央
//!  @details : アニメーションモデルのロード、アンロード
//!             生成するためのボーンの作成
//!
//!============================================================
#pragma once


//============================================================
//　インクルード
//============================================================
#include <unordered_map>
#include "assimp//cimport.h"
#include "assimp//scene.h"
#include "assimp//postprocess.h"
#include "assimp//matrix4x4.h"
#pragma comment (lib, "assimp.lib")


//!===========================================================
//! @struct DEFORM_VERTEX
//! @brief   : 変形後頂点構造体
//!===========================================================
struct DEFORM_VERTEX
{
	aiVector3D  Position;
	aiVector3D  Normal;
	int         BoneNum; 
	std::string BoneName[4];   // 本来はボーンインデックスで管理するべき
	float       BoneWeight[4];
};

//!===========================================================
//! @struct BONE
//! @brief   : ボーン構造体
//!===========================================================
struct BONE
{
	aiMatrix4x4 Matrix;
	aiMatrix4x4 AnimationMatrix;
	aiMatrix4x4 OffsetMatrix;
};


//!===========================================================
//! @class AnimationModel
//! @brief   : アニメーションモデルの作成を行うクラス
//!===========================================================
class AnimationModel
{
public:

	//!-------------------------------------------------------
	//! @fn      : Load(const char *loadFileName)
	//! @brief   : モデルのロードをする
	//! @param   : loadFileName...ロードするファイルの名前
	//! @return  : なし
	//! @details : ファイルの読み込み
	//!            頂点バッファとインデックスバッファを生成
	//!            変形後頂点データとボーンデータを初期化
	//!            テクスチャの読み込み
	//!-------------------------------------------------------
	void Load(const char *loadFileName);

	//!-------------------------------------------------------
	//! @fn         : LoadAnimation(const char *animationFileName, const char* animationName)
	//! @brief      : アニメーションのロードをする
	//! @param arg1 : animationFileName...ロードするアニメーションのファイル名
	//! @param arg2 : animationName.......アニメーションを設定する際の名前
	//! @return     : なし
	//! @details    : ファイルの読み込み
	//!-------------------------------------------------------
	void LoadAnimation(const char *animationFileName, const char* animationName);

	//!-------------------------------------------------------
	//! @fn      : Unload()
	//! @brief   : モデルのアンロードをする
	//! @param   : なし
	//! @return  : なし
	//! @details : 頂点バッファとインデックスバッファの解放
	//!            その他リリース処理を行う
	//!-------------------------------------------------------
	void Unload();

	//!-------------------------------------------------------
	//! @fn         : Update(const char* animationName, int animationFrame)
	//! @brief      : モデルの更新処理をする
	//! @param arg1 : animationName....設定したアニメーションの名前
	//! @param arg2 : animationFrame...更新する際のフレーム
	//! @return     : なし
	//! @details    : アニメーションの更新
	//!               再生したいアニメーションの名前と再生するためのフレームを引数に使用
	//!-------------------------------------------------------
	void Update(const char* animationName, int animationFrame);

	//!-------------------------------------------------------
	//! @fn      : Draw()
	//! @brief   : モデルの描画をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 描画設定をして描画を行う
	//!-------------------------------------------------------
	void Draw();

private:

	//!-------------------------------------------------------
	//! @fn      : CreateBone(aiNode* node)
	//! @brief   : ボーンデータの作成をする
	//! @param   : node...
	//! @return  : なし
	//! @details : 子をつなげてボーンを作成
	//!-------------------------------------------------------
	void CreateBone(aiNode* node);

	//!-------------------------------------------------------
	//! @fn         : UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix)
	//! @brief      : ボーンマトリクスを更新をする
	//! @param arg1 : node.....インポートファイルのルートノード
	//! @param arg2 : matrix...更新するボーンマトリクス
	//! @return     : なし
	//! @details    : マトリクスを乗算してマトリクスを更新
	//!-------------------------------------------------------
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);

	//! インポートファイルを格納
	const aiScene* aniAiScene = NULL;

	//! 頂点バッファ
	ID3D11Buffer** vertexBuffer;

	//! インデックスバッファ
	ID3D11Buffer** indexBuffer;

	//! aアニメーションデータ
	std::unordered_map<std::string, const aiScene*> animation;

	//! テクスチャデータ
	std::unordered_map<std::string, ID3D11ShaderResourceView*> texture;

	//! 変形後頂点データ
	std::vector<DEFORM_VERTEX>* deformVertex;
	
	//! ボーンデータ
	std::unordered_map<std::string, BONE> bone;

};


