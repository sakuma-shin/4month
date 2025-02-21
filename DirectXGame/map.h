#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

class map {
public:

	void mapcopy(const std::string& filePath);

	private:
	int mapWidth;                          // マップの幅
	int mapHeight;                         // マップの高さ
	const int tileSize = 32;               // マップチップ1つのサイズ
	std::vector<std::vector<int>> mapData; // マップデータ
};
