#include "ColorGlass.h"

using namespace KamataEngine;

ColorGlass::~ColorGlass() {
	delete worldTransform_;
	delete player_;
}

void ColorGlass::Initialize(KamataEngine::WorldTransform* worldtransform, Map* map, int x, int z, int number) {

	worldTransform_ = worldtransform;
	map_ = map;
	colorGlassModel_ = Model::CreateFromOBJ("cube", true);
	textureHandle_ = TextureManager::Load("color/purple.png");
	pos[0] = x;
	pos[1] = z;
	mapnumber_ = number;
}

void ColorGlass::Update() {}

void ColorGlass::Draw(KamataEngine::Camera* camera) { colorGlassModel_->Draw(*worldTransform_, *camera, textureHandle_); }

KamataEngine::Vector3 ColorGlass::GetPosition() const { return worldTransform_->translation_; }

int ColorGlass::Getnumber() { return mapnumber_; }
