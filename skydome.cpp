#include "skydome.h"

void skydome::Initialize( Camera* camera) { 
	worldtransform_->Initialize();
	worldtransform_->translation_ = {0.0f, 0.0f, 0.0f};
	worldtransform_->scale_ = {100, 100, 100};
	model_ = Model::CreateFromOBJ("Resources/tenn", true);

	camera_ = camera;
}

void skydome::Update() {}

void skydome::Draw() { 
	model_->Draw(*worldtransform_,*camera_,nullptr);
}
