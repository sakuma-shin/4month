#include "Player.h"
#include <cassert>

using namespace KamataEngine;

void Player::Initialize(Model* model, Camera* camera)
{

	assert(model);
	worldTransform_.Initialize();

	model_ = model;
	camera_ = camera;

}

void Player::Update()
{
}

void Player::Draw()
{
}
