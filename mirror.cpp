#include "mirror.h"


using namespace KamataEngine;

void mirror::Initialize(KamataEngine::WorldTransform* worldtransform, int x, int z,Map* map) {
	worldtransform_ = worldtransform;
	mirrormodel_ = Model::CreateFromOBJ("mirorr", true);
	mirrormodel2_ = Model::CreateFromOBJ("mirorr2", true);
	textureHandle_ = TextureManager::Load("mirorr/mirorr.png");
	preworldtransform_ = worldtransform;
	input_ = Input::GetInstance();

	map_ = map;

	Pos[0] = x;
	Pos[1] = z;
}

void mirror::Update(Player* player) { 
	player_ = player;
	if (isInsideRhombus(this->worldtransform_->translation_, Vector3(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z))) {
		textureHandle_ = TextureManager::Load("mirorron/mirorr.png");
	}
	else {
		textureHandle_ = TextureManager::Load("mirorr/mirorr.png");
	}
	if (time == 0) {

		if (input_->PushKey(DIK_B) && isInsideRhombus(this->worldtransform_->translation_, Vector3(player->GetPosition().x, player->GetPosition().y, player->GetPosition().z))) {
			// textureHandle_ = TextureManager::Load("mirorron/mirorr.png");
			if (input_->PushKey(DIK_W) && map_->CheckCollision(Vector3(worldtransform_->translation_.x, worldtransform_->translation_.y, worldtransform_->translation_.z+2.0f))==0) {
				worldtransform_->translation_.z += 2;
				worldtransform_->TransferMatrix();
				worldtransform_->UpdateMatrix();
				
				time = 30;
			} else if (input_->PushKey(DIK_A) && map_->CheckCollision(Vector3(worldtransform_->translation_.x - 2.0f, worldtransform_->translation_.y, worldtransform_->translation_.z)) == 0) {
				worldtransform_->translation_.x -= 2;
				worldtransform_->TransferMatrix();
				worldtransform_->UpdateMatrix();
				
				time = 30;
			} else if (input_->PushKey(DIK_S) && map_->CheckCollision(Vector3(worldtransform_->translation_.x, worldtransform_->translation_.y, worldtransform_->translation_.z - 2.0f)) == 0) {
				worldtransform_->translation_.z -= 2;
				worldtransform_->TransferMatrix();
				worldtransform_->UpdateMatrix();
				
				time = 30;
			} else if (input_->PushKey(DIK_D) && map_->CheckCollision(Vector3(worldtransform_->translation_.x + 2.0f, worldtransform_->translation_.y, worldtransform_->translation_.z)) == 0) {
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
	if (i == 1) {
		mirrormodel2_->Draw(*worldtransform_, *camera, textureHandle_);
	}
	else if(i == 2) { 
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
