#pragma once
#include <KamataEngine.h>
#include <2D/Sprite.h>

class Explanation {

public:

	~Explanation();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() { return isFinished_; }

private:

	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	uint32_t textureHandle_ = 0u;
	KamataEngine::Sprite* sprite_ = nullptr;

	bool isFinished_ = false;

};