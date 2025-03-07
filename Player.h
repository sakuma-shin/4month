#pragma once
#include <KamataEngine.h>
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include <input/Input.h>

class Map;

class Player {

public:

	~Player();

	void Initialize(KamataEngine::Model* model,uint32_t textureHandle,KamataEngine::Camera* camera);

	void Update(Map* map);

	void Draw(KamataEngine::Camera* camera);

	KamataEngine::Vector3 GetPosition() const { return worldTransform_.translation_; }

	const KamataEngine::WorldTransform& GetWorldTransform() const { return worldTransform_; }

	// プレイヤーの位置を設定する
	void SetPosition(const KamataEngine::Vector3& position) { worldTransform_.translation_ = position; }

	KamataEngine::Vector3 GetRotation() const { return worldTransform_.rotation_; }

	void SetMap(Map* map) { map_ = map; }

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

};