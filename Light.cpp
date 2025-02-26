#include "Light.h"
#include "GameScene.h"
#include <cassert>

using namespace KamataEngine;

void Light::Initialize(uint32_t textureHandle, Vector3 initialPos, Vector2 velocity) {
	worldTransform_.Initialize(); // ワールド変換の初期化

	sprite_ = Sprite::Create(textureHandle, {}); // 各LightごとにSpriteを作成

	// World Transform に初期位置を設定
	worldTransform_.translation_ = initialPos;
	worldTransform_.scale_ = {width_, height_, 1.0f};

	velocity_ = velocity;
	width_ = 20.0f;
	height_ = 20.0f;
	isReflection_ = false;
}

void Light::Update() {
	// ワールド座標で位置を更新
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;

	// 反射の処理 (例: X 座標が境界を越えた場合、反転)
	if (worldTransform_.translation_.x >= 20.0f || worldTransform_.translation_.x <= -20.0f) {
		velocity_.x = -velocity_.x;
	}

	if (worldTransform_.translation_.y >= 20.0f || worldTransform_.translation_.y <= -20.0f) {
		velocity_.y = -velocity_.y;
	}

	// ImGui デバッグ
	ImGui::Begin("Light");
	ImGui::DragFloat3("Light.pos", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat("Light.width", &worldTransform_.scale_.x, 0.01f);
	ImGui::DragFloat("Light.height", &worldTransform_.scale_.y, 0.01f);
	ImGui::End();

	// ワールド行列を更新
	worldTransform_.UpdateMatrix();
}

void Light::Draw() {
	// スクリーン座標に変換
	Vector3 screenPos = GetWorldPositionFromScreen(sprite_->GetPosition().x, sprite_->GetPosition().y);

	// スプライトの位置にワールド座標を設定
	sprite_->SetPosition({screenPos.x, screenPos.y});
	sprite_->SetSize({worldTransform_.scale_.x, worldTransform_.scale_.y});

	sprite_->Draw();
}

Light::~Light() { delete sprite_; }

Vector3 Light::GetWorldPositionFromScreen(float screenPosX, float screenPosY) {   
	// スクリーン座標（screenPosX, screenPosY）をワールド座標に変換
	float worldPosX = screenPosX * (40.0f / 1280.0f) - 20.0f;
	float worldPosY = screenPosY * (40.0f / 720.0f) - 20.0f;

	// ワールド座標を返す
	return {worldPosX, worldPosY, 0.0f}; // Z座標は0で保持（2Dの場合） 
}
