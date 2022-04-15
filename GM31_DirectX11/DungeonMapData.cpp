//!============================================================
//!
//!  @file    : DungeonMapData.cpp
//!  @brief   : �_���W�����}�b�v�����N���X�̃\�[�X�t�@�C��
//!  @author  : ���c �z��
//!  @details : �_���W�����}�b�v�����̎���
//!
//!============================================================
#pragma once


//============================================================
//�@�C���N���[�h
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
//�@�ϐ��錾
//============================================================
static Scene* scene = NULL;

//! ���������p
std::random_device rnd;
std::mt19937 seed(rnd());


//============================================================
//�@�֐�
//============================================================
//!-----------------------------------------------------------
//! @fn      : Random(int start, int end)
//! @brief   : ������Ԃ�
//! @param1  : start...�w�肵�����͈͂̎n�߂̐���
//! @param2  : end.....�w�肵�����͈͂̍Ō�̐���
//! @return  : start����end�܂ł̗���
//! @details : start����end�܂ł̗�����Ԃ�
//!            ���[�J���֐�
//!-----------------------------------------------------------
int Random(int start, int end)
{
	// start����end�܂ł̗�����Ԃ�
	std::uniform_int_distribution<> temp(start, end);
	return temp(seed);
}


//!-----------------------------------------------------------
//! @fn      : Init()
//! @brief   : ������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : ����������
//!-----------------------------------------------------------
void DungeonMapData::Init()
{
	
}


//!-----------------------------------------------------------
//! @fn      : Uninit()
//! @brief   : �I������������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void DungeonMapData::Uninit()
{

}


//!-----------------------------------------------------------
//! @fn      : Update()
//! @brief   : �X�V������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void DungeonMapData::Update()
{

}


//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : �`�������
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������e�Ȃ�
//!-----------------------------------------------------------
void DungeonMapData::Draw()
{

}


//!-----------------------------------------------------------
//! @fn      : SetMapData()
//! @brief   : �}�b�v�̏��̃Z�b�g
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : ���݃f�o�b�O���͎��������v���O����
//!            �����[�X���̓e�L�X�g�t�@�C���̃}�b�v�f�[�^�����[�h
//!-----------------------------------------------------------
void DungeonMapData::SetMapData()
{
#ifdef _DEBUG

	// �}�b�v�̏�����
	ResetMapData();

	// �����̋��̐���
	MakeRects();

	// �����̐���
	MakeRooms();

	// �������ꂽ�����̏���mapData�ɓo�^
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

	// �}�b�v�������[�h
	LoadMapData();
	
	// �}�b�v�f�[�^�������_���ɑI�o
	int mapDataNum = Random(0, 7);

	// �e�X�g�f�[�^���}�b�v���Ɋi�[
	for (int j = 0; j < DUNGEON_MAP_DATA_Z; j++)
	{
		for (int i = 0; i < DUNGEON_MAP_DATA_X; i++)
		{
			mapData[j][i] = tetsMapData[mapDataNum][j][i];

			// ���S���W��ݒ�
			centerPosition[j][i] = D3DXVECTOR3(-DUNGEON_MAP_DATA_X + i * 2.0f, 0.0f, DUNGEON_MAP_DATA_Z - j * 2.0f);
		}
	}

#endif
}


//!-----------------------------------------------------------
//! @fn      : ResetMapData()
//! @brief   : �}�b�v�̏��̃��Z�b�g
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �}�b�v�̏��̑S�ĕǂɐݒ�
//!            ���S���W��ݒ�
//!-----------------------------------------------------------
void DungeonMapData::ResetMapData()
{
	for (int j = 0; j < DUNGEON_MAP_DATA_Z; j++)
	{
		for (int i = 0; i < DUNGEON_MAP_DATA_X; i++)
		{
			mapData[j][i] = MAP_WALL;
			
			// ���S���W��ݒ�
			centerPosition[j][i] = D3DXVECTOR3(-DUNGEON_MAP_DATA_X + i * 2.0f, 0.0f, DUNGEON_MAP_DATA_Z - j * 2.0f);
		}
	}
}


//!-----------------------------------------------------------
//! @fn      : SetStair()
//! @brief   : �K�i�̏��̃Z�b�g
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �K�i�̈ʒu�������_���ɐݒ�
//!-----------------------------------------------------------
void DungeonMapData::SetStair()
{
	// �K�i�������_���ɐݒu
	// ���̕ǂ��l�����������𐶐�
	int mapDataX = (rand() % DUNGEON_MAP_DATA_X - 2) + 1;
	int mapDataZ = (rand() % DUNGEON_MAP_DATA_Z - 2) + 1;

	// �������������ɑΉ������ʒu���K�i�𐶐��ł���ꏊ�ɂȂ�܂ŁA�����𐶐�����
 	while (mapData[mapDataZ][mapDataX] != MAP_NONE)
	{
		mapDataX = (rand() % DUNGEON_MAP_DATA_X - 2) + 1;
		mapDataZ = (rand() % DUNGEON_MAP_DATA_Z - 2) + 1;
	}

	// �K�i�̏���ݒ�
	mapData[mapDataZ][mapDataX] = MAP_STAIR;
}


//!-----------------------------------------------------------
//! @fn      : GetPlayerPosition()
//! @brief   : �v���C���[�̍��W�̃Z�b�g
//! @param   : �Ȃ�
//! @return  : �ݒ肷��v���C���[�̈ʒu
//! @details : �v���C���[�̈ʒu�������_���ɐݒ�
//!-----------------------------------------------------------
D3DXVECTOR3 DungeonMapData::GetPlayerPosition()
{
	// �v���C���[�̈ʒu�������_���ɐݒ�
	// ���̕ǂ��l�����������𐶐�
	int mapDataX = (rand() % DUNGEON_MAP_DATA_X - 2) + 1;
	int mapDataZ = (rand() % DUNGEON_MAP_DATA_Z - 2) + 1;

	// �������������ɑΉ������ʒu���v���C���[��ݒ�ł���ꏊ�ɂȂ�܂ŁA�����𐶐�����
	while (mapData[mapDataZ][mapDataX] != MAP_NONE)
	{
		mapDataX = (rand() % DUNGEON_MAP_DATA_X - 2) + 1;
		mapDataZ = (rand() % DUNGEON_MAP_DATA_Z - 2) + 1;
	}

	// �ݒ肷��ʒu��Ԃ�
	return centerPosition[mapDataZ][mapDataX];
}


//!-----------------------------------------------------------
//! @fn         : GetMapData()
//! @brief      : �}�b�v�̏��̃Z�b�g
//! @param arg1 : xNumber...�擾�������S���W��X�i���j�ԍ�
//! @param arg2 : zNumber...�擾�������S���W��Z�i�c�j�ԍ�
//! @return     : xNumber��zNumber�ɑΉ������}�X�̏��
//! @details    : xNumber��zNumber�ɑΉ������}�X�̏���Ԃ�
//!-----------------------------------------------------------
DungeonMapDataNumber DungeonMapData::GetMapDataNumber(int xNumber, int zNumber)
{
	return (DungeonMapDataNumber)mapData[zNumber][xNumber];
}


//!-----------------------------------------------------------
//! @fn         : GetCenterPosition(int xNumber, int zNumber) const
//! @brief      : ���S���W�̎擾
//! @param arg1 : xNumber...�擾�������S���W��X�i���j�ԍ�
//! @param arg2 : zNumber...�擾�������S���W��Z�i�c�j�ԍ�
//! @return     : xNumber��zNumber�ɑΉ��������S���W
//! @details    : xNumber��zNumber�ɑΉ��������S���W�̂�Ԃ�
//!-----------------------------------------------------------
D3DXVECTOR3 DungeonMapData::GetCenterPosition(int xNumber, int zNumber) const
{
	return centerPosition[zNumber][xNumber];
}


//!-----------------------------------------------------------
//! @fn      : LoadMapData()
//! @brief   : �}�b�v�̏������[�h����
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �e�L�X�g�t�@�C������
//!            �}�b�v�̏������[�h����
//!-----------------------------------------------------------
void DungeonMapData::LoadMapData()
{
	// �ǂݍ��ݗp�̕ϐ�
	FILE* file = NULL;
	char room = '0';

	// ���[�h����t�@�C�������i�[
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

	// �t�@�C���̓ǂݍ���
	for (int fileNum = 0; fileNum < DUNGEON_MAP_DATA_NUM; fileNum++)
	{
		// �t�@�C�����J��
		file = fopen(loadFileName[fileNum], "r");

		// �G���[�`�F�b�N
		if (file == NULL)
		{
			return;
		}

		// �}�b�v���Ɋi�[���Ă���
		for (int j = 0; (room != EOF); j++)
		{
			// ���s�܂��͏I���܂ŌJ��Ԃ�
			for (int i = 0; ((room = fgetc(file)) != '\n') && (room != EOF); i++)
			{
				// ������Ƃ��Ă̐����𐔒l�Ƃ��ăe�X�g�p�ϐ��Ɋi�[
				tetsMapData[fileNum][j][i] = atoi(&room);
			}
		}

		// �t�@�C�������
		fclose(file);

		// �ϐ������Z�b�g
		room = '0';
	}
}


//!-----------------------------------------------------------
//! @fn      : InitRooms()
//! @brief   : �������X�g��S�ăN���A
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �������̏��������s��
//!            �������X�g��S�ăN���A
//!-----------------------------------------------------------
void DungeonMapData::InitRooms()
{
	// �������X�g��S�ăN���A
	rooms.clear();
}


//!-----------------------------------------------------------
//! @fn      : MakeRects()
//! @brief   : ���X�g�̕����̋��𐶐�
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : ���X�g�̕����̋������ɐ������Ă���
//!            �����������̃J�E���g���s��
//!-----------------------------------------------------------
void DungeonMapData::MakeRects()
{
	// ���X�g��������
	InitRooms();

	// ��敪���@�ɂ����̐���
	// �����S�̂���̕����Ƃ���1�ڂ̕����𐶐�
	rooms.push_back(new Room( 0, 0, DUNGEON_MAP_DATA_X,DUNGEON_MAP_DATA_Z));
	rectCount = 1;

	// ��ڂ̕����̃C���X�^���X���擾
	Room* temp = rooms.back();

	// �����C���X�^���X�𐶐����Ȃ��Ȃ�܂Ń��[�v
	while (1)
	{
		// �C���X�^���X�𐶐�����temp�ɑ��
		// �C���X�^���X�𐶐����Ȃ������ꍇ��while���𔲂���
		temp = temp->MakeRect();

		if (rooms.back() != temp)
		{
			// rooms�̃��X�g�ɐ��������C���X�^���X��ǉ�
			rooms.push_back(temp);

			// ��搔���J�E���g
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
//! @brief   : ���X�g�̕����𐶐�
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : ���X�g�̕��������ɐ������Ă���
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
//! @brief      : �����t���R���X�g���N�^
//! @param arg1 : setRectX........�ݒ肵���������̋�捶���X���W
//! @param arg2 : setRectZ........�ݒ肵���������̋�捶���Z���W
//! @param arg3 : setRectWidth....�ݒ肵���������̋��̉���
//! @param arg4 : setRectHeight...�ݒ肵���������̋��̏c��
//! @return     : �Ȃ�
//! @details    : �ݒ肵���������̋��̏��������Ƃ��ē��͂������C���X�^���X�𐶐�
//!-----------------------------------------------------------
DungeonMapData::Room::Room(int setRectX, int setRectZ, int setRectWidth, int setRectHeight)
	: rectX(setRectX), rectZ(setRectZ), rectWidth(setRectWidth), rectHeight(setRectHeight)
{
	// �����ȊO�̕ϐ���������
	roomX = 0;
	roomZ = 0;
	roomWidth  = 0;
	roomHeight = 0;
}


//!-----------------------------------------------------------
//! @fn      : MakeRect()
//! @brief   : �����̋��𐶐�
//! @param   : �Ȃ�
//! @return  : ��������ꍇ�͐��������C���X�^���X
//!            �������Ȃ��ꍇ�͎��g�̃C���X�^���X
//! @details : �����̋��𕪊����ĐV�����C���X�^���X�𐶐�
//!            �菇�Ƃ���
//!            1.���݂̃C���X�^���X�𕪊����镔���Ƃ�
//!              �������邩�ǂ��������߂�
//!            2.��������ꍇ�͕����̋��̍ŏ��T�C�Y���l����
//!              �����ɂ���ĕ���������W�����߂�
//!              ���������Ȃ��ꍇ�͌��݂̃C���X�^���X��Ԃ�
//!            3.����������W�ƌ��݂̃C���X�^���X�̏�񂩂�
//!              �V���������̃C���X�^���X�𐶐�
//!            4.���݂̃C���X�^���X�̋�����
//!              ����������W�ɍ��킹�ĕύX����
//!-----------------------------------------------------------
DungeonMapData::Room* DungeonMapData::Room::MakeRect()
{
	// �����Ɏg�p����ϐ�
	Room* temp = nullptr;
	bool isCreate = false;
	int split = 0;

	// ���𕪊����邩��ݒ�(�m���͂T���̂P�ɐݒ�)
	isCreate = Random(0, 4) != 0 ? true : false;

	// isCreate��false�܂��͕���������ȏ㕪���ł��Ȃ��傫���̏ꍇ�͎��g�̃C���X�^���X��Ԃ�
	// �����ɖ����Ȃ��ꍇ�͕��������Đ������������C���X�^���X��Ԃ�
	if (!isCreate || (rectWidth <= RECT_WIDTH_MIN * 2 && rectHeight <= RECT_HEIGHT_MIN * 2))
	{
		// ���g�̃C���X�^���X��Ԃ�
		return (this);
	}
	else
	{
		// ���������Đ������������C���X�^���X��Ԃ�
		if (rectWidth > rectHeight)
		{
			// �����̕����傫���ꍇ�͉��𕪊�
			// ���̍ŏ��T�C�Y���l�����āA����������W��ݒ�
			split = Random(rectX + RECT_WIDTH_MIN, rectX + rectWidth - RECT_WIDTH_MIN);

			// ����������W����V�����C���X�^���X�𐶐�
			temp = new Room(split, rectZ, rectX + rectWidth - split, rectHeight);

			// �Â����̃C���X�^���X�̏����C��
			rectWidth = split - rectX;
		}
		else
		{
			// �c���̕����傫���ꍇ�͏c�𕪊�
			// ���̍ŏ��T�C�Y���l�����āA����������W��ݒ�
			split = Random(rectZ + RECT_HEIGHT_MIN, rectZ + rectHeight - RECT_HEIGHT_MIN);

			// ����������W����C���X�^���X�𐶐�
			temp = new Room(rectX, split, rectWidth, rectZ + rectHeight - split);

			// �Â����̃C���X�^���X�̏����C��
			rectHeight = split - rectZ;
		}

		// �������������C���X�^���X��Ԃ�
		return temp;
	}
}


//!-----------------------------------------------------------
//! @fn      : MakeRoom()
//! @brief   : �����𐶐�
//! @param   : �Ȃ�
//! @return  : �Ȃ�
//! @details : �����̐V�����C���X�^���X�𐶐�
//!            �菇�Ƃ���
//!            1.�����ŕ����𐶐�
//!            2.�����̍���̍��W�����߂�
//!-----------------------------------------------------------
void DungeonMapData::Room::MakeRoom()
{
	// �����̍ŏ��T�C�Y�`���̑傫���̊Ԃ̗����ŕ����𐶐�
	// �����̏���
	if ((rectWidth / 4) > RECT_ROOM_DIFFERENCE_MIN)
	{
		// ��悪�傫���ꍇ
		// ���u���̂S���̂P�̑傫���v���u���ƕ����̕K�v�����v���傫��
		roomWidth = Random(rectWidth / 4 * 3, rectWidth - RECT_ROOM_DIFFERENCE_MIN);
	}
	else if ((rectWidth / 4) == RECT_ROOM_DIFFERENCE_MIN)
	{
		// ��悪�����������ꍇ
		// ���u���̂S���̂P�̑傫���v���u���ƕ����̕K�v�����v�Ɠ�����
		roomWidth = rectWidth - RECT_ROOM_DIFFERENCE_MIN;
	}
	else if ((rectWidth / 4) < RECT_ROOM_DIFFERENCE_MIN)
	{
		// ��悪�������ꍇ
		// ���u���̂S���̂P�̑傫���v���u���ƕ����̕K�v�����v��菬����
		roomWidth = Random(ROOM_WIDTH_MIN, rectWidth - RECT_ROOM_DIFFERENCE_MIN);
	}

	// �c���̏���
	if ((rectHeight / 4) > RECT_ROOM_DIFFERENCE_MIN)
	{
		// ��悪�傫���ꍇ
		// ���u���̂S���̂P�̑傫���v���u���ƕ����̕K�v�����v���傫��
		roomHeight = Random(rectHeight / 4 * 3, rectHeight - RECT_ROOM_DIFFERENCE_MIN);
	}
	else if ((rectHeight / 4) == RECT_ROOM_DIFFERENCE_MIN)
	{
		// ��悪�����������ꍇ
		// ���u���̂S���̂P�̑傫���v���u���ƕ����̕K�v�����v�Ɠ�����
		roomHeight = rectHeight - RECT_ROOM_DIFFERENCE_MIN;
	}
	else if ((rectHeight / 4) < RECT_ROOM_DIFFERENCE_MIN)
	{
		// ��悪�������ꍇ
		// ���u���̂S���̂P�̑傫���v���u���ƕ����̕K�v�����v��菬����
		roomHeight = Random(ROOM_HEIGHT_MIN, rectHeight - RECT_ROOM_DIFFERENCE_MIN);
	}

	// �����̍���̍��W�����߂�
	// ���̍���̍��W�`���ƕ����̕��̍����̊Ԃ̗����łǂ̂��炢���炷����ݒ�
	roomX = Random(rectX + 1, rectX + (rectWidth - roomWidth) - 1);
	roomZ = Random(rectZ + 1, rectZ + (rectHeight - roomHeight) - 1);
}


//!-----------------------------------------------------------
//! @fn         : SetRect(int setRectX, int setRectZ, int setRectWidth, int setRectHeight)
//! @brief      : �����t���R���X�g���N�^
//! @param arg1 : setRectX........�ݒ肵���������̋�捶���X���W
//! @param arg2 : setRectZ........�ݒ肵���������̋�捶���Z���W
//! @param arg3 : setRectWidth....�ݒ肵���������̋��̉���
//! @param arg4 : setRectHeight...�ݒ肵���������̋��̏c��
//! @return     : �Ȃ�
//! @details    : �ݒ肵���������̋��̏��������Ƃ��ē��͂����̕ϐ��ɑ��
//!-----------------------------------------------------------
void DungeonMapData::Room::SetRect(int setRectX, int setRectZ, int setRectWidth, int setRectHeight)
{
	// ���̑傫����ݒ�
	rectX = setRectX;
	rectZ = setRectZ;
	rectWidth  = setRectWidth;
	rectHeight = setRectHeight;
}