#pragma once
#include "KamataEngine.h"

#include "Player.h"
#include "CameraAngle.h"

#include "Light.h"
#include<list>

#include "Map.h"

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

	void LightCreate(Light::GrowType type, Vector3 pos);

	bool IsFinished() { return isFinished_; }

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

	bool isFinished_ = false;

	//ライト
	std::list<Light*> lights_;
	/*Sprite* lightSprite_ = nullptr;*/
	uint32_t lightTextureHandle_ = 0u;
	Model* lightModel_ = nullptr;

	Map* map_ = nullptr;

	Model* mapModel_ = nullptr;


};
