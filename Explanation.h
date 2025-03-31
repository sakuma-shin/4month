#pragma once
#include <KamataEngine.h>

class Explanation {

public:

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() { return isFinished_; }

private:

	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	bool isFinished_ = false;

};