#include "ColorGlass.h"

using namespace KamataEngine;

void ColorGlass::Initialize(KamataEngine::WorldTransform* worldtransform, Map* map)
{

	worldTransform_ = worldtransform;
	map_ = map;
	colorGlassModel_ = Model::CreateFromOBJ("cube", true);
	textureHandle_ = TextureManager::Load("color/purple.png");

}

void ColorGlass::Update()
{
}

void ColorGlass::Draw(KamataEngine::Camera* camera)
{

	colorGlassModel_->Draw(*worldTransform_, *camera, textureHandle_);

}

KamataEngine::Vector3 ColorGlass::GetPosition() const
{
	return worldTransform_->translation_;
}
