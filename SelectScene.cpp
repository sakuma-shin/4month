#include "SelectScene.h"

SelectScene::~SelectScene() {
	for (int i = 0; i < 6; i++) {
		delete sprite_[i];
		TextureManager::Unload(textureHandle_[i]);
	}
	delete fade_;
}

void SelectScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	counter_ = 0.0f;

	textureHandle_[0] = TextureManager::Load("./Resources/proto/protoSelect.png");
	textureHandle_[1] = TextureManager::Load("./Resources/proto/protoSelect2.png");
	textureHandle_[2] = TextureManager::Load("./Resources/proto/protoSelect3.png");
	textureHandle_[3] = TextureManager::Load("./Resources/proto/protoSelect4.png");
	textureHandle_[4] = TextureManager::Load("./Resources/proto/protoSelect5.png");
	textureHandle_[5] = TextureManager::Load("./Resources/proto/protoSelect6.png");
	for (int i = 0; i < 6; i++) {
		sprite_[i] = Sprite::Create(textureHandle_[i], {0, 0}, {1, 1, 1, 1}, {0, 0}, 0, 0);
	}

	loadingTextureHandle_ = TextureManager::Load("./Resources/proto/protoLoading.png");
	loadingSprite_ = Sprite::Create(loadingTextureHandle_, {0, 0}, {1, 1, 1, 1}, {0, 0}, 0, 0);

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);
}

void SelectScene::Update() {
	if (input_->TriggerKey(DIK_I)) {

		isTutorial_ = true;
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

		counter_++;
		if (counter_ >= loadingTime) {
			isFinished_ = true;
		}
		break;
	}

	fade_->Update();
}

void SelectScene::Draw() {
	Sprite::PreDraw(dxCommon_->GetCommandList());
	if (this != nullptr) {
		sprite_[stageNum_ - 1]->Draw();

		if (phase_==FadePhase::kfadeOut&&counter_ <= loadingTime) {
			loadingSprite_->Draw();
		}

		if (!fade_->isFinished()) {
			fade_->Draw(dxCommon_->GetCommandList());
		}
		
 		
	}
	Sprite::PostDraw();
}

int SelectScene::SelectStage() {
	if (input_->TriggerKey(DIK_D)) {
		stageNum_++;
		if (stageNum_ >= 7) {
			stageNum_ = 1;
		}
	}
	if (input_->TriggerKey(DIK_A)) {
		stageNum_--;
		if (stageNum_ <= 0) {
			stageNum_ = 1;
		}
	}
	return stageNum_;
}