#include "Map.h"

using namespace KamataEngine;

void Map::Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera) {
	// NULLチェック
	assert(model);
	
	// 引数の内容をメンバ変数に記録
	//this->model_ = model;

	model_ = Model::CreateFromOBJ("wall", true);
	textureHandle_ = textureHandle;
	camera_ = camera;

	Size = {2,2,2};
	walltextureHandle_= TextureManager::Load("white1x1.png");
	
	textureHandle_ = TextureManager::Load("uvChecker.png");

	mirrormodel_->Create();
	mirrormodel_= Model::CreateFromOBJ("mirorr",true);

	mirrormodel2_->Create();
	mirrormodel2_ = Model::CreateFromOBJ("mirorr2", true);

	goalmodel_ = Model::CreateFromOBJ("gole", true);

	prismmodel_ = Model::CreateFromOBJ("prism", true);

	filename = "Resources/map/01.csv"; // 読み込むCSVファイル名
	readCSV();
	
	worldTransform_.resize(MaxX*MaxY); 
	for (uint32_t i = 0; i < MaxX * MaxY; ++i) {
		worldTransform_[i] = new WorldTransform;
		worldTransform_[i]->Initialize();
		worldTransform_[i]->translation_.x = (i % MaxX) * Size.x;
		if (map[i % MaxX][i / MaxX] != 0  &&map[i % MaxX][i / MaxX] != 1) {
			worldTransform_[i]->translation_.y = 0;
		} else {
			worldTransform_[i]->translation_.y = 2;
		}
		if (Digit(map[i % MaxX][i / MaxX]) == 7) {
			door* newdoor = new door;
			newdoor->Initialize(UnFirstnumber(map[i % MaxX][i / MaxX]));
			door_.push_back(newdoor);

		}
		
		worldTransform_[i]->translation_.z = int(i / MaxX) * Size.z;
	}

	for (WorldTransform* worldTransformBlock : worldTransform_) {
		worldTransformBlock->TransferMatrix();
		worldTransformBlock->UpdateMatrix();
	}
}

void Map::Update() { 
	doorcount = 0;
	for (door* door : door_) {
		door->Update();
	}
}

void Map::Draw() {
	int i = 0;
	for (WorldTransform* worldTransformBlock : worldTransform_) {
		if (map[i % MaxX][i / MaxX] == 8) {
			model_->Draw(*worldTransformBlock, *camera_);
		} else if (map[i % MaxX][i / MaxX] == 2) {
			goalmodel_->Draw(*worldTransformBlock, *camera_);
		} else if (Digit(map[i % MaxX][i / MaxX]) == 7) {
			door_[doorcount]->Draw(worldTransformBlock, camera_);
			doorcount++;
		}
		else if (map[i % MaxX][i / MaxX] == 31) {
			mirrormodel2_->Draw(*worldTransformBlock, *camera_);
		}else if (map[i % MaxX][i / MaxX] == 32) {
			mirrormodel_->Draw(*worldTransformBlock, *camera_);
		} else if (map[i % MaxX][i / MaxX] == 9) {
			prismmodel_->Draw(*worldTransformBlock, *camera_);
		} else if (map[i % MaxX][i / MaxX] == 0) {
			model_->Draw(*worldTransformBlock, *camera_, walltextureHandle_);
		} 
		else {
			model_->Draw(*worldTransformBlock, *camera_,textureHandle_);
		}
		i++;
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

int Map::Digit(int number) { 
	if (number / 10 < 1) {
		return number;
	}
	int k = 0;
	for (; number / 10 >= 1; k++) {
		number = number / 10;
	}
	return number;

}

int Map::Digitnamber(int number) { 
	if (number / 10 < 1) {
		return number;
	}
	int k = 0;
	for (; number / 10 >= 1; k++) {
		number = number / 10;
	}
	return k;
}

int Map::UnFirstnumber(int number) { 
	int k = 1;
	for (int i = 0; i < Digitnamber(number); i++) {
		k *= 10;
	}

	return number - Digit(number) * (k);
}

