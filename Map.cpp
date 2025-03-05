#include "Map.h"
using namespace KamataEngine;

void Map::Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera) {
	// NULLチェック
	assert(model);
	
	// 引数の内容をメンバ変数に記録
	this->model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;

	Size = {2,2,2};
	walltextureHandle_= TextureManager::Load("uvChecker.png");
	

	filename = "Resources/map/01.csv"; // 読み込むCSVファイル名
	readCSV();
	
	worldTransform_.resize(MaxX*MaxY); 
	for (uint32_t i = 0; i < MaxX * MaxY; ++i) {
		worldTransform_[i] = new WorldTransform;
		worldTransform_[i]->Initialize();
		worldTransform_[i]->translation_.x = (i % MaxX) * Size.x;
		if (map[i % MaxX][i / MaxX] == 10) {
			worldTransform_[i]->translation_.y = 0;
		} else {
			worldTransform_[i]->translation_.y = 2;
		}
		
		worldTransform_[i]->translation_.z = int(i / MaxX) * Size.z;
	}

	for (WorldTransform* worldTransformBlock : worldTransform_) {
		worldTransformBlock->TransferMatrix();
		worldTransformBlock->UpdateMatrix();
	}
}

void Map::Update() {
	
}

void Map::Draw() {
	for (WorldTransform* worldTransformBlock : worldTransform_) {
		if (worldTransformBlock->translation_.y > 0) {
			model_->Draw(*worldTransformBlock, *camera_, walltextureHandle_);
		} else {
			model_->Draw(*worldTransformBlock, *camera_, textureHandle_);
		}
		
	}
}

void Map::readCSV() {
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}
	int i = 0;
	std::string line;
	while (std::getline(file, line)) { // 1行ずつ読み込む
		std::vector<int> row;
		std::stringstream ss(line);
		std::string cell;

		while (std::getline(ss, cell, ',')) { // カンマで分割
			try {
				row.push_back(std::stoi(cell)); // 文字列をint型に変換
			} catch (const std::exception& e) {
				e;
				std::cerr << "Conversion error: " << cell << " is not an integer." << std::endl;
			}
		}

		// 読み込んだ整数データを出力
		for (const auto& value : row) {
			std::cout << value << " ";
		}
		std::cout << std::endl;

		for (int j = 0; j < (int)row.size(); j++) {
			map[i][j] = row[j];
		}
		i++;
	}

	file.close();
}

int Map::CheckCollision(KamataEngine::Vector3 pos) { // マップのX,Z座標を計算
	int mapX = static_cast<int>(pos.x / Size.x);
	int mapZ = static_cast<int>(pos.z / Size.z);

	// **範囲外なら即「衝突」として処理**
	if (mapX < 0 || mapX >= MaxX || mapZ < 0 || mapZ >= MaxY) {
		return 1; // マップ外は壁扱い
	}

	// マップの範囲内かチェック
	if (mapX >= 0 && mapX < MaxX && mapZ >= 0 && mapZ < MaxY) {
		// その位置のマップ値が 10 なら壁
		if (map[mapX][mapZ] == 10) {
			return 1;
		}
	}
	// 範囲外も壁とみなす
	return 0;
}
