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

	if (map_->CheckCollision(Vector3(worldTransform_->translation_.x, worldTransform_->translation_.y, worldTransform_->translation_.z + 2.0f)) == 0 ||
	    map_->CheckCollision(Vector3(worldTransform_->translation_.x - 2.0f, worldTransform_->translation_.y, worldTransform_->translation_.z)) == 0 ||
	    map_->CheckCollision(Vector3(worldTransform_->translation_.x, worldTransform_->translation_.y, worldTransform_->translation_.z - 2.0f)) == 0 ||
	    map_->CheckCollision(Vector3(worldTransform_->translation_.x + 2.0f, worldTransform_->translation_.y, worldTransform_->translation_.z)) == 0) {
		if (input_->TriggerKey(DIK_K)) {
			if (isSet_) {
				Broken();
			}
		}
	}

	int count = player_->GetCount();

	std::string windowName = "Prism_" + std::to_string(reinterpret_cast<uintptr_t>(this));
	ImGui::Begin(windowName.c_str());
	ImGui::InputInt("key", &key_);
	ImGui::InputInt("count", &count);
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