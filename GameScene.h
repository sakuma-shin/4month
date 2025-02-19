#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class GameScene {
public:
	// コンストラクタ
	GameScene();

	// デストラクタ
	~GameScene();

	void Initialize();

	void Update();

	void Draw();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// テクスチャハンドル
	uint32_t playerTextureHandle_ = 0;

	// モデル
	Model* playerModel_ = nullptr;

	// カメラ
	Camera camera_;
};
