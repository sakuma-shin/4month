#include "Fading.h"

void Fading::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	textureHandle_ = TextureManager::Load("./Resources/white1x1.png");
	alpha_ = 0;
	sprite_ = Sprite::Create(textureHandle_, {0, 0}, {0, 0, 0, float(alpha_)}, {0, 0}, 0, 0);
}

void Fading::Update() {
	/*ImGui::Begin("fade");
	if (!isFade_) {
	
	}
	if (ImGui::Button("fadeStart", {50, 50})) {
		if (!isFade_) {
			isFade_ = true;
		}
	}
		ImGui::End();*/
}

void Fading::Draw() {
	Sprite::PreDraw(dxCommon_->GetCommandList());
	sprite_->Draw();
	Sprite::PostDraw();
}

void Fading::Fade() {
	if (isFade_) {
		if (alpha_ >= 255) {
			isChanged_ = true;
		}
		if (!isChanged_) {
			alpha_ += 5;
		} else {
			alpha_ -= 5;
			if (alpha_ <= 0) {
				isChanged_ = false;
				isFade_ = false;
				alpha_ = 0;
			}
		}
	}
}
