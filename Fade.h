#pragma once
#include <KamataEngine.h>
#include <d3d12.h>

// フェーズ
enum class FadePhase {

	kFadeIn,
	kMain,
	kfadeOut

};

class Fade {

public:
	enum class Status {

		None,
		FadeIn,
		FadeOut

	};

public:
	~Fade();

	void Initialize();

	void Update();

	void Draw(ID3D12GraphicsCommandList* commandList);

	void Start(Status status, float duration);

	bool isFinished() const;

	void Stop();

private:
	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;

	// テクスチャハンドル
	uint32_t fadeTexture_ = 0;

	// 現在のフェードのの状態
	Status status_ = Status::None;

	// フェードの継続時間
	float duration_ = 0.0f;

	// カウンター
	float counter_ = 0.0f;
};