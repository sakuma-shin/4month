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

enum class MapChipType {

	kBlank, // 空白
	kBlock, // ブロック

};

struct MapChipData {

	std::vector<std::vector<MapChipType>> data;

};

class Map {
public:
	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera);
	void Update();
	void Draw();
	void readCSV();

	KamataEngine::Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t zIndex);
	
private:
	std::string filename;
	static const int MaxX = 10; //10個並ぶ
	static const int MaxY = 15; //15個並ぶ

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

	// 1ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;

	// ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;


	KamataEngine::Model* mirrormodel_;

	KamataEngine::Model* mirrormodel2_;

	KamataEngine::Model* golemodel_;

	KamataEngine::Model* prismmodel_;
	KamataEngine::Model* doormodel_;
	
};
