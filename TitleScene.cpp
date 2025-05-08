#include "TitleScene.h"

TitleScene::~TitleScene() {}

void TitleScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("./Resources/proto/protoTitle.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0}, {1, 1, 1, 1}, {0, 0}, 0, 0);

	sceneChangeSoundHandle_ = audio_->LoadWave("sounds/firstMusic.mp3");

	
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);


}

void TitleScene::Update() {

	if (input_->TriggerKey(DIK_SPACE)) {

	/*	isFinished_ = true;*/
		if (audio_->IsPlaying(sceneChangeSoundHandle_)) {
			audio_->PlayWave(sceneChangeSoundHandle_,false,0.5f);
		}
	}

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
	if (this != nullptr) {
		Sprite::PreDraw(dxCommon_->GetCommandList());
		sprite_->Draw();
		fade_->Draw(dxCommon_->GetCommandList());
		Sprite::PostDraw();
	}
}
