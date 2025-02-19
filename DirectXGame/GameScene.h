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

	//モデル
	Model* model_ = nullptr;

	//ワールドトランスフォーム
	WorldTransform worldTransform_;

	// カメラ
	Camera camera_;

	//自キャラ
	Player* player_ = nullptr;

};
