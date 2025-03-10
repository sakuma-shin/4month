#pragma once
#include <KamataEngine.h>
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include"math/Vector2.h"
#include "Player.h"
#include <input/Input.h>

class mirror {
public:
	void Initialize(KamataEngine::WorldTransform* worldtransform);
	void Update(Player* player);
	void Draw(int i,KamataEngine::Camera* camera);
	bool isInsideRhombus(KamataEngine::Vector3 mirror, KamataEngine::Vector3 player);
	KamataEngine::Vector3 Getpos() { 
		return worldtransform_->translation_;
	}


	private:
	KamataEngine::WorldTransform* worldtransform_;

	KamataEngine::Model* mirrormodel_;

	KamataEngine::Model* mirrormodel2_;
	Player* player_;

	KamataEngine::Input* input_ = nullptr;

	uint32_t textureHandle_ = 0u;
};
