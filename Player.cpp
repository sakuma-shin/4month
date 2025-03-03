#include "Player.h"
#include "MathUtility.h"

using namespace KamataEngine;

Player::~Player()
{



}

void Player::Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera)
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

	// プレイヤーの初期位置を設定
	worldTransform_.translation_ = { -5.0f, 4.0f, 0.0f };

}

void Player::Update()
{

	InputMove();

	//衝突情報を初期化
	CollisionMapInfo collisionMapInfo;

	//移動量に速度の値をコピー
	collisionMapInfo.move = worldTransform_.translation_;

	worldTransform_.TransferMatrix();
	worldTransform_.UpdateMatrix();

}

void Player::Draw(Camera* camera)
{

	model_->Draw(worldTransform_, *camera, textureHandle_);

}

void Player::InputMove()
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

}

void Player::CheckMapCollision(CollisionMapInfo& info)
{
	info;


}

void Player::CheckMapCollisionTop(CollisionMapInfo& info)
{
	//移動後の4つの角の座標
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {

		positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));

	}

	//奥方向当たり判定
	if (info.move.z <= 0) {

		return;

	}
}

void Player::CheckMapCollisionBottom(CollisionMapInfo& info)
{
	//手前方向当たり判定
	info;
}

void Player::CheckMapCollisionLeft(CollisionMapInfo& info)
{
	//左方向当たり判定
	info;
}

void Player::CheckMapCollisionRight(CollisionMapInfo& info)
{
	//右方向当たり判定
	info;
}

KamataEngine::Vector3 Player::CornerPosition(const KamataEngine::Vector3& center, Corner corner)
{

	Vector3 offsetTarble[kNumCorner] = {

		{kWidth / 2.0f,-kHeight / 2.0f,0},
		{-kWidth / 2.0f,-kHeight / 2.0f,0},
		{kWidth / 2.0f,kHeight / 2.0f,0},
		{-kWidth / 2.0f,kHeight / 2.0f,0}

	};

	//return center + offsetTarble[static_cast<uint32_t>(corner)];
	return Add(center, offsetTarble[static_cast<uint32_t>(corner)]);

}
