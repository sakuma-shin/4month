#pragma once
#include <KamataEngine.h>
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include"math/Vector2.h"
#include "Target.h"

class door {
public:
	void Initialize(int key, std::vector<Target*> target, int x, int z);
	void Update(std::vector<Target*> target);
	void Draw(KamataEngine::WorldTransform* worldtransform, KamataEngine::Camera* camera);
	bool keyopen();
	int Digit(int number);

	int Digitnamber(int number);

	int UnFirstnumber(int number);

	bool IsOpen()const { return openflag; }
	int GetX() const { return x_; }
	int GetZ() const { return z_; }

private:
	KamataEngine::Model* doormodel_;
	bool openflag = false;
	int key_;
	std::vector<Target*> target_;
	int x_;
	int z_;
};