#pragma once
#include "KamataEngine.h"
#include "Player.h"

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

	// 3Dモデル
	Model* model_ = nullptr;

	//プレイヤー
	Player* player_ = nullptr;

	// カメラ
	Camera camera_;
};
