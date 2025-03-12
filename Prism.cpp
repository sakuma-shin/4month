#include "Prism.h"

void Prism::Initialize(int key, WorldTransform* worldTransform) {
	key_ = key;
	worldTransform_ = worldTransform;

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

void Prism::Update() {
	ImGui::Begin("prism");
	ImGui::InputInt("key", &key_);
	if (ImGui::Button("broken", {50, 50})) {
		Broken();
	}
	if (ImGui::Button("Set", {50, 50})) {
		Set();
	}
	ImGui::End();
}

void Prism::Draw( Camera* camera) {
	if (isSet_) {
		model_->Draw(*worldTransform_, *camera);
	}
}

int Prism::CheckLight2Direction() { return 1; }

void Prism::ReflectLight() {}

void Prism::DecompositionLight() {}

void Prism::Broken() { isSet_ = false; }

void Prism::Set() { isSet_ = true; }
