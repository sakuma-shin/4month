#pragma once
#include <2d/Sprite.h>
#include <KamataEngine.h>

using namespace KamataEngine;

class skydome {
public:
	~skydome();

	void Initialize(Camera* camera);
	void Update();
	void Draw();

private:
	WorldTransform worldtransform_;
	Model* model_ = new Model;
	Camera* camera_;
	uint32_t textureReticle = 0u;
	Sprite* Reticle_[5];
	Sprite* Reticle2_[5];
	float velo = 0.0f;
};
