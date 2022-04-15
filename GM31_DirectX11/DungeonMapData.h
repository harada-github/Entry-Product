//!============================================================
//!
//!  @file    : DungeonMapData.h
//!  @brief   : �_���W�����}�b�v���N���X�̃w�b�_�[�t�@�C��
//!  @author  : ���c �z��
//!  @details : �_���W�����}�b�v���̐�����ϐ����Ǘ�
//!
//!============================================================
#pragma once


//============================================================
//�@�C���N���[�h
//============================================================
#include <list>


#define DUNGEON_MAP_DATA_X (50)
#define DUNGEON_MAP_DATA_Z (45)

#define DUNGEON_MAP_DATA_NUM (10)

#define RECT_WIDTH_MIN  (8) // �����̋�扡�̍ŏ��T�C�Y
#define RECT_HEIGHT_MIN (8) // �����̋��c�̍ŏ��T�C�Y

#define ROOM_WIDTH_MIN  (4) // �����̉��̍ŏ��T�C�Y
#define ROOM_HEIGHT_MIN (4) // �����̏c�̍ŏ��T�C�Y

#define RECT_ROOM_DIFFERENCE_MIN (4) // ���ƕ����̑傫���̍��̍ŏ���


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
//! @brief   : �_���W�����}�b�v���̃N���X
//!===========================================================
class DungeonMapData
{
public:

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : ������������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : ����������
	//!-------------------------------------------------------
	void Init();

	//!-------------------------------------------------------
	//! @fn      : Uninit()
	//! @brief   : �I������������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������e�Ȃ�
	//!-------------------------------------------------------
	void Uninit();

	//!-------------------------------------------------------
	//! @fn      : Update()
	//! @brief   : �X�V������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������e�Ȃ�
	//!-------------------------------------------------------
	void Update();

	//!-------------------------------------------------------
	//! @fn      : Draw()
	//! @brief   : �`�������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������e�Ȃ�
	//!-------------------------------------------------------
	void Draw();

	//!-------------------------------------------------------
	//! @fn      : SetMapData()
	//! @brief   : �}�b�v�̏��̃Z�b�g
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : 
	//!-------------------------------------------------------
	void SetMapData();

	//!-------------------------------------------------------
	//! @fn      : ResetMapData()
	//! @brief   : �}�b�v�f�[�^�̃��Z�b�g
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �}�b�v�f�[�^�̃��Z�b�g
	//!            mapData�̐�����S��0�ɂ���
	//!-------------------------------------------------------
	void ResetMapData();

	//!-------------------------------------------------------
	//! @fn      : SetStair()
	//! @brief   : �K�i�̏��̃Z�b�g
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : 
	//!-------------------------------------------------------
	void SetStair();

	//!-------------------------------------------------------
	//! @fn      : GetPlayerPosition()
	//! @brief   : �v���C���[�̍��W�̃Z�b�g
	//! @param   : �Ȃ�
	//! @return  : �ݒ肷��v���C���[�̈ʒu
	//! @details : �v���C���[�̈ʒu�������_���ɐݒ�
	//!-------------------------------------------------------
	D3DXVECTOR3 GetPlayerPosition();

	//!-------------------------------------------------------
	//! @fn         : GetMapData()
	//! @brief      : �}�b�v�̏��̃Z�b�g
	//! @param arg1 : xNumber...�擾�������S���W��X�i���j�ԍ�
	//! @param arg2 : zNumber...�擾�������S���W��Z�i�c�j�ԍ�
	//! @return     : xNumber��zNumber�ɑΉ������}�X�̏��
	//! @details    : xNumber��zNumber�ɑΉ������}�X�̏���Ԃ�
	//!-------------------------------------------------------
	DungeonMapDataNumber GetMapDataNumber(int xNumber, int zNumber);

	//!-------------------------------------------------------
	//! @fn         : GetCenterPosition(int xNumber, int zNumber) const
	//! @brief      : ���S���W�̎擾
	//! @param arg1 : xNumber...�擾�������S���W��X�i���j�ԍ�
	//! @param arg2 : zNumber...�擾�������S���W��Z�i�c�j�ԍ�
	//! @return     : xNumber��zNumber�ɑΉ��������S���W
	//! @details    : xNumber��zNumber�ɑΉ��������S���W�̂�Ԃ�
	//!-------------------------------------------------------
	D3DXVECTOR3 GetCenterPosition(int xNumber, int zNumber) const;

	//!-------------------------------------------------------
	//! @fn      : LoadMapData()
	//! @brief   : �}�b�v�̏������[�h����
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �e�L�X�g�t�@�C������
	//!            �}�b�v�̏������[�h����
	//!-------------------------------------------------------
	void LoadMapData();

	//!-------------------------------------------------------
	//! @fn      : InitRooms()
	//! @brief   : �������X�g��S�ăN���A
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������̏��������s��
	//!            �������X�g��S�ăN���A
	//!-------------------------------------------------------
	void InitRooms();

	//!-------------------------------------------------------
	//! @fn      : MakeRects()
	//! @brief   : ���X�g�̕����̋��𐶐�
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : ���X�g�̕����̋������ɐ������Ă���
	//!            �����������̃J�E���g���s��
	//!-------------------------------------------------------
	void MakeRects();

	//!-------------------------------------------------------
	//! @fn      : MakeRooms()
	//! @brief   : ���X�g�̕����𐶐�
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : ���X�g�̕��������ɐ������Ă���
	//!-------------------------------------------------------
	void MakeRooms();


	//!=======================================================
	//! @class Room
	//! @brief   : �����N���X
	//!=======================================================
	class Room
	{
	public:

		//!-------------------------------------------------------
		//! @fn         : Room(int setStartX, int setStartZ, int setWidth, int setHeight)
		//!             :     : startX(setStartX), startZ(setStartZ), width(setWidth), height(setHeight)
		//! @brief      : �����t���R���X�g���N�^
		//! @param arg1 : setRectX........�ݒ肵���������̋�捶���X���W
		//! @param arg2 : setRectZ........�ݒ肵���������̋�捶���Z���W
		//! @param arg3 : setRectWidth....�ݒ肵���������̋��̉���
		//! @param arg4 : setRectHeight...�ݒ肵���������̋��̏c��
		//! @return     : �Ȃ�
		//! @details    : �ݒ肵���������̋��̏��������Ƃ��ē��͂������C���X�^���X�𐶐�
		//!-------------------------------------------------------
		Room(int setRectX, int setRectZ, int setRectWidth, int setRectHeight);

		//!-------------------------------------------------------
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
		//!-------------------------------------------------------
		Room* MakeRect();

		//!-------------------------------------------------------
		//! @fn      : MakeRoom()
		//! @brief   : �����𐶐�
		//! @param   : �Ȃ�
		//! @return  : �Ȃ�
		//! @details : �����̐V�����C���X�^���X�𐶐�
		//!            �菇�Ƃ���
		//!            1.�����ŕ����𐶐�
		//!            2.�����̍���̍��W�����߂�
		//!-------------------------------------------------------
		void MakeRoom();

		//!-------------------------------------------------------
		//! @fn         : SetRect(int setRectX, int setRectZ, int setRectWidth, int setRectHeight)
		//! @brief      : �����t���R���X�g���N�^
		//! @param arg1 : setRectX........�ݒ肵���������̋�捶���X���W
		//! @param arg2 : setRectZ........�ݒ肵���������̋�捶���Z���W
		//! @param arg3 : setRectWidth....�ݒ肵���������̋��̉���
		//! @param arg4 : setRectHeight...�ݒ肵���������̋��̏c��
		//! @return     : �Ȃ�
		//! @details    : �ݒ肵���������̋��̏��������Ƃ��ē��͂����̕ϐ��ɑ��
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
	
		//! ���̍���̓_�̍��W
		int rectX;
		int rectZ;

		//! ���̕��ƍ���
		int rectWidth;
		int rectHeight;

		//! �����̍���̓_�̍��W
		int roomX;
		int roomZ;

		//! �����̕��ƍ���
		int roomWidth;
		int roomHeight;

		//! �ʘH�J�n�̍��W
		int pathwayPoint;

	};



private:

	//! �}�b�v�̏��
	int mapData[DUNGEON_MAP_DATA_Z][DUNGEON_MAP_DATA_X];

	//! �e�X�g�}�b�v�̏��
	int tetsMapData[DUNGEON_MAP_DATA_NUM][DUNGEON_MAP_DATA_Z][DUNGEON_MAP_DATA_X];

	//! �}�X�̒��S���W
	D3DXVECTOR3 centerPosition[DUNGEON_MAP_DATA_Z][DUNGEON_MAP_DATA_X];

	//! �����̃C���X�^���X
	std::list<Room*> rooms;

	//! ��搔
	int rectCount;

};