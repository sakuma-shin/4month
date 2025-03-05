#include "Target.h"

void Target::Initialize(int number, KamataEngine::WorldTransform* worldTransform) { 
	coad = number % 10;
	color = (number % 100)/10;
	worldTransform_ = worldTransform;
}

void Target::Update() { 
	
}

void Target::Draw(KamataEngine::Camera* camera) {

}
