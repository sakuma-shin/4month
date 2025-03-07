#pragma once
#include <KamataEngine.h>
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include <input/Input.h>
#include "Map.h"

class Map;

class Player {

public:

	struct CollisionMapInfo {

		bool isWallHitX = false;
		bool isHitWallZ = false;

		KamataEngine::Vector3 move;

	};

	~Player();

	void Initialize(KamataEngine::Model* model,uint32_t textureHandle,KamataEngine::Camera* camera,const KamataEngine::Vector3& position);

	void Update();

	void Draw(KamataEngine::Camera* camera);

	KamataEngine::Vector3 GetPosition() const { return worldTransform_.translation_; }

	// プレイヤーの位置を設定する
	void SetPosition(const KamataEngine::Vector3& position) { worldTransform_.translation_ = position; }

	KamataEngine::Vector3 GetRotation() const { return worldTransform_.rotation_; }

	void SetMapChipField(Map* mapChipField) { map_ = mapChipField; }

	void InputMove();

	void CheckMapCollision(CollisionMapInfo& info);

private:

	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Model* model_ = nullptr;	
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	KamataEngine::Camera* camera_ = nullptr;

	//入力
	KamataEngine::Input* input_ = nullptr;

	Map* map_ = nullptr;

	KamataEngine::Vector3 velocity_ = {};

	static inline const float kAcceleration = 0.01f;

	static inline const float kAttenuation = 0.99f;

	static inline const float kLimitSpeed = 0.5f;

	//キャラクターの当たりサイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;


};