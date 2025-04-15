#include "TitleScene.h"
#include <input/Input.h>
#include <cmath>
#include <numbers>

TitleScene::~TitleScene() {

	delete fade_;
	delete sprite_;

}

void TitleScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);

	titleTextureHandle_ = KamataEngine::TextureManager::Load("./Resources./color./black.png");
	sprite_ = KamataEngine::Sprite::Create(titleTextureHandle_, { 0,0 });

}

void TitleScene::Update() {

	switch (phase_) {

	case FadePhase::kFadeIn:
		if (fade_->isFinished()) {
			phase_ = FadePhase::kMain;
		}
		break;

	case FadePhase::kMain:
		if (input_->TriggerKey(DIK_SPACE)) {
			phase_ = FadePhase::kfadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
		}
		break;

	case FadePhase::kfadeOut:
		if (fade_->isFinished()) {
			isFinished_ = true;
		}
		break;
	}

	fade_->Update();
}

void TitleScene::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	KamataEngine::Sprite::PreDraw(commandList);

	sprite_->Draw();
	fade_->Draw(commandList);

	KamataEngine::Sprite::PostDraw();
	dxCommon_->ClearDepthBuffer();

}
