#pragma once
#include <KamataEngine.h>
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include"math/Vector2.h"
#include "Target.h"

class door {
public:
	void Initialize(int key, std::vector<Target*> target,int x,int z,int number);
	void Update(std::vector<Target*> target);
	void Draw(KamataEngine::WorldTransform* worldtransform, KamataEngine::Camera* camera);
	bool keyopen();

	bool Getopenflag() { 
		return openflag;
	}
	int Digit(int number);

	int Digitnamber(int number);

	int UnFirstnumber(int number);

	int Getpos(int i) { 
		return pos[i];
	}
	int Getnumber() { return number_; }

private:
	KamataEngine::Model* doormodel_;
	bool openflag = false;
	int key_;
	std::vector<Target*> target_;
	int pos[2];
	int number_;
};