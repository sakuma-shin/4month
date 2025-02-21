#include "map.h"


void map::mapcopy(const std::string& filePath) {
	std::ifstream file(filePath);
	std::string line;

	while (std::getline(file, line)) {
		std::istringstream lineStream(line);
		std::vector<int> row;
		std::string cell;
		while (std::getline(lineStream, cell, ',')) {
			row.push_back(std::stoi(cell));
		}
		mapData.push_back(row);
	}

	mapHeight = static_cast<int>(mapData.size());
	mapWidth = mapHeight > 0 ? static_cast<int>(mapData[0].size()) : 0;
}
