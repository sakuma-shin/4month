#include "Player.h"

using namespace KamataEngine;

Player::~Player()
{



}

void Player::Initialize(KamataEngine::Model* model, uint32_t textureHandle,KamataEngine::Camera* camera)
{

	//NULLチェック
	assert(model);

	//引数の内容をメンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;

	//インスタンス
	input_ = Input::GetInstance();

	//ワールド変換の初期化
	worldTransform_.Initialize();


}

void Player::Update()
{

	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	//キャラクターの移動速度
	const float kCharacterSpeed = 0.2f;

	//押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_A)) {

		move.x -= kCharacterSpeed;

	}

	if (input_->PushKey(DIK_D)) {

		move.x += kCharacterSpeed;

	}

	//押した方向で移動ベクトルを変更(上下)
	if (input_->PushKey(DIK_W)) {

		move.z += kCharacterSpeed;

	}

	if (input_->PushKey(DIK_S)) {

		move.z -= kCharacterSpeed;

	}

	//座標移動
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.z += move.z;

	worldTransform_.TransferMatrix();
	worldTransform_.UpdateMatrix();

}

void Player::Draw(Camera* camera)
{

	model_->Draw(worldTransform_,*camera,textureHandle_);

}
