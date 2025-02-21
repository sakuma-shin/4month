#include "CameraAngle.h"
#include <ImGui.h>
#include "MathUtility.h"

using namespace KamataEngine;

void CameraAngle::Initialize(const WorldTransform& worldTransform)
{

	//ワールドトランスフォームの初期設定
	worldTransform_.matWorld_ = worldTransform.matWorld_;
	worldTransform_.rotation_ = worldTransform.rotation_;
	worldTransform_.translation_ = worldTransform.translation_;

	camera_.Initialize();

}

void CameraAngle::Update()
{

	//座標の数値を加算
	worldTransform_.translation_.x = translation_.x;
	worldTransform_.translation_.y = translation_.y;
	worldTransform_.translation_.z = translation_.z;

	//角度の数値を加算
	worldTransform_.rotation_.x = rotation_.x;
	worldTransform_.rotation_.y = rotation_.y;
	worldTransform_.rotation_.z = rotation_.z;

	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	camera_.matView = MathUtility::Inverse(worldTransform_.matWorld_);

	ImGui::Begin("Camera");
	ImGui::DragFloat3("Translation", &translation_.x, 0.01f);
	ImGui::DragFloat3("Rotation", &rotation_.x, 0.01f);
	ImGui::End();


}
