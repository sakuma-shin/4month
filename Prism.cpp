#include "Prism.h"

void Prism::Initialize(int key, WorldTransform* worldTransform, int x, int z, Map* map) {
	key_ = key;
	worldTransform_ = worldTransform;

	pos_[0] = x;
	pos_[1] = z;

	map_ = map;

	input_ = Input::GetInstance();

	// keyに応じて対応したモデルを読み、自身の向きを決定する
	if (key_ == 91) {
		model_ = Model::CreateFromOBJ("prism", true);
		prismDirection_ = Light::GrowType::Up;
	} else if (key_ == 92) {
		model_ = Model::CreateFromOBJ("prism", true);
		prismDirection_ = Light::GrowType::Down;
	} else if (key_ == 93) {
		model_ = Model::CreateFromOBJ("prism", true);
		prismDirection_ = Light::GrowType::Left;
	} else if (key_ == 94) {
		model_ = Model::CreateFromOBJ("prism", true);
		prismDirection_ = Light::GrowType::Right;
	} else { // 仮に数字が該当しなかったら向きは右とする
		model_ = Model::CreateFromOBJ("prism", true);
		prismDirection_ = Light::GrowType::NO;
	}
}

void Prism::Update(Player* player) {
	player_ = player;

	if (map_->CheckCollision(Vector3(player_->GetPosition().x, player_->GetPosition().y, player_->GetPosition().z + 2.0f)) == key_ ||
	    map_->CheckCollision(Vector3(player_->GetPosition().x - 2.0f, player_->GetPosition().y, player_->GetPosition().z)) == key_ ||
	    map_->CheckCollision(Vector3(player_->GetPosition().x, player_->GetPosition().y, player_->GetPosition().z - 2.0f)) == key_ ||
	    map_->CheckCollision(Vector3(player_->GetPosition().x + 2.0f, player_->GetPosition().y, player_->GetPosition().z)) == key_) {
		if (input_->TriggerKey(DIK_K)) {
			if (isSet_) {
				Broken();
			}
		}
	}

	if (input_->TriggerKey(DIK_W)) {
		prismDirection_ = Light::GrowType::Up;
	} else if (input_->TriggerKey(DIK_S)) {
		prismDirection_ = Light::GrowType::Down;
	} else if (input_->TriggerKey(DIK_A)) {
		prismDirection_ = Light::GrowType::Left;
	} else if (input_->TriggerKey(DIK_D)) {
		prismDirection_ = Light::GrowType::Right;
	}

	if (!isSet_) {
		if (input_->TriggerKey(DIK_L)) {
			if (prismDirection_ == Light::GrowType::Up) {
				if (map_->CheckCollision(Vector3(player_->GetPosition().x, player_->GetPosition().y, player_->GetPosition().z + 2.0f)) == 0) {
					key_ = 91;
					model_ = Model::CreateFromOBJ("prism", true); // 対応するモデルを読み込み直す
					worldTransform_->translation_ =Vector3 {float((int)player->GetPosition().x) / 2 * 2, 0, (float)((int)player->GetPosition().z+2) / 2 * 2};
					pos_[0] = ((int)player->GetPosition().x) / 2;
					pos_[1] = ((int)player->GetPosition().z + 2) / 2;
					Set();
				}
			} else if (prismDirection_ == Light::GrowType::Down) {
				if (map_->CheckCollision(Vector3(player_->GetPosition().x, player_->GetPosition().y, player_->GetPosition().z - 2.0f)) == 0) {
					key_ = 92;
					model_ = Model::CreateFromOBJ("prism", true);
					worldTransform_->translation_ = Vector3{float((int)player->GetPosition().x) / 2 * 2, 0, (float)((int)player->GetPosition().z - 2) / 2 * 2};
					pos_[0] = ((int)player->GetPosition().x) / 2;
					pos_[1] = ((int)player->GetPosition().z - 2) / 2;
					Set();
				}
			} else if (prismDirection_ == Light::GrowType::Left) {
				if (map_->CheckCollision(Vector3(player_->GetPosition().x - 2.0f, player_->GetPosition().y, player_->GetPosition().z)) == 0) {
					key_ = 93;
					model_ = Model::CreateFromOBJ("prism", true);
					worldTransform_->translation_ = Vector3{float((int)player->GetPosition().x-2) / 2 * 2, 0, (float)((int)player->GetPosition().z) / 2 * 2};
					pos_[0] = ((int)player->GetPosition().x-2) / 2;
					pos_[1] = ((int)player->GetPosition().z) / 2;
					Set();
				}
			} else if (prismDirection_ == Light::GrowType::Right) {
				if (map_->CheckCollision(Vector3(player_->GetPosition().x + 2.0f, player_->GetPosition().y, player_->GetPosition().z)) == 0) {
					key_ = 94;
					model_ = Model::CreateFromOBJ("prism", true);
					worldTransform_->translation_ = Vector3{float((int)player->GetPosition().x+2) / 2 * 2, 0, (float)((int)player->GetPosition().z) / 2 * 2};
					pos_[0] = ((int)player->GetPosition().x+2) / 2;
					pos_[1] = ((int)player->GetPosition().z ) / 2;
					Set();
				}
			}
		}
	}
	worldTransform_->TransferMatrix();
	worldTransform_->UpdateMatrix();

	int count = player_->GetCount();

	std::string windowName = "Prism_" + std::to_string(reinterpret_cast<uintptr_t>(this));
	ImGui::Begin(windowName.c_str());
	ImGui::InputInt("key", &key_);
	ImGui::InputInt("count", &count);
	ImGui::DragFloat3("worldtransform", &worldTransform_->translation_.x);
	if (ImGui::Button("broken", {50, 50})) {
		Broken();
	}
	if (ImGui::Button("Set", {50, 50})) {
		Set();
	}
	ImGui::End();
}

void Prism::Draw(Camera* camera) {
	if (isSet_) {
		model_->Draw(*worldTransform_, *camera);
	}
}

void Prism::DecompositionLight() {}

void Prism::Broken() {
	isSet_ = false;
	player_->SetCount(1);
}

void Prism::Set() {
	isSet_ = true;
	player_->SetCount(0);
}