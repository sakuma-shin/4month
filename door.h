#pragma once
#include <KamataEngine.h>
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include"math/Vector2.h"
#include "Target.h"

class door {
public:
	void Initialize(int key, std::vector<Target*> target);
	void Update(std::vector<Target*> target);
	void Draw(KamataEngine::WorldTransform* worldtransform, KamataEngine::Camera* camera);
	bool keyopen();

	bool Getopenflag() { 
		return openflag;
	}
	int Digit(int number);

	int Digitnamber(int number);

	int UnFirstnumber(int number);

private:
	KamataEngine::Model* doormodel_;
	bool openflag = false;
	int key_;
	std::vector<Target*> target_;
};