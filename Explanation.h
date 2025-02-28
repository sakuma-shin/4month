#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;

class ExplanationScene {

public:

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() { return isFinished_; }

private:

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool isFinished_ = false;

};