#pragma once
#include "KamataEngine.h"
#include <input/Input.h>

class Color {

public:

	void Initialize();

	void Update();

	void Draw();

	void SetColor(int red, int blue, int green);

	//紫を分解
	void SplitColor1(int& color1, int& color2);

private:

	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Camera* camera_ = nullptr;

	//入力
	KamataEngine::Input* input_ = nullptr;

	int red_ = 0;
	int blue_ = 0;
	int green_ = 0;

	//テクスチャ
	uint32_t redTextureHandle_ = 0u;
	uint32_t blueTextureHandle_ = 0u;
	uint32_t greenTextureHandle_ = 0u;

	uint32_t purpleTextureHandle_ = 0u;

	bool isSplit = false;

};