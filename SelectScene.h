#pragma once
#include "Fade.h"
#include "base/DirectXCommon.h"
#include "skydome.h"
#include <KamataEngine.h>
using namespace KamataEngine;

class SelectScene {
public:
	~SelectScene();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() { return isFinished_; }

	Input* GetInput() { return input_; }

	int SelectStage();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool isFinished_ = false;

	const int stageNum = 4;

	uint32_t numTextureHandle_[5] = {};
	uint32_t textureHandle_=0u;
	Sprite* numSprite_[5] = {nullptr};
	Sprite* sprite_ = {nullptr};

	skydome* skydome_ = nullptr;

	uint32_t loadingTextureHandle_ = {};
	Sprite* loadingSprite_ = nullptr;

	int stageNum_ = 1;

	Fade* fade_ = nullptr;

	FadePhase phase_ = FadePhase::kFadeIn;

	const float loadingTime = 10.0f;

	float counter_ = 0.0f;

	// カメラ
	Camera camera_;
};
