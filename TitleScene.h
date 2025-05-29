#pragma once
#include "Fade.h"
#include "base/DirectXCommon.h"
#include <KamataEngine.h>
#include "skydome.h"
using namespace KamataEngine;

class TitleScene {

public:
	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() { return isFinished_; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool isFinished_ = false;

	Fade* fade_ = nullptr;

	FadePhase phase_ = FadePhase::kFadeIn;

	float counter = 0.0f;

	uint32_t textureHandle_ = 0u;
	Sprite* sprite_ = nullptr;

	Model* mirrorModel_ = nullptr;
	Model* lightModel_ = nullptr;

	uint32_t sceneChangeSoundHandle_ = 0u;

	WorldTransform mirrorWorldTransform_;

	WorldTransform lightWorldTransform_;

	WorldTransform lightWorldTransform2_;

	ObjectColor lightColor_;

	Camera camera_;

	uint32_t mirrorGH = 0u;

	skydome* skydome_ = nullptr;


};