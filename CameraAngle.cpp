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
	worldTransform_.scale_ = worldTransform.scale_;

	//インスタンス
	input_ = Input::GetInstance();

	worldTransform_.Initialize();
	camera_.Initialize();

    translation_ = { 0.0f, 30.0f, -30.0f };  //初期位置
    rotation_ = { 0.5f, 0.0f, 0.0f };        //初期回転

    //カメラの初期ターゲット位置
    cameraTarget_ = { 0.0f, 0.0f, 0.0f };    //ターゲットの位置
    cameraUp_ = { 0.0f, 1.0f, 0.0f };

}

void CameraAngle::Update()
{

    //移動ベクトル
    //Vector3 move = { 0, 0, 0 };

    //カメラの移動速度
    const float kCameraSpeed = 0.02f;
    const float kCameraDistance = 30.0f;

    //キー入力で移動量を加算
    if (input_->PushKey(DIK_LEFT)) {
        rotation_.y -= kCameraSpeed; // 左回転
    }
    if (input_->PushKey(DIK_RIGHT)) {
        rotation_.y += kCameraSpeed; // 右回転
    }

    cameraPosition_.x = cameraTarget_.x + kCameraDistance * sinf(rotation_.y);
    cameraPosition_.y = cameraTarget_.y + 30.0f;
    cameraPosition_.z = cameraTarget_.z + kCameraDistance * cosf(rotation_.y);

    UpdateViewMatrix();

    //角度を更新
    //rotation_.y += move.y;

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

void CameraAngle::SetEye(const KamataEngine::Vector3& eye)
{

    cameraPosition_ = eye;

}

void CameraAngle::SetTarget(const KamataEngine::Vector3& target)
{

    cameraTarget_ = target;

}

void CameraAngle::SetUp(const KamataEngine::Vector3& up)
{

    cameraUp_ = up;

}

void CameraAngle::UpdateViewMatrix()
{

    camera_.matView = MakeLookAtMatrix(cameraPosition_, cameraTarget_, cameraUp_);

}

