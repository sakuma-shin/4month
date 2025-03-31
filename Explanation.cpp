#include "Explanation.h"
using namespace KamataEngine;

void Explanation::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
}

void Explanation::Update()
{

	if (input_->TriggerKey(DIK_SPACE)) {

		isFinished_ = true;

	}

}

void Explanation::Draw()
{
}
