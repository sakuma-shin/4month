#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class Fading {
public:
	void Initialize();

	void Update();

	void Draw();

	void Fade();

	int GetAlpha() { return alpha_; }

private:
	DirectXCommon* dxCommon_ = nullptr;

	uint32_t textureHandle_ = 0u;

	Sprite* sprite_ = nullptr;

	int alpha_ = 0;

	bool isFade_ = false;
	bool isChanged_ = false;
};
