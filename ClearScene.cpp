#include "ClearScene.h"

ClearScene::~ClearScene()
{

	

}

void ClearScene::Initialize()
{

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

}

void ClearScene::Update()
{

	if (input_->TriggerKey(DIK_SPACE)) {

		isFinished_ = true;

	}

}

void ClearScene::Draw()
{
}
