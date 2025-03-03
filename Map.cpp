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

IndexSet Map::GetMapChipIndexSetByPosition(const Vector3& position)
{

	IndexSet indexSet = {};
	indexSet.xIndex = static_cast<uint32_t>((position.x + kBlockWidth / 2.0f) / kBlockWidth);

	indexSet.yIndex = kNumBlockVirtical - 1 -
		static_cast<uint32_t>((position.y + kBlockHeight / 2.0f) / kBlockHeight);

	return indexSet;

}
