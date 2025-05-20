#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class Fragment {
public:
	~Fragment();

	void Initialize(Model* model, Vector3 pos, Camera* camera);

	void Update();

	void Draw();

private:
	Model* model_;

	static inline const uint32_t kNum = 8;

	std::array<WorldTransform, kNum> worldTransforms_;

	Camera* camera_ = nullptr;

	ObjectColor objectColor_;
	Vector4 color_;
};
