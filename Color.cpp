#include "Color.h"

using namespace KamataEngine;

void Color::Initialize()
{

	//インスタンス
	input_ = Input::GetInstance();

}

void Color::Update()
{

	SetColor(red_, blue_, green_);

	if (input_->PushKey(DIK_RETURN)) {

		// 色を分解
		int redPart = 0;
		int bluePart = 0;
		SplitColor1(redPart, bluePart);

		DebugText::GetInstance()->ConsolePrintf("Red: %d, Blue: %d", redPart, bluePart);

	}


}

void Color::Draw()
{

	

}

void Color::SetColor(int red, int blue, int green)
{

	red_ = red;
	blue_ = blue;
	green_ = green;

}

void Color::SplitColor1(int& color1, int& color2)
{

	color1 = red_;
	color2 = blue_;

}
