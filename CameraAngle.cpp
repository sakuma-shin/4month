#include "CameraAngle.h"
#include <ImGui.h>
#include "MathUtility.h"
#include "Player.h"

using namespace KamataEngine;

void CameraAngle::Initialize(const WorldTransform& worldTransform, Player* player)
{

	//ワールドトランスフォームの初期設定
	worldTransform_.matWorld_ = worldTransform.matWorld_;
	worldTransform_.rotation_ = worldTransform.rotation_;
	worldTransform_.translation_ = worldTransform.translation_;
	worldTransform_.scale_ = worldTransform.scale_;
    player_ = player;

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

void CameraAngle::Update() {
    
    //カメラの移動速度
    const float kCameraSpeed = 0.02f;
    
    //カメラとターゲットの距離
    const float kCameraDistance = 50.0f;

    if (input_->PushKey(DIK_LEFT)) {
        rotation_.y -= kCameraSpeed; //左
    }
    if (input_->PushKey(DIK_RIGHT)) {
        rotation_.y += kCameraSpeed;  //右
    }
    if (input_->PushKey(DIK_UP)) {
        rotation_.x -= kCameraSpeed;  //上
    }
    if (input_->PushKey(DIK_DOWN)) {
        rotation_.x += kCameraSpeed;  //下
    }

    //カメラの向きをプレイヤーに向ける
    //cameraTarget_ = player_->GetPosition();

    //特定の座標をターゲットとして設定
    KamataEngine::Vector3 targetPosition = { 0.0f, 0.0f, 0.0f };

    //カメラの位置を更新
    translation_.x = targetPosition.x + kCameraDistance * sinf(rotation_.y);
    translation_.y = targetPosition.y + kCameraDistance * sinf(rotation_.x);
    translation_.z = targetPosition.z + kCameraDistance * cosf(rotation_.y);

    //カメラの向きをターゲットに向ける
    camera_.matView = MakeLookAtMatrix(translation_, targetPosition, cameraUp_);

    //変換行列を更新
    worldTransform_.translation_ = translation_;
    worldTransform_.rotation_ = rotation_;
    worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

    //カメラの行列を更新
    camera_.matView = MakeLookAtMatrix(translation_, targetPosition, cameraUp_);
    worldTransform_.UpdateMatrix();

    ImGui::Begin("Camera");
    ImGui::DragFloat3("Translation", &translation_.x, 0.01f);
    ImGui::DragFloat3("Rotation", &rotation_.x, 0.01f);
    ImGui::End();
}


//void CameraAngle::Update() {
//    // カメラの移動速度
//    const float kCameraSpeed = 0.02f;
//    const float kCameraDistance = 70.0f;  //カメラとターゲットの距離
//
//    // 左右矢印キーで回転
//    if (input_->PushKey(DIK_LEFT)) {
//        rotation_.y -= kCameraSpeed;  //左
//    }
//    if (input_->PushKey(DIK_RIGHT)) {
//        rotation_.y += kCameraSpeed;  //右
//    }
//    if (input_->PushKey(DIK_UP)) {
//        rotation_.x -= kCameraSpeed;  //上
//    }
//    if (input_->PushKey(DIK_DOWN)) {
//        rotation_.x += kCameraSpeed;  //下
//    }
//
//    //カメラの位置更新
//    translation_.x = cameraTarget_.x + kCameraDistance * sinf(rotation_.y);
//    translation_.y = cameraTarget_.y + kCameraDistance * sinf(rotation_.x);
//    translation_.z = cameraTarget_.z + kCameraDistance * cosf(rotation_.y);
//
//    //カメラの向きをプレイヤーに向ける
//    cameraTarget_ = player_->GetPosition();
//
//    //変換行列を更新
//    worldTransform_.translation_ = translation_;
//    worldTransform_.rotation_ = rotation_;
//    worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
//
//    //カメラビュー行列を更新
//    camera_.matView = MakeLookAtMatrix(translation_, cameraTarget_, cameraUp_);
//    worldTransform_.UpdateMatrix();
//
//    ImGui::Begin("Camera");
//    ImGui::DragFloat3("Translation", &translation_.x, 0.01f);
//    ImGui::DragFloat3("Rotation", &rotation_.x, 0.01f);
//    ImGui::End();
//}


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

