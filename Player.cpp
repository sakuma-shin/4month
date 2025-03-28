#include "Player.h"
#include "Map.h"

using namespace KamataEngine;

Player::~Player() {}

void Player::Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera) {

	// NULLチェック
	assert(model);

	// 引数の内容をメンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;

	// インスタンス
	input_ = Input::GetInstance();

	// ワールド変換の初期化
	worldTransform_.Initialize();

	// プレイヤーの初期位置を設定
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void Player::Update(Map* map) {
	map_ = map;

	// キャラクターの移動ベクトル
	move = {0, 0, 0};

	// キャラクターの移動速度
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_A) && map_->CheckCollision({worldTransform_.translation_.x - kCharacterSpeed + 0.3f, worldTransform_.translation_.y, worldTransform_.translation_.z + 0.3f}) == 0 &&
	    map_->CheckCollision({worldTransform_.translation_.x - kCharacterSpeed + 0.3f, worldTransform_.translation_.y, worldTransform_.translation_.z + 1.8f}) == 0) {

		move.x -= kCharacterSpeed;
	}

	if (input_->PushKey(DIK_D) && map_->CheckCollision({worldTransform_.translation_.x + kCharacterSpeed + 1.8f, worldTransform_.translation_.y, worldTransform_.translation_.z + 0.3f}) == 0 &&
	    map_->CheckCollision({worldTransform_.translation_.x + kCharacterSpeed + 1.8f, worldTransform_.translation_.y, worldTransform_.translation_.z + 1.8f}) == 0) {

		move.x += kCharacterSpeed;
	}

	// 押した方向で移動ベクトルを変更(上下)
	if (input_->PushKey(DIK_W) && map_->CheckCollision({worldTransform_.translation_.x + 0.3f, worldTransform_.translation_.y, worldTransform_.translation_.z + kCharacterSpeed + 1.8f}) == 0 &&
	    map_->CheckCollision({worldTransform_.translation_.x + 1.8f, worldTransform_.translation_.y, worldTransform_.translation_.z + kCharacterSpeed + 1.8f}) == 0) {

		move.z += kCharacterSpeed;

	} else {
		move.z = 0;
	}

	if (input_->PushKey(DIK_S) && map_->CheckCollision({worldTransform_.translation_.x + 0.3f, worldTransform_.translation_.y, worldTransform_.translation_.z - kCharacterSpeed + 0.3f}) == 0 &&
	    map_->CheckCollision({worldTransform_.translation_.x + 1.8f, worldTransform_.translation_.y, worldTransform_.translation_.z - kCharacterSpeed + 0.3f}) == 0) {

		move.z -= kCharacterSpeed;
	}

	/*if (map_->CheckCollision(worldTransform_.translation_)) {
	    move = { 0,0,0 };
	}*/

	// 座標移動
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.z += move.z;

	worldTransform_.TransferMatrix();
	worldTransform_.UpdateMatrix();
}

void Player::Draw(Camera* camera) { model_->Draw(worldTransform_, *camera, textureHandle_); }
