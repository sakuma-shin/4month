#pragma once
#include <KamataEngine.h>
#include <3d/WorldTransform.h>
#include "3D/Model.h"

class Player {

public:

	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	void Update();

	void Draw();

private:

//ワールド変換
	KamataEngine::WorldTransform worldTransform_;

//モデル
	KamataEngine::Model* model_ = nullptr;

//カメラ
	KamataEngine::Camera* camera_ = nullptr;



};