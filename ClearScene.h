#pragma once
#include "base/DirectXCommon.h"
#include <KamataEngine.h>
#include "skydome.h"
using namespace KamataEngine;

class ClearScene {

public:
	~ClearScene();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() { return isFinished_; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool isFinished_ = false;

	uint32_t textureHandle_ = 0u;
	Sprite* sprite_ = nullptr;

	skydome* skydome_ = nullptr;

	Camera camera_;
};