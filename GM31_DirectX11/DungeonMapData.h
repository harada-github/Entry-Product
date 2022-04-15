//!============================================================
//!
//!  @file    : DungeonMapData.h
//!  @brief   : ダンジョンマップ情報クラスのヘッダーファイル
//!  @author  : 原田 陽央
//!  @details : ダンジョンマップ情報の生成や変数を管理
//!
//!============================================================
#pragma once


//============================================================
//　インクルード
//============================================================
#include <list>


#define DUNGEON_MAP_DATA_X (50)
#define DUNGEON_MAP_DATA_Z (45)

#define DUNGEON_MAP_DATA_NUM (10)

#define RECT_WIDTH_MIN  (8) // 部屋の区画横の最小サイズ
#define RECT_HEIGHT_MIN (8) // 部屋の区画縦の最小サイズ

#define ROOM_WIDTH_MIN  (4) // 部屋の横の最小サイズ
#define ROOM_HEIGHT_MIN (4) // 部屋の縦の最小サイズ

#define RECT_ROOM_DIFFERENCE_MIN (4) // 区画と部屋の大きさの差の最小数


enum DungeonMapDataNumber
{
	MAP_WALL,
	MAP_NONE,
	MAP_ROAD,
	MAP_STAIR,
	MAP_MAX_COUNT,
};


//!===========================================================
//! @class DungeonMapData
//! @brief   : ダンジョンマップ情報のクラス
//!===========================================================
class DungeonMapData
{
public:

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : 初期化をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 初期化処理
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
	//! @details : 実装内容なし
	//!-------------------------------------------------------
	void Update();

	//!-------------------------------------------------------
	//! @fn      : Draw()
	//! @brief   : 描画をする
	//! @param   : なし
	//! @return  : なし
	//! @details : 実装内容なし
	//!-------------------------------------------------------
	void Draw();

	//!-------------------------------------------------------
	//! @fn      : SetMapData()
	//! @brief   : マップの情報のセット
	//! @param   : なし
	//! @return  : なし
	//! @details : 
	//!-------------------------------------------------------
	void SetMapData();

	//!-------------------------------------------------------
	//! @fn      : ResetMapData()
	//! @brief   : マップデータのリセット
	//! @param   : なし
	//! @return  : なし
	//! @details : マップデータのリセット
	//!            mapDataの数字を全て0にする
	//!-------------------------------------------------------
	void ResetMapData();

	//!-------------------------------------------------------
	//! @fn      : SetStair()
	//! @brief   : 階段の情報のセット
	//! @param   : なし
	//! @return  : なし
	//! @details : 
	//!-------------------------------------------------------
	void SetStair();

	//!-------------------------------------------------------
	//! @fn      : GetPlayerPosition()
	//! @brief   : プレイヤーの座標のセット
	//! @param   : なし
	//! @return  : 設定するプレイヤーの位置
	//! @details : プレイヤーの位置をランダムに設定
	//!-------------------------------------------------------
	D3DXVECTOR3 GetPlayerPosition();

	//!-------------------------------------------------------
	//! @fn         : GetMapData()
	//! @brief      : マップの情報のセット
	//! @param arg1 : xNumber...取得した中心座標のX（横）番号
	//! @param arg2 : zNumber...取得した中心座標のZ（縦）番号
	//! @return     : xNumberとzNumberに対応したマスの情報
	//! @details    : xNumberとzNumberに対応したマスの情報を返す
	//!-------------------------------------------------------
	DungeonMapDataNumber GetMapDataNumber(int xNumber, int zNumber);

	//!-------------------------------------------------------
	//! @fn         : GetCenterPosition(int xNumber, int zNumber) const
	//! @brief      : 中心座標の取得
	//! @param arg1 : xNumber...取得した中心座標のX（横）番号
	//! @param arg2 : zNumber...取得した中心座標のZ（縦）番号
	//! @return     : xNumberとzNumberに対応した中心座標
	//! @details    : xNumberとzNumberに対応した中心座標のを返す
	//!-------------------------------------------------------
	D3DXVECTOR3 GetCenterPosition(int xNumber, int zNumber) const;

	//!-------------------------------------------------------
	//! @fn      : LoadMapData()
	//! @brief   : マップの情報をロードする
	//! @param   : なし
	//! @return  : なし
	//! @details : テキストファイルから
	//!            マップの情報をロードする
	//!-------------------------------------------------------
	void LoadMapData();

	//!-------------------------------------------------------
	//! @fn      : InitRooms()
	//! @brief   : 部屋リストを全てクリア
	//! @param   : なし
	//! @return  : なし
	//! @details : 部屋情報の初期化を行う
	//!            部屋リストを全てクリア
	//!-------------------------------------------------------
	void InitRooms();

	//!-------------------------------------------------------
	//! @fn      : MakeRects()
	//! @brief   : リストの部屋の区画を生成
	//! @param   : なし
	//! @return  : なし
	//! @details : リストの部屋の区画を順に生成していく
	//!            生成した区画のカウントを行う
	//!-------------------------------------------------------
	void MakeRects();

	//!-------------------------------------------------------
	//! @fn      : MakeRooms()
	//! @brief   : リストの部屋を生成
	//! @param   : なし
	//! @return  : なし
	//! @details : リストの部屋を順に生成していく
	//!-------------------------------------------------------
	void MakeRooms();


	//!=======================================================
	//! @class Room
	//! @brief   : 部屋クラス
	//!=======================================================
	class Room
	{
	public:

		//!-------------------------------------------------------
		//! @fn         : Room(int setStartX, int setStartZ, int setWidth, int setHeight)
		//!             :     : startX(setStartX), startZ(setStartZ), width(setWidth), height(setHeight)
		//! @brief      : 引数付きコンストラクタ
		//! @param arg1 : setRectX........設定したい部屋の区画左上のX座標
		//! @param arg2 : setRectZ........設定したい部屋の区画左上のZ座標
		//! @param arg3 : setRectWidth....設定したい部屋の区画の横幅
		//! @param arg4 : setRectHeight...設定したい部屋の区画の縦幅
		//! @return     : なし
		//! @details    : 設定したい部屋の区画の情報を引数として入力し部屋インスタンスを生成
		//!-------------------------------------------------------
		Room(int setRectX, int setRectZ, int setRectWidth, int setRectHeight);

		//!-------------------------------------------------------
		//! @fn      : MakeRect()
		//! @brief   : 部屋の区画を生成
		//! @param   : なし
		//! @return  : 分割する場合は生成したインスタンス
		//!            分割しない場合は自身のインスタンス
		//! @details : 部屋の区画を分割して新しいインスタンスを生成
		//!            手順として
		//!            1.現在のインスタンスを分割する部屋とし
		//!              分割するかどうかを決める
		//!            2.分割する場合は部屋の区画の最小サイズを考慮し
		//!              乱数によって分割する座標を決める
		//!              ※分割しない場合は現在のインスタンスを返す
		//!            3.分割する座標と現在のインスタンスの情報から
		//!              新しい部屋のインスタンスを生成
		//!            4.現在のインスタンスの区画情報を
		//!              分割する座標に合わせて変更する
		//!-------------------------------------------------------
		Room* MakeRect();

		//!-------------------------------------------------------
		//! @fn      : MakeRoom()
		//! @brief   : 部屋を生成
		//! @param   : なし
		//! @return  : なし
		//! @details : 部屋の新しいインスタンスを生成
		//!            手順として
		//!            1.乱数で部屋を生成
		//!            2.部屋の左上の座標を決める
		//!-------------------------------------------------------
		void MakeRoom();

		//!-------------------------------------------------------
		//! @fn         : SetRect(int setRectX, int setRectZ, int setRectWidth, int setRectHeight)
		//! @brief      : 引数付きコンストラクタ
		//! @param arg1 : setRectX........設定したい部屋の区画左上のX座標
		//! @param arg2 : setRectZ........設定したい部屋の区画左上のZ座標
		//! @param arg3 : setRectWidth....設定したい部屋の区画の横幅
		//! @param arg4 : setRectHeight...設定したい部屋の区画の縦幅
		//! @return     : なし
		//! @details    : 設定したい部屋の区画の情報を引数として入力し区画の変数に代入
		//!-------------------------------------------------------
		void SetRect(int setRectX, int setRectZ, int setRectWidth, int setRectHeight);

		int GetRoomX()
		{
			return roomX;
		}

		int GetRoomZ()
		{
			return roomZ;
		}

		int GetRoomWidth()
		{
			return roomWidth;
		}

		int GetRoomHeight()
		{
			return roomHeight;
		}



	private:
	
		//! 区画の左上の点の座標
		int rectX;
		int rectZ;

		//! 区画の幅と高さ
		int rectWidth;
		int rectHeight;

		//! 部屋の左上の点の座標
		int roomX;
		int roomZ;

		//! 部屋の幅と高さ
		int roomWidth;
		int roomHeight;

		//! 通路開始の座標
		int pathwayPoint;

	};



private:

	//! マップの情報
	int mapData[DUNGEON_MAP_DATA_Z][DUNGEON_MAP_DATA_X];

	//! テストマップの情報
	int tetsMapData[DUNGEON_MAP_DATA_NUM][DUNGEON_MAP_DATA_Z][DUNGEON_MAP_DATA_X];

	//! マスの中心座標
	D3DXVECTOR3 centerPosition[DUNGEON_MAP_DATA_Z][DUNGEON_MAP_DATA_X];

	//! 部屋のインスタンス
	std::list<Room*> rooms;

	//! 区画数
	int rectCount;

};