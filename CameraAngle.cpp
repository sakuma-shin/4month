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

    translation_ = { 0.0f, 30.0f, -30.0f };  // 初期位置
    rotation_ = { 0.5f, 0.0f, 0.0f };        // 初期回転

    // カメラの初期ターゲット位置を設定（カメラが注視するポイント）
    cameraTarget_ = { 0.0f, 0.0f, 0.0f };    // ターゲットの位置（例：原点）
    cameraUp_ = { 0.0f, 1.0f, 0.0f };

}

void CameraAngle::Update()
{
    // カメラの移動速度
    const float kCameraSpeed = 0.02f;

    // キー入力で移動量を加算
    if (input_->PushKey(DIK_LEFT)) {
        rotation_.y -= kCameraSpeed; // 左回転
    }
    if (input_->PushKey(DIK_RIGHT)) {
        rotation_.y += kCameraSpeed; // 右回転
    }

    // 半径（カメラと注視点の距離）
    float radius = 30.0f;

    // rotation_.y を使ってカメラ位置を極座標で計算
    translation_.x = cameraTarget_.x + radius * cos(rotation_.y);
    translation_.z = cameraTarget_.z + radius * sin(rotation_.y);
    translation_.y = cameraTarget_.y + 30.0f; // 高さを固定

    // ワールド座標を更新
    worldTransform_.translation_ = translation_;
    worldTransform_.rotation_ = rotation_;
    worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

    // カメラビュー行列を更新（LookAtを使用）
    camera_.matView = MakeLookAt(translation_, cameraTarget_, cameraUp_);

    // ワールド行列を更新
    worldTransform_.UpdateMatrix();

    // ImGui でデバッグ表示
    ImGui::Begin("Camera");
    ImGui::DragFloat3("Translation", &translation_.x, 0.01f);  // カメラ位置を確認
    ImGui::DragFloat3("Rotation", &rotation_.x, 0.01f);        // カメラ回転を確認
    ImGui::End();
}


//void CameraAngle::Update()
//{
//
//    // キャラクターの移動ベクトル
//    Vector3 move = { 0, 0, 0 };
//
//    // カメラの移動速度
//    const float kCameraSpeed = 0.02f;
//
//    // キー入力で移動量を加算
//    if (input_->PushKey(DIK_LEFT)) {
//        move.y -= kCameraSpeed; // 左回転
//    }
//    if (input_->PushKey(DIK_RIGHT)) {
//        move.y += kCameraSpeed; // 右回転
//    }
//
//    // 角度を更新（移動量を rotation_ に加算）
//    rotation_.y += move.y;
//
//    // 変換行列を更新
//    worldTransform_.translation_ = translation_;
//    worldTransform_.rotation_ = rotation_;
//    worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
//
//    // カメラビュー行列を更新
//    camera_.matView = MathUtility::Inverse(worldTransform_.matWorld_);
//
//    // ワールド行列を更新
//    worldTransform_.UpdateMatrix();
//
//    // ImGui でデバッグ表示
//    ImGui::Begin("Camera");
//    ImGui::DragFloat3("Translation", &translation_.x, 0.01f);  // カメラ位置を変更
//    ImGui::DragFloat3("Rotation", &rotation_.x, 0.01f);        // カメラ回転を変更
//    ImGui::End();
//}

