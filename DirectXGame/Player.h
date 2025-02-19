#pragma once
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"

class Player {

public:

	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera);

	void Update();

	void Draw();

private:

//ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

//モデル
	KamataEngine::Model* model_ = nullptr;

//カメラ
	KamataEngine::Camera* camera_ = nullptr;

//テクスチャハンドル
uint32_t  textureHandle_ = 0u;

};