
#include "door.h"
#include "Map.h"

using namespace KamataEngine;

void door::Initialize(int key, std::vector<Target*> target, int x, int z) {
	doormodel_ = Model::CreateFromOBJ("door", true);
	key_ = key;
	target_ = target;
	pos[0] = x;
	pos[1] = z;
}


void door::Update(std::vector<Target*> target) {
	target_ = target;

	std::string windowName = "door_" + std::to_string(reinterpret_cast<uintptr_t>(this));
	ImGui::Begin(windowName.c_str());

	if (ImGui::Checkbox("opendoor", &openflag)) {

	}

	if (keyopen()) {
		openflag = true;
	}

	ImGui::End();
}


void door::Draw(KamataEngine::WorldTransform* worldtransform, KamataEngine::Camera* camera) {
	if (!openflag) {
		doormodel_->Draw(*worldtransform, *camera);
	}
}

bool door::keyopen() {
	int k = Digitnamber(key_);//何桁
	int number = key_;//番号
	int count = 0;
	for (int i = 0; i < k; i++) {
		int digit = Digit(number);
		for (Target* target : target_) {
			if (target->GetHit()) {
				if (digit == target->Getcoad()) {
					count++;
					if (k == count) {
						return true;
					} else {
						number = UnFirstnumber(number);
					}
				}
			}
		}

	}
	return false;

}

int door::Digit(int number) {
	if (number / 10 < 1) {
		return number;
	}
	int k = 0;
	for (; number / 10 >= 1; k++) {
		number = number / 10;
	}
	return number;
}

int door::Digitnamber(int number) {
	int k = 1;
	for (; number / 10 >= 1; ) {
		number = number / 10;
		k++;
	}
	return k;
}

int door::UnFirstnumber(int number) {
	int k = 1;
	for (int i = 1; i < Digitnamber(number); i++) {
		k *= 10;
	}

	return number - Digit(number) * (k);
}

