#pragma once
#include <KamataEngine.h>
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include <input/Input.h>

class Map;

//マップとの当たり判定
struct CollisionMapInfo {

	bool hitWall = false;
	KamataEngine::Vector3 move;

};

//角
enum Corner {

	kRightBottom,
	kLeftBottom,
	kRightTop,
	kLeftTop,

	kNumCorner

};

class Player {

public:

	~Player();

	void Initialize(KamataEngine::Model* model,uint32_t textureHandle,KamataEngine::Camera* camera);

	void Update();

	void Draw(KamataEngine::Camera* camera);

	KamataEngine::Vector3 GetPosition() const { return worldTransform_.translation_; }

	// プレイヤーの位置を設定する
	void SetPosition(const KamataEngine::Vector3& position) { worldTransform_.translation_ = position; }

	KamataEngine::Vector3 GetRotation() const { return worldTransform_.rotation_; }

	void SetMapChipField(Map* map) { map_ = map; }

	void InputMove();

	void CheckMapCollision(CollisionMapInfo& info);

	void CheckMapCollisionTop(CollisionMapInfo& info);

	void CheckMapCollisionBottom(CollisionMapInfo& info);

	void CheckMapCollisionLeft(CollisionMapInfo& info);

	void CheckMapCollisionRight(CollisionMapInfo& info);

	KamataEngine::Vector3 CornerPosition(const KamataEngine::Vector3& center, Corner corner);

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

	//マップチップフィールド
	Map* map_ = nullptr;

	//判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

};