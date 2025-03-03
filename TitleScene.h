#pragma once
#include <KamataEngine.h>
#include "base/DirectXCommon.h"
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

};