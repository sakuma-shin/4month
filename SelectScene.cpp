#include "SelectScene.h"

SelectScene::~SelectScene() {

	delete fade_;

}

void SelectScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);

}

//void SelectScene::Update() {
//
//	switch (phase_) {
//
//	case FadePhase::kFadeIn:
//
//		if (fade_->isFinished()) {
//
//			phase_ = FadePhase::kMain;
//
//		}
//
//		break;
//
//	case FadePhase::kMain:
//
//		if (KamataEngine::Input::GetInstance()->TriggerKey(DIK_SPACE)) {
//
//			phase_ = FadePhase::kfadeOut;
//			fade_->Start(Fade::Status::FadeOut, 1.0f);
//
//		}
//
//		break;
//
//	case FadePhase::kfadeOut:
//
//		if (fade_->isFinished()) {
//
//			phase_ = FadePhase::kFadeIn;
//
//			isFinished_ = true;
//
//		}
//
//	}
//
//	if (input_->TriggerKey(DIK_SPACE)) {
//
//		isFinished_ = true;
//	}
//
//	if (input_->TriggerKey(DIK_RETURN)) {
//
//		isExplanation_ = true;
//
//	}
//
//}

void SelectScene::Update() {

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
			isFinished_ = true;  // フェード後にシーン終了
		}
		if (input_->TriggerKey(DIK_RETURN)) {
			phase_ = FadePhase::kfadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
			isExplanation_ = true;  // フェード後に説明画面へ
		}
		break;

	case FadePhase::kfadeOut:
		if (fade_->isFinished()) {
			// isFinished_ か isExplanation_ のどちらかが有効になっている
		}
		break;
	}
}


void SelectScene::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	KamataEngine::Sprite::PreDraw(commandList);
	fade_->Draw(commandList);

	KamataEngine::Sprite::PostDraw();
	dxCommon_->ClearDepthBuffer();

}
