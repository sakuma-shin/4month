#include "Map.h"

using namespace KamataEngine;

void Map::Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera, int stagenumber) {
	// NULLチェック
	assert(model);

	// 引数の内容をメンバ変数に記録
	// this->model_ = model;

	model_ = Model::CreateFromOBJ("wall", true);
	textureHandle_ = textureHandle;
	camera_ = camera;

	Size = {2, 2, 2};
	walltextureHandle_ = TextureManager::Load("white1x1.png");

	textureHandle_ = TextureManager::Load("uvChecker.png");

	// mirrormodel_->Create();
	// mirrormodel_= Model::CreateFromOBJ("mirorr",true);

	// mirrormodel2_->Create();
	// mirrormodel2_ = Model::CreateFromOBJ("mirorr2", true);

	goalmodel_ = Model::CreateFromOBJ("gole", true);

	// prismmodel_ = Model::CreateFromOBJ("prism", true);

	// doormodel_ = Model::CreateFromOBJ("door", true);

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

	worldTransform_.resize(MaxX * MaxY);
	for (uint32_t i = 0; i < MaxX * MaxY; ++i) {
		worldTransform_[i] = new WorldTransform;
		worldTransform_[i]->Initialize();
		worldTransform_[i]->translation_.x = (i % MaxX) * Size.x;
		if (map[i % MaxX][i / MaxX] != 0 && map[i % MaxX][i / MaxX] != 1) {
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
			newdoor->Initialize(UnFirstnumber(map[i % MaxX][i / MaxX]), target_);
			door_.push_back(newdoor);
		}
		if (map[i % MaxX][i / MaxX] >= 30 && map[i % MaxX][i / MaxX] <= 34) {
			mirror* newmirror = new mirror;
			newmirror->Initialize(worldTransform_[i], i % MaxX, i / MaxX, this);
			mirror_.push_back(newmirror);
		}
	}

	for (uint32_t i = 0; i < MaxX * MaxY; ++i) {
		if (Digit(map[i % MaxX][i / MaxX]) == 9) {
			Prism* newprism = new Prism;
			newprism->Initialize(map[i % MaxX][i / MaxX], worldTransform_[i], i % MaxX, i / MaxX, this);
			prism_.push_back(newprism);
		}
	}

	for (WorldTransform* worldTransformBlock : worldTransform_) {
		worldTransformBlock->TransferMatrix();
		worldTransformBlock->UpdateMatrix();
	}
}

void Map::Update(Player* player) {
	doorcount = 0;
	mirrorcount = 0;
	targetcount = 0;
	prismcount = 0;
	for (door* door : door_) {
		door->Update(target_);
	}
	for (Target* target : target_) { //
		target->Update();
	}
	int i=0;
	for (mirror* mirrorL : mirror_) { //
		mirrorL->Update(player);
		if (int(mirrorL->Getpos().x / 2.0f) != mirrorL->GetPos(0) || int(mirrorL->Getpos().z / 2.0f) != mirrorL->GetPos(1)) {
			
			if (int(mirrorL->Getpos().x / 2.0f)-mirrorL->GetPos(0) == 1) {
				i = 1;
			}
			else if (int(mirrorL->Getpos().x / 2.0f)-mirrorL->GetPos(0) == -1) {
				i = 2;
			}
			else if (int(mirrorL->Getpos().z / 2.0f) - mirrorL->GetPos(1)==1) {
				i = 3;
			} 
			else if (int(mirrorL->Getpos().z / 2.0f) - mirrorL->GetPos(1)==-1) {
				i = 4;
			}
			
			WorldTransform* dai;
			dai = mirrorL->Getworld();

			int x;
			x=map[mirrorL->GetPos(0)][mirrorL->GetPos(1)];
			map[mirrorL->GetPos(0)][mirrorL->GetPos(1)] = map[int(mirrorL->Getpos().x / 2.0f)][int(mirrorL->Getpos().z / 2.0f)];
			map[int(mirrorL->Getpos().x / 2.0f)][int(mirrorL->Getpos().z / 2.0f)] = x;
			mirrorL->PosChange(i);


			std::vector<mirror*> mirrors_;
			for (uint32_t k = 0; k < MaxX * MaxY; ++k) {
				if (map[k % MaxX][k / MaxX] >= 30 && map[k % MaxX][k / MaxX] <= 34) {
					mirror* newmirror = new mirror;
					newmirror->Initialize(worldTransform_[k], k % MaxX, k / MaxX, this);
					mirrors_.push_back(newmirror);
				}
			}
			mirror_ = mirrors_;

			
		}
	}
	if (i != 0) {
		Reorldtransform();
	}

	for (Prism* prism : prism_) {
		prism->Update(player);
		if (!prism->IsSet()) {
			map[prism->GetPos(0)][prism->GetPos(1)] = 0;
		} else if (prism->IsSet()) {
			map[prism->GetPos(0)][prism->GetPos(1)] = prism->ReturnKey();
		}
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
		} else if (map[i % MaxX][i / MaxX] == 31) {
			mirror_[mirrorcount]->Draw(1, camera_);
			mirrorcount++;
		} else if (map[i % MaxX][i / MaxX] == 32) {
			mirror_[mirrorcount]->Draw(2, camera_);
			mirrorcount++;
		} else if (Digit(map[i % MaxX][i / MaxX]) == 9) {
			prism_[prismcount]->Draw(camera_);
			prismcount++;
		} else if (map[i % MaxX][i / MaxX] == 0) {
			model_->Draw(*worldTransformBlock, *camera_, walltextureHandle_);
		} else {
			model_->Draw(*worldTransformBlock, *camera_, textureHandle_);
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

	// マップの範囲内かチェック
	if (mapX >= 0 && mapX < MaxX && mapZ >= 0 && mapZ < MaxY) {

		// その位置のマップ値が 8 なら壁
		switch (map[mapX][mapZ]) {

			// マップ番号と同じ数字を返す
		case 8:
			// 壁
			return 8;
			break;

		case 31:
			// 右下鏡
			return 31;
			break;

		case 32:
			// 右上鏡
			return 32;
			break;

		case 33:
			// 水平鏡
			return 33;
			break;

		case 34:
			// 垂直鏡
			return 34;
			break;

		case 91:
			// プリズム上
			return 91;
			break;

		case 92:
			// プリズム下
			return 92;
			break;

		case 93:
			// プリズム左
			return 93;
			break;

		case 94:
			// プリズム右
			return 94;
			break;

		case 42:
			// 垂直鏡
			return 42;
			break;
		}
	}

	// 範囲内かつ衝突しない場合は「衝突なし」
	return 0;
}

void Map::Reorldtransform() {
	std::vector<WorldTransform*> world_;
	world_.resize(MaxX * MaxY);
	for (uint32_t i = 0; i < MaxX * MaxY; ++i) {
		world_[i] = new WorldTransform;
		world_[i]->Initialize();
		world_[i]->translation_.x = (i % MaxX) * Size.x;
		if (map[i % MaxX][i / MaxX] != 0 && map[i % MaxX][i / MaxX] != 1) {
			world_[i]->translation_.y = 0;
		} else {
			world_[i]->translation_.y = 2;
		}

		if (Digit(map[i % MaxX][i / MaxX]) == 6) {
			Target* newtarget = new Target;
			newtarget->Initialize(map[i % MaxX][i / MaxX], world_[i]);
			target_.push_back(newtarget);
		}
		world_[i]->translation_.z = int(i / MaxX) * Size.z;
	}
	mirror_.clear();
	for (uint32_t i = 0; i < MaxX * MaxY; ++i) {
		
		if (Digit(map[i % MaxX][i / MaxX]) == 7) {
			door* newdoor = new door;
			newdoor->Initialize(UnFirstnumber(map[i % MaxX][i / MaxX]), target_);
			door_.push_back(newdoor);
		}
		if (map[i % MaxX][i / MaxX] >= 30 && map[i % MaxX][i / MaxX] <= 34) {
			mirror* newmirror = new mirror;
			newmirror->Initialize(world_[i], i % MaxX, i / MaxX, this);
			mirror_.push_back(newmirror);
		}
	}

	for (WorldTransform* worldTransformBlock : world_) {
		worldTransformBlock->TransferMatrix();
		worldTransformBlock->UpdateMatrix();
	}

	worldTransform_ = world_;

}

std::vector<KamataEngine::Vector3> Map::GetTilePositionsInRange(int min, int max) {
	std::vector<KamataEngine::Vector3> positions;

	// マップを走査
	for (int y = 0; y < MaxY; ++y) {
		for (int x = 0; x < MaxX; ++x) {
			if (map[x][y] >= min && map[x][y] < max) {
				// ワールド座標に変換
				KamataEngine::Vector3 worldPos;
				worldPos.x = x * Size.x; // サイズを考慮
				worldPos.y = 0.0f;
				worldPos.z = y * Size.z;

				positions.push_back(worldPos);
			}
		}
	}

	return positions;
}

std::vector<Light::GrowType> Map::GetMirrorTypesInRange() {
	std::vector<Light::GrowType> types;
	// マップを走査
	for (int y = 0; y < MaxY; ++y) {
		for (int x = 0; x < MaxX; ++x) {
			if (map[x][y] == 41) {
				Light::GrowType type;
				type = Light::Up;
				types.push_back(type);
			} else if (map[x][y] == 42) {
				Light::GrowType type;
				type = Light::Down;
				types.push_back(type);
			} else if (map[x][y] == 43) {
				Light::GrowType type;
				type = Light::Left;
				types.push_back(type);
			} else if (map[x][y] == 44) {
				Light::GrowType type;
				type = Light::Right;
				types.push_back(type);
			}
		}
	}
	return types;
}
