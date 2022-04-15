//!============================================================
//!
//!  @file    : Scene.h
//!  @brief   : �V�[���N���X�̃w�b�_�[�t�@�C��
//!  @author  : ���c �z��
//!  @details : �^�C�g���V�[����Q�[���V�[���̌p�����̃N���X
//!             �Q�[���I�u�W�F�N�g�̊Ǘ����s��
//!
//!============================================================
#pragma once


//============================================================
//�@�C���N���[�h
//============================================================
#include <list>
#include <vector>
#include <typeinfo>
#include "GameObject.h"
#include "Camera.h"


//!===========================================================
//! @enum Layer
//! @brief   : ���C���[�񋓑�
//!===========================================================
enum Layer
{
	CAMERA_LAYER,          // �J����
	NO_ZSORT_OBJECT_LAYER, // Z�\�[�g�����Ȃ�3D�I�u�W�F�N�g
	OBJECT3D_LAYER,        // 3D�I�u�W�F�N�g
	OBJECT2D_LAYER,        // 2D�I�u�W�F�N�g
	LAYER_COUNT            // ���C���[��
};


//!===========================================================
//! @class Scene
//! @brief   : �p�����̃V�[���N���X
//!===========================================================
class Scene
{
public:

	//!-------------------------------------------------------
	//! @fn      : Scene()
	//! @brief   : �R���X�g���N�^
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������e�Ȃ�
	//!-------------------------------------------------------
	Scene(){}

	//!-------------------------------------------------------
	//! @fn      : ~Scene()
	//! @brief   : �f�X�g���N�^
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������z�֐�
	//!-------------------------------------------------------
	virtual ~Scene(){}

	//!-------------------------------------------------------
	//! @fn      : Init()
	//! @brief   : ������������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �������z�֐�
	//!-------------------------------------------------------
	virtual void Init() = 0;

	//!-------------------------------------------------------
	//! @fn      : Uninit()
	//! @brief   : �I������������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �I�u�W�F�N�g�̉���ƃ��X�g�̃N���A���s��
	//!-------------------------------------------------------
	virtual void Uninit()
	{
		for (int i = 0; i < LAYER_COUNT; i++)
		{
			for (GameObject* object : gameObject[i])
			{
				object->Uninit();
				delete object;
			}

			// ���X�g�̃N���A
			gameObject[i].clear();
		}
	}

	//!-------------------------------------------------------
	//! @fn      : Update()
	//! @brief   : �X�V����������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �I�u�W�F�N�g�̍X�V�����Ɖ���\�񂵂��I�u�W�F�N�g�̉��������
	//!-------------------------------------------------------
	virtual void Update()
	{
		for (int i = 0; i < LAYER_COUNT; i++)
		{
			// �͈�for���[�v
			for (GameObject* object : gameObject[i])
			{
				object->Update();
			}

			// �����_��
			gameObject[i].remove_if([](GameObject* object) {return object->Destroy(); });
		}
	}

	//!-------------------------------------------------------
	//! @fn      : Draw()
	//! @brief   : �`�揈��������
	//! @param   : �Ȃ�
	//! @return  : �Ȃ�
	//! @details : �I�u�W�F�N�g�̕`�揈��
	//!-------------------------------------------------------
	virtual void Draw()
	{
		// Z�\�[�g�i�J�����̍��W����ɂ��ċ߂����ɃI�u�W�F�N�g���\�[�g�j
		gameObject[OBJECT3D_LAYER].sort
		(
			[this](GameObject* object1, GameObject* object2)
			{
				// �J�����I�u�W�F�N�g��ێ�
				GameObject* cameraObject = GetGameObject<Camera>(CAMERA_LAYER);

				// object1 �� cameraObject �Ƃ̍����v�Z
				float o1XDis = cameraObject->GetPosition().x - object1->GetPosition().x;
				float o1YDis = cameraObject->GetPosition().y - object1->GetPosition().y;
				float o1ZDis = cameraObject->GetPosition().z - object1->GetPosition().z;

				// object2 �� cameraObject �Ƃ̍����v�Z
				float o2XDis = cameraObject->GetPosition().x - object2->GetPosition().x;
				float o2YDis = cameraObject->GetPosition().y - object2->GetPosition().y;
				float o2ZDis = cameraObject->GetPosition().z - object2->GetPosition().z;

				// ���ꂼ��̍��W�̓����r����
				// object1�̕���cameraObject�ɋ߂��ꍇ true ��Ԃ�
				return (o1XDis * o1XDis + o1YDis * o1YDis + o1ZDis * o1ZDis) > (o2XDis * o2XDis + o2YDis * o2YDis + o2ZDis * o2ZDis);
			}
		);

		// �`��
		for (int i = 0; i < LAYER_COUNT; i++)
		{
			for (GameObject* object : gameObject[i])
			{
				object->Draw();
			}
		}
	}

	//!-------------------------------------------------------
	//! @fn      : AddGameObject(int Layer)
	//! @brief   : �I�u�W�F�N�g�̒ǉ�������
	//! @param   : Layer...���C���[�̔ԍ�
	//!            0�̓J�����A1��3D�I�u�W�F�N�g�A2��2D�I�u�W�F�N�g
	//! @return  : �ǉ������Q�[���I�u�W�F�N�g
	//! @details : �I�u�W�F�N�g�̒ǉ������i�e���v���[�g�֐��j
	//!-------------------------------------------------------
	template <typename T>
	T* AddGameObject(int Layer)
	{
		T* addGameObject = new T();
		addGameObject->Init();
		gameObject[Layer].push_back(addGameObject);

		return addGameObject;
	}

	//!-------------------------------------------------------
	//! @fn      : GetGameObject(int Layer)
	//! @brief   : �P�̂̃I�u�W�F�N�g�̏����擾����
	//! @param   : Layer...���C���[�̔ԍ�
	//!            0�̓J�����A1��3D�I�u�W�F�N�g�A2��2D�I�u�W�F�N�g
	//! @return  : �擾�����I�u�W�F�N�g�A�擾�ł��Ȃ��ꍇ��NULL��Ԃ�
	//! @details : �P�̃I�u�W�F�N�g�̏��擾�i�e���v���[�g�֐��j
	//!-------------------------------------------------------
	template <typename T>
	T* GetGameObject(int Layer)
	{
		for (GameObject* object : gameObject[Layer])
		{
			if (typeid(*object) == typeid(T)) // �^�𒲂ׂ�iRTTI���I�^���j
			{
				return (T*)object;
			}
		}

		return NULL;
	}

	//!-------------------------------------------------------
	//! @fn      : GetGameObjects(int Layer)
	//! @brief   : �����̃I�u�W�F�N�g�̏����擾����
	//! @param   : Layer...���C���[�̔ԍ�
	//!            0�̓J�����A1��3D�I�u�W�F�N�g�A2��2D�I�u�W�F�N�g
	//! @return  : �擾�����I�u�W�F�N�g
	//! @details : �����I�u�W�F�N�g�̏��擾�i�e���v���[�g�֐��j
	//!-------------------------------------------------------
	template <typename T>
	std::vector<T*> GetGameObjects(int Layer)
	{
		std::vector<T*> objects; // STL�̔z��
		for (GameObject* object : gameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}

		return objects;
	}

protected:

	//! �Q�[���I�u�W�F�N�g���i�[���郊�X�g�̕ϐ��iSTL�̃��X�g�\���j
	std::list<GameObject*> gameObject[LAYER_COUNT];
};
