#pragma once
#include <KamataEngine.h>
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include <input/Input.h>

class Player {

public:

	~Player();

	void Initialize(KamataEngine::Model* model,uint32_t textureHandle,KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	void Update();

	void Draw(KamataEngine::Camera* camera);

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

	KamataEngine::Vector3 velocity_ = {};

	static inline const float kAcceleration = 0.01f;

	static inline const float kAttenuation = 0.99f;

	static inline const float kLimitSpeed = 0.5f;

};