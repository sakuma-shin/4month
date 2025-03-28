#pragma once
#include "KamataEngine.h"
#include <input/Input.h>

class Color {

public:
	void Initialize(KamataEngine::Model* model, uint32_t purpleTextureHandle, uint32_t redTextureHandle, uint32_t blueTextureHandle, uint32_t greenTextureHandle);

	void Update();

	void Draw(KamataEngine::Camera* camera);

private:
	// ワールド変換データ
	KamataEngine::WorldTransform redWorldTransform_;
	KamataEngine::WorldTransform blueWorldTransform_;
	KamataEngine::WorldTransform greenWorldTransform_;
	KamataEngine::WorldTransform purpleWorldTransform_;

	KamataEngine::Camera* camera_ = nullptr;

	// 入力
	KamataEngine::Input* input_ = nullptr;

	KamataEngine::Model* model_ = nullptr;

	int red_ = 0;
	int blue_ = 0;
	int green_ = 0;

	// テクスチャ
	uint32_t redTextureHandle_ = 0u;
	uint32_t blueTextureHandle_ = 0u;
	uint32_t greenTextureHandle_ = 0u;

	uint32_t purpleTextureHandle_ = 0u;

	bool isSplit = false;
};