#include "Map.h"

using namespace KamataEngine;

void Map::Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera,int stagenumber) {
	// NULLチェック
	assert(model);

	//Size = { 2,2,2 };

	// 引数の内容をメンバ変数に記録
	//this->model_ = model;

	model_ = Model::CreateFromOBJ("wall", true);
	textureHandle_ = textureHandle;
	camera_ = camera;

	walltextureHandle_= TextureManager::Load("white1x1.png");
	
	textureHandle_ = TextureManager::Load("uvChecker.png");

	//mirrormodel_->Create();
	mirrormodel_= Model::CreateFromOBJ("mirorr",true);

	//mirrormodel2_->Create();
	mirrormodel2_ = Model::CreateFromOBJ("mirorr2", true);

	goalmodel_ = Model::CreateFromOBJ("gole", true);

	//prismmodel_ = Model::CreateFromOBJ("prism", true);

	//doormodel_ = Model::CreateFromOBJ("door", true);
	
	if (stagenumber == 1) {
		filename = "Resources/map/01.csv"; // 読み込むCSVファイル名
	} else if (stagenumber == 2) {
		filename = "Resources/map/debugMap1.csv"; // 読み込むCSVファイル名
	} else if (stagenumber == 3) {
		filename = "Resources/map/debugMap2.csv"; // 読み込むCSVファイル名
	} else if (stagenumber == 4) {
		filename = "Resources/map/debugMap3.csv"; // 読み込むCSVファイル名
	} else if (stagenumber == 5) {
		filename = "Resources/map/debugMap4.csv"; // 読み込むCSVファイル名
	}
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
		
		if (Digit(map[i % MaxX][i / MaxX]) == 6) {
			Target* newtarget = new Target;
			newtarget->Initialize(map[i % MaxX][i / MaxX], worldTransform_[i]);
			target_.push_back(newtarget);
		}
		
		worldTransform_[i]->translation_.z = int(i / MaxX) * Size.z;
	}
	for (uint32_t i = 0; i < MaxX * MaxY; ++i) {
		if (Digit(map[i % MaxX][i / MaxX]) == 7) {
			door* newdoor = new door;
			newdoor->Initialize(UnFirstnumber(map[i % MaxX][i / MaxX]),target_);
			door_.push_back(newdoor);

		}
	}

	for (uint32_t i = 0; i < MaxX * MaxY; ++i) {
		if (Digit(map[i % MaxX][i / MaxX]) == 9) {
			Prism* newprism = new Prism;
			newprism->Initialize(UnFirstnumber(map[i % MaxX][i / MaxX]));
			prism_.push_back(newprism);
		}
	}

	for (WorldTransform* worldTransformBlock : worldTransform_) {
		worldTransformBlock->TransferMatrix();
		worldTransformBlock->UpdateMatrix();
	}
}

void Map::Update() { 
	doorcount = 0;
	targetcount = 0;
	prismcount = 0;
	for (door* door : door_) {
		door->Update(target_);
	}
	for (Target* target : target_) { //
		target->Update();
	}
	for (Prism* prism : prism_) {
		prism->Update();
	}
}

void Map::Draw() {
	int i = 0;
	for (WorldTransform* worldTransformBlock : worldTransform_) {
		if (map[i % MaxX][i / MaxX] == 8) {
			model_->Draw(*worldTransformBlock, *camera_);
		} else if (map[i % MaxX][i / MaxX] == 2) {
			goalmodel_->Draw(*worldTransformBlock, *camera_);
		} else if (Digit(map[i % MaxX][i / MaxX]) == 6) {
			target_[targetcount]->Draw(camera_);
			targetcount++;
		} else if (Digit(map[i % MaxX][i / MaxX]) == 7) {
			door_[doorcount]->Draw(worldTransformBlock, camera_);
			doorcount++;
		}
		else if (map[i % MaxX][i / MaxX] == 31) {
			mirrormodel2_->Draw(*worldTransformBlock, *camera_);
		}else if (map[i % MaxX][i / MaxX] == 32) {
			mirrormodel_->Draw(*worldTransformBlock, *camera_);
		} else if (map[i % MaxX][i / MaxX] == 9) {
			prism_[prismcount]->Draw(worldTransformBlock, camera_);
			prismcount++;
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
		return 0;
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



int Map::CheckCollision(KamataEngine::Vector3 pos) { // マップのX,Z座標を計算


	int mapX = static_cast<int>(pos.x / Size.x);
	int mapZ = static_cast<int>(pos.z / Size.z);
	
	if (map == nullptr) {
		// エラーハンドリング
		return 1; // 衝突と見なす
	}

	// 範囲外なら即「衝突」として処理
	if (mapX < 0 || mapX >= MaxX || mapZ < 0 || mapZ >= MaxY) {
		return 1; // マップ外は壁扱い
	}

	// マップ内での衝突チェック
	if (map[mapX][mapZ] == 8) { // その位置のマップ値が 10 なら壁
		return 1;
	}

	// 範囲内かつ衝突しない場合は「衝突なし」
	return 0;

}
