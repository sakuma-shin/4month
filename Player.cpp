#include "Player.h"

using namespace KamataEngine;

void Player::Initialize(Model* model, Camera* camera, const Vector3& position)
{

	//NULLチェック
	assert(model);

	//引数の内容をメンバ変数に記録
	model_ = model;
	camera_ = camera;
	worldTransform_.translation_ = position;

	//ワールド座標初期化
	worldTransform_.Initialize();

}

void Player::Update()
{
}

void Player::Draw()
{
}
