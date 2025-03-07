#include "door.h"

using namespace KamataEngine;

void door::Initialize(int key) { 
	doormodel_ = Model::CreateFromOBJ("door", true); 
	key_ = key;
}

void door::Update() {
	std::string windowName = "door_" + std::to_string(reinterpret_cast<uintptr_t>(this));
	ImGui::Begin(windowName.c_str());
	ImGui::Checkbox("opendoor", &openflag);
	ImGui::End();
}

void door::Draw(KamataEngine::WorldTransform* worldtransform, KamataEngine::Camera* camera) {
	if (!openflag) {
		doormodel_->Draw(*worldtransform, *camera);
	}
}
	
