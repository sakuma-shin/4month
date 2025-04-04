#pragma once
#include "base/DirectXCommon.h"
#include <KamataEngine.h>
#include "Fade.h"
using namespace KamataEngine;

class SelectScene {
public:
	~SelectScene();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() { return isFinished_; }
	bool IsExplanation() { return isExplanation_; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool isFinished_ = false;
	bool isExplanation_ = false;

	Fade* fade_ = nullptr;

	FadePhase phase_ = FadePhase::kFadeIn;

};
