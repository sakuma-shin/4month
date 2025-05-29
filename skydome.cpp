#include "skydome.h"
using namespace KamataEngine;
skydome::~skydome() {
	for (int i = 0; i < 5; i++) {
		delete Reticle_[i];
		delete Reticle2_[i];
	}
}

void skydome::Initialize(Camera* camera) {

	worldtransform_.translation_ = {0.0f, 0.0f, 0.0f};
	worldtransform_.scale_ = {-100, 100, 100};
	model_ = Model::CreateFromOBJ("tenn", true);
	textureReticle = TextureManager::Load("backgraund.png");
	Reticle_[0] = Sprite::Create(textureReticle, Vector2(0.0f, 0.0f), Vector4(1, 1, 1, 1), Vector2(0.0f, 0.0f));
	Reticle_[2] = Sprite::Create(textureReticle, Vector2(0.0f, 288.0f), Vector4(1, 1, 1, 1), Vector2(0.0f, 0.0f));
	Reticle_[4] = Sprite::Create(textureReticle, Vector2(0.0f, 576.0f), Vector4(1, 1, 1, 1), Vector2(0.0f, 0.0f));
	Reticle2_[0] = Sprite::Create(textureReticle, Vector2(-2560.0f, 0.0f), Vector4(1, 1, 1, 1), Vector2(0.0f, 0.0f));
	Reticle2_[2] = Sprite::Create(textureReticle, Vector2(-2560.0f, 288.0f), Vector4(1, 1, 1, 1), Vector2(0.0f, 0.0f));
	Reticle2_[4] = Sprite::Create(textureReticle, Vector2(-2560.0f, 576.0f), Vector4(1, 1, 1, 1), Vector2(0.0f, 0.0f));
	textureReticle = TextureManager::Load("backgraund2.png");
	Reticle_[1] = Sprite::Create(textureReticle, Vector2(0.0f, 144.0f), Vector4(1, 1, 1, 1), Vector2(0.0f, 0.0f));
	Reticle_[3] = Sprite::Create(textureReticle, Vector2(0.0f, 432.0f), Vector4(1, 1, 1, 1), Vector2(0.0f, 0.0f));
	Reticle2_[1] = Sprite::Create(textureReticle, Vector2(-2560.0f, 144.0f), Vector4(1, 1, 1, 1), Vector2(0.0f, 0.0f));
	Reticle2_[3] = Sprite::Create(textureReticle, Vector2(-2560.0f, 432.0f), Vector4(1, 1, 1, 1), Vector2(0.0f, 0.0f));
	camera_ = camera;

	worldtransform_.Initialize();

	worldtransform_.UpdateMatrix();
}

void skydome::Update() {
	//std::string windowName = "skydome" + std::to_string(reinterpret_cast<uintptr_t>(this));
	/*ImGui::Begin(windowName.c_str());

	ImGui::DragFloat3("light.translation", &worldtransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("light.rotate", &worldtransform_.rotation_.x, 0.01f);
	ImGui::DragFloat3("light.scale", &worldtransform_.scale_.x, 0.01f);*/
	worldtransform_.UpdateMatrix();
	velo = 1.5f;
	Reticle_[1]->SetPosition(Vector2(Reticle_[1]->GetPosition().x + velo, Reticle_[1]->GetPosition().y));
	Reticle2_[1]->SetPosition(Vector2(Reticle2_[1]->GetPosition().x + velo, Reticle2_[1]->GetPosition().y));
	Reticle_[3]->SetPosition(Vector2(Reticle_[3]->GetPosition().x + velo, Reticle_[3]->GetPosition().y));
	Reticle2_[3]->SetPosition(Vector2(Reticle2_[3]->GetPosition().x + velo, Reticle2_[3]->GetPosition().y));

	if (Reticle_[1]->GetPosition().x >= 2560.f) {
		Reticle_[1]->SetPosition(Vector2(0.0f, 144.0f));
		Reticle2_[1]->SetPosition(Vector2(-2560.0f, 144.0f));
		Reticle_[3]->SetPosition(Vector2(0.0f, 432.0f));
		Reticle2_[3]->SetPosition(Vector2(-2560.0f, 432.0f));
	}
}

void skydome::Draw() {
	for (int i = 0; i < 5; i++) {
		Reticle_[i]->Draw();
		Reticle2_[i]->Draw();
	}
	// model_->Draw(worldtransform_, *camera_);
}
