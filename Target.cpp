#include "Target.h"

using namespace KamataEngine;

Target::~Target() {}

void Target::Initialize(int number, KamataEngine::WorldTransform* worldTransform) {
	targetmodel_->Create();
	targetmodel_ = Model::CreateFromOBJ("sensor", true);
	coad = number % 10;
	color = (number % 100) / 10;
	worldTransform_ = worldTransform;
	Hit = false;
	number_ = number;
}

void Target::Update() {
	/*std::string windowName = "Target" + std::to_string(reinterpret_cast<uintptr_t>(this));
	ImGui::Begin(windowName.c_str());
	ImGui::Checkbox("hit", &Hit);
	ImGui::End();*/
}

void Target::Draw(KamataEngine::Camera* camera) { targetmodel_->Draw(*worldTransform_, *camera); }
