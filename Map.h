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
#include"Light.h"
#include "door.h"
#include<list>
#include "Target.h"
#include "mirror.h"
#include "Player.h"
#include "Prism.h"

class mirror;

class Prism;

class Map {
public:
	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera, int stagenumber);
	void Update(Player* player);
	void Draw();
	void readCSV();

	int CheckCollision(KamataEngine::Vector3 pos);
	void Reorldtransform();

	std::vector<KamataEngine::Vector3> GetTilePositionsInRange(int min, int max);
	std::vector<Light::GrowType> GetMirrorTypesInRange();

private:

	int Digit(int number);

	int Digitnamber(int number);

	int UnFirstnumber(int number);

	std::vector<Target*> Gettargetlist() { 
		return target_;
	}



	private:
	std::string filename;
	static const int MaxX = 10;
	static const int MaxY = 15;
	int map[MaxX][MaxY];
	//ブロックの大きさ
	KamataEngine::Vector3 Size = { 2,2,2 };
	// ワールド変換データ
	std::vector<KamataEngine::WorldTransform*> worldTransform_;
	// モデル
	KamataEngine::Model* model_;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	uint32_t walltextureHandle_ = 0u;

	KamataEngine::Camera* camera_;

	KamataEngine::Model* goalmodel_;

	KamataEngine::Model* prismmodel_;

	KamataEngine::Model* doormodel_;
	
	std::vector<door*> door_;

	std::vector<Target*> target_;

	std::vector<mirror*> mirror_;
  
	std::vector<Prism*> prism_;
  
	int doorcount = 0;
	int targetcount = 0;

	int mirrorcount = 0;

	int prismcount = 0;

};
