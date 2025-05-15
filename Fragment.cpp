#include "Fragment.h"
#include "MathUtility.h"

void Fragment::Initialize(Model* model, Vector3 pos, Camera* camera) {
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		worldTransform.translation_ = pos;
	}
	model;
	camera_ = camera;

	objectColor_.Initialize();
	color_ = {1, 1, 1, 1};
}

void Fragment::Update() {
	for (auto& worldTransform : worldTransforms_) {
		RotateXYZMatrix(worldTransform.rotation_);
		MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_);
		worldTransform.UpdateMatrix();
	}
}

void Fragment::Draw() {
	for (auto& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, *camera_, &objectColor_);
	}
}
