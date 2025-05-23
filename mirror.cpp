#include "mirror.h"

using namespace KamataEngine;

void mirror::Initialize(KamataEngine::WorldTransform* worldtransform, int x, int z, Map* map, int number) {
	worldtransform_ = worldtransform;
	mirrormodel_ = Model::CreateFromOBJ("mirorr", true);
	mirrormodel2_ = Model::CreateFromOBJ("mirorr2", true);
	textureHandle_ = TextureManager::Load("mirorr/mirorr.png");
	preworldtransform_ = worldtransform;
	input_ = Input::GetInstance();

	map_ = map;

	Pos[0] = x;
	Pos[1] = z;

	number_ = number;
}

void mirror::Update(Player* player) {
	player_ = player;

	if (isInsideRhombus(this->worldtransform_->translation_, Vector3(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z))) {
		textureHandle_ = TextureManager::Load("mirorron/mirorr.png");
	} else {
		textureHandle_ = TextureManager::Load("mirorr/mirorr.png");
	}
	if (time == 0) {

		if (input_->PushKey(DIK_SPACE) && isInsideRhombus(this->worldtransform_->translation_, Vector3(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z))) {
			// textureHandle_ = TextureManager::Load("mirorron/mirorr.png");
			if (input_->PushKey(DIK_W) && map_->CheckCollision(Vector3(worldtransform_->translation_.x, worldtransform_->translation_.y, worldtransform_->translation_.z + 2.0f)) == 0 &&
			    (map_->CheckCollision({player_->GetPosition().x + 0.3f, player_->GetPosition().y, player_->GetPosition().z + 1.8f + 2}) == 0 &&
			         map_->CheckCollision({player_->GetPosition().x + 1.8f, player_->GetPosition().y, player_->GetPosition().z + 1.8f + 2}) == 0 ||
			     map_->CheckCollision({player_->GetPosition().x + 0.3f, player_->GetPosition().y, player_->GetPosition().z + 1.8f + 2}) == 31 &&
			         map_->CheckCollision({player_->GetPosition().x + 1.8f, player_->GetPosition().y, player_->GetPosition().z + 1.8f + 2}) == 31 ||
			     map_->CheckCollision({player_->GetPosition().x + 0.3f, player_->GetPosition().y, player_->GetPosition().z + 1.8f + 2}) == 32 &&
			         map_->CheckCollision({player_->GetPosition().x + 1.8f, player_->GetPosition().y, player_->GetPosition().z + 1.8f + 2}) == 32)

			) {
				worldtransform_->translation_.z += 2;
				worldtransform_->TransferMatrix();
				worldtransform_->UpdateMatrix();

				time = 30;
			} else if (
			    input_->PushKey(DIK_A) && map_->CheckCollision(Vector3(worldtransform_->translation_.x - 2.0f, worldtransform_->translation_.y, worldtransform_->translation_.z)) == 0 &&
			    (map_->CheckCollision({player_->GetPosition().x - 2 + 0.3f, player_->GetPosition().y, player_->GetPosition().z + 0.3f}) == 0 &&
			         map_->CheckCollision({player_->GetPosition().x - 2 + 0.3f, player_->GetPosition().y, player_->GetPosition().z + 1.8f}) == 0 ||
			     map_->CheckCollision({player_->GetPosition().x - 2 + 0.3f, player_->GetPosition().y, player_->GetPosition().z + 0.3f}) == 31 &&
			         map_->CheckCollision({player_->GetPosition().x - 2 + 0.3f, player_->GetPosition().y, player_->GetPosition().z + 1.8f}) == 31 ||
			     map_->CheckCollision({player_->GetPosition().x - 2 + 0.3f, player_->GetPosition().y, player_->GetPosition().z + 0.3f}) == 32 &&
			         map_->CheckCollision({player_->GetPosition().x - 2 + 0.3f, player_->GetPosition().y, player_->GetPosition().z + 1.8f}) == 32)) {
				worldtransform_->translation_.x -= 2;
				worldtransform_->TransferMatrix();
				worldtransform_->UpdateMatrix();

				time = 30;
			} else if (
			    input_->PushKey(DIK_S) && map_->CheckCollision(Vector3(worldtransform_->translation_.x, worldtransform_->translation_.y, worldtransform_->translation_.z - 2.0f)) == 0 &&
			    (map_->CheckCollision({player_->GetPosition().x + 1.8f, player_->GetPosition().y, player_->GetPosition().z + 0.3f - 2}) == 0 &&
			         map_->CheckCollision({player_->GetPosition().x + 1.8f, player_->GetPosition().y, player_->GetPosition().z + 1.8f - 2}) == 0 ||
			     map_->CheckCollision({player_->GetPosition().x + 1.8f, player_->GetPosition().y, player_->GetPosition().z + 0.3f - 2}) == 31 &&
			         map_->CheckCollision({player_->GetPosition().x + 1.8f, player_->GetPosition().y, player_->GetPosition().z + 1.8f - 2}) == 31 ||
			     map_->CheckCollision({player_->GetPosition().x + 1.8f, player_->GetPosition().y, player_->GetPosition().z + 0.3f - 2}) == 32 &&
			         map_->CheckCollision({player_->GetPosition().x + 1.8f, player_->GetPosition().y, player_->GetPosition().z + 1.8f - 2}) == 32)) {
				worldtransform_->translation_.z -= 2;
				worldtransform_->TransferMatrix();
				worldtransform_->UpdateMatrix();

				time = 30;
			} else if (
			    input_->PushKey(DIK_D) && map_->CheckCollision(Vector3(worldtransform_->translation_.x + 2.0f, worldtransform_->translation_.y, worldtransform_->translation_.z)) == 0 &&
			    (map_->CheckCollision({player_->GetPosition().x + 2 + 0.3f, player_->GetPosition().y, player_->GetPosition().z + 0.3f}) == 0 &&
			         map_->CheckCollision({player_->GetPosition().x + 2 + 1.8f, player_->GetPosition().y, player_->GetPosition().z + 0.3f}) == 0 ||
			     map_->CheckCollision({player_->GetPosition().x + 2 + 0.3f, player_->GetPosition().y, player_->GetPosition().z + 0.3f}) == 31 &&
			         map_->CheckCollision({player_->GetPosition().x + 2 + 1.8f, player_->GetPosition().y, player_->GetPosition().z + 0.3f}) == 31 ||
			     map_->CheckCollision({player_->GetPosition().x + 2 + 0.3f, player_->GetPosition().y, player_->GetPosition().z + 0.3f}) == 32 &&
			         map_->CheckCollision({player_->GetPosition().x + 2 + 1.8f, player_->GetPosition().y, player_->GetPosition().z + 0.3f}) == 32)) {
				worldtransform_->translation_.x += 2;
				worldtransform_->TransferMatrix();
				worldtransform_->UpdateMatrix();

				time = 30;
			}
		}
	} else {
		time--;
	}
}

void mirror::Draw(int i, KamataEngine::Camera* camera) {
	if (Pos[0] == 6 && Pos[1] == 2) {
		Pos[0] = 6;
	}

	if (i == 1) {
		mirrormodel2_->Draw(*worldtransform_, *camera, textureHandle_);
	} else if (i == 2) {
		mirrormodel_->Draw(*worldtransform_, *camera, textureHandle_);
	}
}

bool mirror::isInsideRhombus(KamataEngine::Vector3 mirror, KamataEngine::Vector3 player) {
	// ひし形の半対角線長さは2
	float d = 2.2f;
	float x = player.x - mirror.x;
	float z = player.z - mirror.z;
	// ひし形の式：|x| + |y| <= 2 という条件を満たすかどうか
	return (std::abs(x) + std::abs(z) <= d);
}