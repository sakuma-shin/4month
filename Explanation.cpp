#include "Explanation.h"

void ExplanationScene::Initialize()
{

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

}

void ExplanationScene::Update()
{

	if (input_->TriggerKey(DIK_SPACE)) {

		isFinished_ = true;

	}

}

void ExplanationScene::Draw()
{
}
