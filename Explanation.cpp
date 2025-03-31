#include "Explanation.h"
#include <base\DirectXCommon.h>

using namespace KamataEngine;

Explanation::~Explanation()
{

	delete sprite_;

}

void Explanation::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("./resources./color./green.png");
	sprite_ = KamataEngine::Sprite::Create(textureHandle_, { 0, 0 });


}

void Explanation::Update()
{

	if (input_->TriggerKey(DIK_RETURN)) {

		isFinished_ = true;

	}

}

void Explanation::Draw()
{

	dxCommon_ = KamataEngine::DirectXCommon::GetInstance();
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	KamataEngine::Sprite::PreDraw(commandList);
	sprite_->Draw();
	KamataEngine::Sprite::PostDraw();

}
