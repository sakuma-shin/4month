#include "CameraAngle.h"
#include <ImGui.h>
#include "MathUtility.h"
#include <algorithm>

using namespace KamataEngine;

CameraAngle::~CameraAngle()
{
}

void CameraAngle::Initialize(const WorldTransform& worldTransform)
{

	//ワールドトランスフォームの初期設定
	worldTransform_.matWorld_ = worldTransform.matWorld_;
	worldTransform_.rotation_ = worldTransform.rotation_;
	worldTransform_.translation_ = worldTransform.translation_;
	worldTransform_.scale_ = worldTransform.scale_;

	//インスタンス
	input_ = Input::GetInstance();

	worldTransform_.Initialize();
	camera_.Initialize();

    translation_ = { 0.0f, 50.0f, -30.0f };
    rotation_ = { 0.7f, 0.0f, 0.0f };

    //カメラの初期ターゲット位置を設定
    cameraTarget_ = { 0.0f, 0.0f, 0.0f };
    cameraUp_ = { 0.0f, 1.0f, 0.0f };

}

void CameraAngle::Update()
{

    //キャラクターの移動ベクトル
    Vector3 move = { 0, 0, 0 };

    //カメラの移動速度
    const float kCameraSpeed = 0.01f;

    if (input_->PushKey(DIK_UP)) {

        move.x += kCameraSpeed;

    }

    if (input_->PushKey(DIK_DOWN)) {

        move.x -= kCameraSpeed;

    }

    //角度を更新
    rotation_.x += move.x;
    rotation_.y += move.y;

    //回転角度を制限
    rotation_.x = std::clamp(rotation_.x, 0.7f, 1.0f);

    //カメラの向きに合わせたターゲット計算
    Vector3 direction{
     std::sin(rotation_.y),
     std::sin(rotation_.x),
     std::cos(rotation_.y)
    };

    cameraTarget_ = translation_ + direction;

    //変換行列を更新
    worldTransform_.translation_ = translation_;
    worldTransform_.rotation_ = rotation_;
    worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

    //カメラビュー行列を更新
    camera_.matView = MathUtility::Inverse(worldTransform_.matWorld_);

    //ワールド行列を更新
    worldTransform_.UpdateMatrix();

    ImGui::Begin("Camera");
    ImGui::DragFloat3("Translation", &translation_.x, 0.01f);
    ImGui::DragFloat3("Rotation", &rotation_.x, 0.01f);
    ImGui::End();
}

