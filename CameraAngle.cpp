#include "CameraAngle.h"
#include "MathUtility.h"
#include "Player.h"
#include <ImGui.h>
#include <algorithm>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

#define XM_PIDIV4  (M_PI / 2.0f)
#define XM_3PIDIV4 (3.0f * M_PI / 4.0f)

using namespace KamataEngine;

CameraAngle::~CameraAngle() {}

void CameraAngle::Initialize(const WorldTransform& worldTransform, Player* player) {

	// ワールドトランスフォームの初期設定
	worldTransform_.matWorld_ = worldTransform.matWorld_;
	worldTransform_.rotation_ = worldTransform.rotation_;
	worldTransform_.translation_ = worldTransform.translation_;
	worldTransform_.scale_ = worldTransform.scale_;
	player_ = player;

	// インスタンス
	input_ = Input::GetInstance();

	worldTransform_.Initialize();
	camera_.Initialize();

	translation_ = {0.0f, 30.0f, -30.0f}; // 初期位置
	rotation_ = {-1.5f, 0.0f, 0.0f};      // 初期回転

	// カメラの初期ターゲット位置
	cameraTarget_ = {0.0f, 0.0f, 0.0f}; // ターゲットの位置
	cameraUp_ = {0.0f, 1.0f, 0.0f};
}

void CameraAngle::Update() {

	// カメラの移動速度
	const float kCameraSpeed = 0.02f;
	const float kCameraDistance = 40.0f; // カメラとターゲットの距離

	// 左右矢印キーで回転
	if (input_->PushKey(DIK_LEFT)) {
		rotation_.y -= kCameraSpeed; // 左
	}
	if (input_->PushKey(DIK_RIGHT)) {
		rotation_.y += kCameraSpeed; // 右
	}

	// 上下矢印キーで回転（プレイヤーと同じ目線から真上まで制限）
	if (input_->PushKey(DIK_UP)) {
		rotation_.x -= kCameraSpeed; // 上
		if (rotation_.x < -XM_PIDIV4)
			rotation_.x = -XM_PIDIV4; // 上限を真上（-90度）に制限
	}
	if (input_->PushKey(DIK_DOWN)) {
		rotation_.x += kCameraSpeed; // 下
		if (rotation_.x > 0)
			rotation_.x = 0; // 下限をプレイヤーと同じ目線（0度）に制限
	}

	// カメラの位置更新（修正後）
	translation_.x = cameraTarget_.x + kCameraDistance * sinf(rotation_.y);
	translation_.y = cameraTarget_.y + kCameraDistance * sinf(rotation_.x);
	translation_.z = cameraTarget_.z - kCameraDistance * cosf(rotation_.y);

	// カメラの向きをプレイヤーに向ける
	cameraTarget_ = player_->GetPosition();

	// 変換行列を更新
	worldTransform_.translation_ = translation_;
	worldTransform_.rotation_ = rotation_;
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// カメラビュー行列を更新
	camera_.matView = MakeLookAtMatrix(translation_, cameraTarget_, cameraUp_);
	worldTransform_.UpdateMatrix();

	ImGui::Begin("Camera");
	ImGui::DragFloat3("Translation", &translation_.x, 0.01f);
	ImGui::DragFloat3("Rotation", &rotation_.x, 0.01f);
	ImGui::End();
}

// void CameraAngle::Update() {
//     // カメラの移動速度
//     const float kCameraSpeed = 0.02f;
//     const float kCameraDistance = 40.0f;  //カメラとターゲットの距離
//
//     // 左右矢印キーで回転
//     if (input_->PushKey(DIK_LEFT)) {
//         rotation_.y -= kCameraSpeed;  //左
//     }
//     if (input_->PushKey(DIK_RIGHT)) {
//         rotation_.y += kCameraSpeed;  //右
//     }
//     if (input_->PushKey(DIK_UP)) {
//         rotation_.x -= kCameraSpeed;  //上
//         if (rotation_.x < -1.5) rotation_.x = -1.5;  // 上限を-45度に制限
//     }
//     if (input_->PushKey(DIK_DOWN)) {
//         rotation_.x += kCameraSpeed;  //下
//         if (rotation_.x > 0) rotation_.x = 0;
//     }
//
//     // カメラの位置更新（修正後）
//     translation_.x = cameraTarget_.x + kCameraDistance * sinf(rotation_.y);
//     translation_.y = cameraTarget_.y + kCameraDistance * sinf(rotation_.x);
//     translation_.z = cameraTarget_.z - kCameraDistance * cosf(rotation_.y);
//
//     //カメラの向きをプレイヤーに向ける
//     cameraTarget_ = player_->GetPosition();
//
//     //変換行列を更新
//     worldTransform_.translation_ = translation_;
//     worldTransform_.rotation_ = rotation_;
//     worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
//
//     //カメラビュー行列を更新
//     camera_.matView = MakeLookAtMatrix(translation_, cameraTarget_, cameraUp_);
//     worldTransform_.UpdateMatrix();
//
//     ImGui::Begin("Camera");
//     ImGui::DragFloat3("Translation", &translation_.x, 0.01f);
//     ImGui::DragFloat3("Rotation", &rotation_.x, 0.01f);
//     ImGui::End();
// }

void CameraAngle::SetEye(const KamataEngine::Vector3& eye) { cameraPosition_ = eye; }

void CameraAngle::SetTarget(const KamataEngine::Vector3& target) { cameraTarget_ = target; }

void CameraAngle::SetUp(const KamataEngine::Vector3& up) { cameraUp_ = up; }

void CameraAngle::UpdateViewMatrix() { camera_.matView = MakeLookAtMatrix(cameraPosition_, cameraTarget_, cameraUp_); }
