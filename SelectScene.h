#pragma once
#include "base/DirectXCommon.h"
#include <KamataEngine.h>
using namespace KamataEngine;

class SelectScene {
public:
	~SelectScene();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() { return isFinished_; }

	bool IsTutorial() { return isTutorial_; }

	Input* GetInput() { return input_; }

	int SelectStage();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool isFinished_ = false;
	bool isTutorial_ = false;

	uint32_t textureHandle_ = 0u;
	Sprite* sprite_ = nullptr;

	int stageNum_ = 1;
};
