//!============================================================
//!
//!  @file    : DungeonMapData.cpp
//!  @brief   : ダンジョンマップ生成クラスのソースファイル
//!  @author  : 原田 陽央
//!  @details : ダンジョンマップ生成の実装
//!
//!============================================================
#pragma once


//============================================================
//　インクルード
//============================================================
#include <time.h>
#include <cstdlib>
#include <random>
#include "Main.h"
#include "Manager.h"
#include "Scene.h"
#include "Renderer.h"
#include "Resource.h"
#include "DungeonMapData.h"


//============================================================
//　変数宣言
//============================================================
static Scene* scene = NULL;

//! 乱数生成用
std::random_device rnd;
std::mt19937 seed(rnd());


//============================================================
//　関数
//============================================================
//!-----------------------------------------------------------
//! @fn      : Random(int start, int end)
//! @brief   : 乱数を返す
//! @param1  : start...指定したい範囲の始めの数字
//! @param2  : end.....指定したい範囲の最後の数字
//! @return  : startからendまでの乱数
//! @details : startからendまでの乱数を返す
//!            ローカル関数
//!-----------------------------------------------------------
int Random(int start, int end)
{
	// startからendまでの乱数を返す
	std::uniform_int_distribution<> temp(start, end);
	return temp(seed);
}


//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : 初期化をする
//! @param   : なし
//! @return  : なし
//! @details : 初期化処理
//!-----------------------------------------------------------
void DungeonMapData::Init()
{
	
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : 終了処理をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void DungeonMapData::Uninit()
{

}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : 更新をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void DungeonMapData::Update()
{

}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : 描画をする
//! @param   : なし
//! @return  : なし
//! @details : 実装内容なし
//!-----------------------------------------------------------
void DungeonMapData::Draw()
{

}


//!-----------------------------------------------------------
//! @fn      : SetMapData()
//! @brief   : マップの情報のセット
//! @param   : なし
//! @return  : なし
//! @details : 現在デバッグ時は自動生成プログラム
//!            リリース時はテキストファイルのマップデータをロード
//!-----------------------------------------------------------
void DungeonMapData::SetMapData()
{
#ifdef _DEBUG

	// マップの初期化
	ResetMapData();

	// 部屋の区画の生成
	MakeRects();

	// 部屋の生成
	MakeRooms();

	// 生成された部屋の情報をmapDataに登録
	for (auto room : rooms)
	{
		for (int j = room->GetRoomZ(); j < room->GetRoomZ() + room->GetRoomHeight(); j++)
		{
			for (int i = room->GetRoomX(); i < room->GetRoomX() + room->GetRoomWidth(); i++)
			{
				mapData[j][i] = MAP_NONE;
			}
		}	
	}

#else

	// マップ情報をロード
	LoadMapData();
	
	// マップデータをランダムに選出
	int mapDataNum = Random(0, 7);

	// テストデータをマップ情報に格納
	for (int j = 0; j < DUNGEON_MAP_DATA_Z; j++)
	{
		for (int i = 0; i < DUNGEON_MAP_DATA_X; i++)
		{
			mapData[j][i] = tetsMapData[mapDataNum][j][i];

			// 中心座標を設定
			centerPosition[j][i] = D3DXVECTOR3(-DUNGEON_MAP_DATA_X + i * 2.0f, 0.0f, DUNGEON_MAP_DATA_Z - j * 2.0f);
		}
	}

#endif
}


//!-----------------------------------------------------------
//! @fn      : ResetMapData()
//! @brief   : マップの情報のリセット
//! @param   : なし
//! @return  : なし
//! @details : マップの情報の全て壁に設定
//!            中心座標を設定
//!-----------------------------------------------------------
void DungeonMapData::ResetMapData()
{
	for (int j = 0; j < DUNGEON_MAP_DATA_Z; j++)
	{
		for (int i = 0; i < DUNGEON_MAP_DATA_X; i++)
		{
			mapData[j][i] = MAP_WALL;
			
			// 中心座標を設定
			centerPosition[j][i] = D3DXVECTOR3(-DUNGEON_MAP_DATA_X + i * 2.0f, 0.0f, DUNGEON_MAP_DATA_Z - j * 2.0f);
		}
	}
}


//!-----------------------------------------------------------
//! @fn      : SetStair()
//! @brief   : 階段の情報のセット
//! @param   : なし
//! @return  : なし
//! @details : 階段の位置をランダムに設定
//!-----------------------------------------------------------
void DungeonMapData::SetStair()
{
	// 階段をランダムに設置
	// 橋の壁を考慮した乱数を生成
	int mapDataX = (rand() % DUNGEON_MAP_DATA_X - 2) + 1;
	int mapDataZ = (rand() % DUNGEON_MAP_DATA_Z - 2) + 1;

	// 生成した乱数に対応した位置が階段を生成できる場所になるまで、乱数を生成する
 	while (mapData[mapDataZ][mapDataX] != MAP_NONE)
	{
		mapDataX = (rand() % DUNGEON_MAP_DATA_X - 2) + 1;
		mapDataZ = (rand() % DUNGEON_MAP_DATA_Z - 2) + 1;
	}

	// 階段の情報を設定
	mapData[mapDataZ][mapDataX] = MAP_STAIR;
}


//!-----------------------------------------------------------
//! @fn      : GetPlayerPosition()
//! @brief   : プレイヤーの座標のセット
//! @param   : なし
//! @return  : 設定するプレイヤーの位置
//! @details : プレイヤーの位置をランダムに設定
//!-----------------------------------------------------------
D3DXVECTOR3 DungeonMapData::GetPlayerPosition()
{
	// プレイヤーの位置をランダムに設定
	// 橋の壁を考慮した乱数を生成
	int mapDataX = (rand() % DUNGEON_MAP_DATA_X - 2) + 1;
	int mapDataZ = (rand() % DUNGEON_MAP_DATA_Z - 2) + 1;

	// 生成した乱数に対応した位置がプレイヤーを設定できる場所になるまで、乱数を生成する
	while (mapData[mapDataZ][mapDataX] != MAP_NONE)
	{
		mapDataX = (rand() % DUNGEON_MAP_DATA_X - 2) + 1;
		mapDataZ = (rand() % DUNGEON_MAP_DATA_Z - 2) + 1;
	}

	// 設定する位置を返す
	return centerPosition[mapDataZ][mapDataX];
}


//!-----------------------------------------------------------
//! @fn         : GetMapData()
//! @brief      : マップの情報のセット
//! @param arg1 : xNumber...取得した中心座標のX（横）番号
//! @param arg2 : zNumber...取得した中心座標のZ（縦）番号
//! @return     : xNumberとzNumberに対応したマスの情報
//! @details    : xNumberとzNumberに対応したマスの情報を返す
//!-----------------------------------------------------------
DungeonMapDataNumber DungeonMapData::GetMapDataNumber(int xNumber, int zNumber)
{
	return (DungeonMapDataNumber)mapData[zNumber][xNumber];
}


//!-----------------------------------------------------------
//! @fn         : GetCenterPosition(int xNumber, int zNumber) const
//! @brief      : 中心座標の取得
//! @param arg1 : xNumber...取得した中心座標のX（横）番号
//! @param arg2 : zNumber...取得した中心座標のZ（縦）番号
//! @return     : xNumberとzNumberに対応した中心座標
//! @details    : xNumberとzNumberに対応した中心座標のを返す
//!-----------------------------------------------------------
D3DXVECTOR3 DungeonMapData::GetCenterPosition(int xNumber, int zNumber) const
{
	return centerPosition[zNumber][xNumber];
}


//!-----------------------------------------------------------
//! @fn      : LoadMapData()
//! @brief   : マップの情報をロードする
//! @param   : なし
//! @return  : なし
//! @details : テキストファイルから
//!            マップの情報をロードする
//!-----------------------------------------------------------
void DungeonMapData::LoadMapData()
{
	// 読み込み用の変数
	FILE* file = NULL;
	char room = '0';

	// ロードするファイル名を格納
	const char* loadFileName[DUNGEON_MAP_DATA_NUM] =
	{
		"Asset\\Data\\MapData1.txt",
		"Asset\\Data\\MapData2.txt",
		"Asset\\Data\\MapData3.txt",
		"Asset\\Data\\MapData4.txt",
		"Asset\\Data\\MapData5.txt",
		"Asset\\Data\\MapData6.txt",
		"Asset\\Data\\MapData7.txt",
		"Asset\\Data\\MapData8.txt",
		"Asset\\Data\\MapData9.txt",
		"Asset\\Data\\MapData10.txt",
	};

	// ファイルの読み込み
	for (int fileNum = 0; fileNum < DUNGEON_MAP_DATA_NUM; fileNum++)
	{
		// ファイルを開く
		file = fopen(loadFileName[fileNum], "r");

		// エラーチェック
		if (file == NULL)
		{
			return;
		}

		// マップ情報に格納していく
		for (int j = 0; (room != EOF); j++)
		{
			// 改行または終末まで繰り返す
			for (int i = 0; ((room = fgetc(file)) != '\n') && (room != EOF); i++)
			{
				// 文字列としての数字を数値としてテスト用変数に格納
				tetsMapData[fileNum][j][i] = atoi(&room);
			}
		}

		// ファイルを閉じる
		fclose(file);

		// 変数をリセット
		room = '0';
	}
}


//!-----------------------------------------------------------
//! @fn      : InitRooms()
//! @brief   : 部屋リストを全てクリア
//! @param   : なし
//! @return  : なし
//! @details : 部屋情報の初期化を行う
//!            部屋リストを全てクリア
//!-----------------------------------------------------------
void DungeonMapData::InitRooms()
{
	// 部屋リストを全てクリア
	rooms.clear();
}


//!-----------------------------------------------------------
//! @fn      : MakeRects()
//! @brief   : リストの部屋の区画を生成
//! @param   : なし
//! @return  : なし
//! @details : リストの部屋の区画を順に生成していく
//!            生成した区画のカウントを行う
//!-----------------------------------------------------------
void DungeonMapData::MakeRects()
{
	// リストを初期化
	InitRooms();

	// 区域分割法による区画の生成
	// 部屋全体を一つの部屋として1つ目の部屋を生成
	rooms.push_back(new Room( 0, 0, DUNGEON_MAP_DATA_X,DUNGEON_MAP_DATA_Z));
	rectCount = 1;

	// 一つ目の部屋のインスタンスを取得
	Room* temp = rooms.back();

	// 部屋インスタンスを生成しなくなるまでループ
	while (1)
	{
		// インスタンスを生成してtempに代入
		// インスタンスを生成しなかった場合はwhile文を抜ける
		temp = temp->MakeRect();

		if (rooms.back() != temp)
		{
			// roomsのリストに生成したインスタンスを追加
			rooms.push_back(temp);

			// 区画数をカウント
			rectCount++;
		}
		else
		{
			break;
		}
	}
	
}


//!-----------------------------------------------------------
//! @fn      : MakeRooms()
//! @brief   : リストの部屋を生成
//! @param   : なし
//! @return  : なし
//! @details : リストの部屋を順に生成していく
//!-----------------------------------------------------------
void DungeonMapData::MakeRooms()
{
	for (auto room : rooms)
	{
		room->MakeRoom();
	}
}


//!-----------------------------------------------------------
//! @fn         : Room(int setRectX, int setRectZ, int setRectWidth, int setRectHeight)
//!             :    : rectX(setRectX), rectZ(setRectZ), rectWidth(setRectWidth), rectHeight(setRectHeight)
//! @brief      : 引数付きコンストラクタ
//! @param arg1 : setRectX........設定したい部屋の区画左上のX座標
//! @param arg2 : setRectZ........設定したい部屋の区画左上のZ座標
//! @param arg3 : setRectWidth....設定したい部屋の区画の横幅
//! @param arg4 : setRectHeight...設定したい部屋の区画の縦幅
//! @return     : なし
//! @details    : 設定したい部屋の区画の情報を引数として入力し部屋インスタンスを生成
//!-----------------------------------------------------------
DungeonMapData::Room::Room(int setRectX, int setRectZ, int setRectWidth, int setRectHeight)
	: rectX(setRectX), rectZ(setRectZ), rectWidth(setRectWidth), rectHeight(setRectHeight)
{
	// 区画情報以外の変数を初期化
	roomX = 0;
	roomZ = 0;
	roomWidth  = 0;
	roomHeight = 0;
}


//!-----------------------------------------------------------
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
//!-----------------------------------------------------------
DungeonMapData::Room* DungeonMapData::Room::MakeRect()
{
	// 生成に使用する変数
	Room* temp = nullptr;
	bool isCreate = false;
	int split = 0;

	// 区画を分割するかを設定(確率は５分の１に設定)
	isCreate = Random(0, 4) != 0 ? true : false;

	// isCreateがfalseまたは部屋がこれ以上分割できない大きさの場合は自身のインスタンスを返す
	// 条件に満たない場合は分割をして生成した部屋インスタンスを返す
	if (!isCreate || (rectWidth <= RECT_WIDTH_MIN * 2 && rectHeight <= RECT_HEIGHT_MIN * 2))
	{
		// 自身のインスタンスを返す
		return (this);
	}
	else
	{
		// 分割をして生成した部屋インスタンスを返す
		if (rectWidth > rectHeight)
		{
			// 横幅の方が大きい場合は横を分割
			// 区画の最小サイズを考慮して、分割する座標を設定
			split = Random(rectX + RECT_WIDTH_MIN, rectX + rectWidth - RECT_WIDTH_MIN);

			// 分割する座標から新しいインスタンスを生成
			temp = new Room(split, rectZ, rectX + rectWidth - split, rectHeight);

			// 古い方のインスタンスの情報を修正
			rectWidth = split - rectX;
		}
		else
		{
			// 縦幅の方が大きい場合は縦を分割
			// 区画の最小サイズを考慮して、分割する座標を設定
			split = Random(rectZ + RECT_HEIGHT_MIN, rectZ + rectHeight - RECT_HEIGHT_MIN);

			// 分割する座標からインスタンスを生成
			temp = new Room(rectX, split, rectWidth, rectZ + rectHeight - split);

			// 古い方のインスタンスの情報を修正
			rectHeight = split - rectZ;
		}

		// 生成した部屋インスタンスを返す
		return temp;
	}
}


//!-----------------------------------------------------------
//! @fn      : MakeRoom()
//! @brief   : 部屋を生成
//! @param   : なし
//! @return  : なし
//! @details : 部屋の新しいインスタンスを生成
//!            手順として
//!            1.乱数で部屋を生成
//!            2.部屋の左上の座標を決める
//!-----------------------------------------------------------
void DungeonMapData::Room::MakeRoom()
{
	// 部屋の最小サイズ～区画の大きさの間の乱数で部屋を生成
	// 横幅の処理
	if ((rectWidth / 4) > RECT_ROOM_DIFFERENCE_MIN)
	{
		// 区画が大きい場合
		// ※「区画の４分の１の大きさ」が「区画と部屋の必要差分」より大きい
		roomWidth = Random(rectWidth / 4 * 3, rectWidth - RECT_ROOM_DIFFERENCE_MIN);
	}
	else if ((rectWidth / 4) == RECT_ROOM_DIFFERENCE_MIN)
	{
		// 区画が少し小さい場合
		// ※「区画の４分の１の大きさ」が「区画と部屋の必要差分」と等しい
		roomWidth = rectWidth - RECT_ROOM_DIFFERENCE_MIN;
	}
	else if ((rectWidth / 4) < RECT_ROOM_DIFFERENCE_MIN)
	{
		// 区画が小さい場合
		// ※「区画の４分の１の大きさ」が「区画と部屋の必要差分」より小さい
		roomWidth = Random(ROOM_WIDTH_MIN, rectWidth - RECT_ROOM_DIFFERENCE_MIN);
	}

	// 縦幅の処理
	if ((rectHeight / 4) > RECT_ROOM_DIFFERENCE_MIN)
	{
		// 区画が大きい場合
		// ※「区画の４分の１の大きさ」が「区画と部屋の必要差分」より大きい
		roomHeight = Random(rectHeight / 4 * 3, rectHeight - RECT_ROOM_DIFFERENCE_MIN);
	}
	else if ((rectHeight / 4) == RECT_ROOM_DIFFERENCE_MIN)
	{
		// 区画が少し小さい場合
		// ※「区画の４分の１の大きさ」が「区画と部屋の必要差分」と等しい
		roomHeight = rectHeight - RECT_ROOM_DIFFERENCE_MIN;
	}
	else if ((rectHeight / 4) < RECT_ROOM_DIFFERENCE_MIN)
	{
		// 区画が小さい場合
		// ※「区画の４分の１の大きさ」が「区画と部屋の必要差分」より小さい
		roomHeight = Random(ROOM_HEIGHT_MIN, rectHeight - RECT_ROOM_DIFFERENCE_MIN);
	}

	// 部屋の左上の座標を決める
	// 区画の左上の座標～区画と部屋の幅の差分の間の乱数でどのくらいずらすかを設定
	roomX = Random(rectX + 1, rectX + (rectWidth - roomWidth) - 1);
	roomZ = Random(rectZ + 1, rectZ + (rectHeight - roomHeight) - 1);
}


//!-----------------------------------------------------------
//! @fn         : SetRect(int setRectX, int setRectZ, int setRectWidth, int setRectHeight)
//! @brief      : 引数付きコンストラクタ
//! @param arg1 : setRectX........設定したい部屋の区画左上のX座標
//! @param arg2 : setRectZ........設定したい部屋の区画左上のZ座標
//! @param arg3 : setRectWidth....設定したい部屋の区画の横幅
//! @param arg4 : setRectHeight...設定したい部屋の区画の縦幅
//! @return     : なし
//! @details    : 設定したい部屋の区画の情報を引数として入力し区画の変数に代入
//!-----------------------------------------------------------
void DungeonMapData::Room::SetRect(int setRectX, int setRectZ, int setRectWidth, int setRectHeight)
{
	// 区画の大きさを設定
	rectX = setRectX;
	rectZ = setRectZ;
	rectWidth  = setRectWidth;
	rectHeight = setRectHeight;
}