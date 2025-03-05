#include "door.h"

using namespace KamataEngine;

void door::Initialize() { 
	doormodel_ = Model::CreateFromOBJ("door", true); 
}

void door::Update() {
	ImGui::Begin("door");
	ImGui::Checkbox("opendoor", &openflag);
	ImGui::End();
}

void door::Draw(KamataEngine::WorldTransform* worldtransform, KamataEngine::Camera* camera) {
	if (!openflag) {
		doormodel_->Draw(*worldtransform, *camera);
	}
}
	
