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

}

//void CameraAngle::Update()
//{
//
//	//座標の数値を加算
//	worldTransform_.translation_.x = translation_.x;
//	worldTransform_.translation_.y = translation_.y;
//	worldTransform_.translation_.z = translation_.z;
//
//	//角度の数値を加算
//	worldTransform_.rotation_.x = rotation_.x;
//	worldTransform_.rotation_.y = rotation_.y;
//	worldTransform_.rotation_.z = rotation_.z;
//
//	//キャラクターの移動ベクトル
//	Vector3 move = { 0,0,0 };
//
//	//キャラクターの移動速度
//	const float kCameraSpeed = 0.2f;
//
//	if (input_->PushKey(DIK_LEFT)) {
//
//		move.y -= kCameraSpeed;
//
//	}
//
//	if (input_->PushKey(DIK_RIGHT)) {
//
//		move.y += kCameraSpeed;
//
//	}
//
//	worldTransform_.rotation_.y += move.y;
//
//	worldTransform_.TransferMatrix();
//	worldTransform_.UpdateMatrix();
//	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
//	camera_.matView = MathUtility::Inverse(worldTransform_.matWorld_);
//
//	ImGui::Begin("Camera");
//	ImGui::DragFloat3("Translation", &translation_.x, 0.01f);
//	ImGui::DragFloat3("Rotation", &rotation_.x, 0.01f);
//	ImGui::End();
//
//
//}

void CameraAngle::Update()
{
    if (input_ == nullptr) {
        DebugText::GetInstance()->ConsolePrintf("input_ is nullptr\n");
        return;
    }

    // キャラクターの移動ベクトル
    Vector3 move = { 0, 0, 0 };

    // カメラの移動速度
    const float kCameraSpeed = 0.02f;

    // キー入力で移動量を加算
    if (input_->PushKey(DIK_LEFT)) {
      //  DebugText::GetInstance()->ConsolePrintf("LEFT key pressed\n");
        move.y -= kCameraSpeed;
    }

    if (input_->PushKey(DIK_RIGHT)) {
       // DebugText::GetInstance()->ConsolePrintf("RIGHT key pressed\n");
        move.y += kCameraSpeed;
    }

    // 角度を更新（移動量を rotation_ に加算）
    rotation_.y += move.y;
   // DebugText::GetInstance()->ConsolePrintf("Rotation Y: %f\n", rotation_.y);

    // 変換行列を更新
    worldTransform_.translation_ = translation_;
    worldTransform_.rotation_ = rotation_;
    worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
    camera_.matView = MathUtility::Inverse(worldTransform_.matWorld_);

    // ワールド行列を更新
    worldTransform_.UpdateMatrix();

    // ImGui でデバッグ表示
    ImGui::Begin("Camera");
    ImGui::DragFloat3("Translation", &translation_.x, 0.01f);
    ImGui::DragFloat3("Rotation", &rotation_.x, 0.01f);
    ImGui::End();
}

