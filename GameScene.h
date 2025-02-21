#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "CameraAngle.h"

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

	//モデル
	Model* playerModel_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	//プレイヤー
	Player* player_ = nullptr;

	// カメラ
	Camera camera_;

	//カメラアングル
	CameraAngle* cameraAngle_ = nullptr;

};
