#pragma once
#include <KamataEngine.h>
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include"math/Vector2.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "door.h"
#include<list>

class Map {
public:
	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera);
	void Update();
	void Draw();
	void readCSV();
	
private:
	std::string filename;
	static const int MaxX = 10;
	static const int MaxY = 15;
	int map[MaxX][MaxY];
	//ブロックの大きさ
	KamataEngine::Vector3 Size;
	// ワールド変換データ
	std::vector<KamataEngine::WorldTransform*> worldTransform_;
	// モデル
	KamataEngine::Model* model_;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	uint32_t walltextureHandle_ = 0u;

	KamataEngine::Camera* camera_;

	KamataEngine::Model* mirrormodel_;

	KamataEngine::Model* mirrormodel2_;

	KamataEngine::Model* goalmodel_;

	KamataEngine::Model* prismmodel_;
	
	std::vector<door*> door_;
	
	int doorcount = 0;
};
