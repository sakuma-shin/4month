#pragma once
#include "KamataEngine.h"
#include "Light.h"
#include<list>

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

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// カメラ
	Camera camera_;

	//ライト
	std::list<Light*> lights_;
	/*Sprite* lightSprite_ = nullptr;*/
	uint32_t lightTextureHandle_ = 0u;
};
