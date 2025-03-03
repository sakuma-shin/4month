#include "MapChipFIeld.h"
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

namespace {

    std::map<std::string, MapChipType> mapChipTable = {

    {"0", MapChipType::kBlank},

    {"8", MapChipType::kBlock}, //壁

    };

};
void MapChipField::ResetMapChipData()
{

    // マップチップデータをリセット
    mapChipData_.data.clear();
    mapChipData_.data.resize(kNumBlockVirtical);

    for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data) {

        mapChipDataLine.resize(kNumBlockHorizontal);

    }

}

void MapChipField::LoadMapChipCsv(const std::string& filePath)
{

    // マップチップデータをリセット
    ResetMapChipData();

    // ファイルを開く
    std::ifstream file;
    file.open(filePath);
    assert(file.is_open());

    // マップチップCSV
    std::stringstream mapChipCsv;

    // ファイルの内容を文字列ストリームにコピー
    mapChipCsv << file.rdbuf();

    // ファイルを閉じる
    file.close();

    // CSVからマップチップデータを読み込む
    for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {

        std::string line;
        getline(mapChipCsv, line);

        // 1行目の文字列をストリームに変換して解析しやすくする
        std::istringstream line_stream(line);

        for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {

            std::string word;
            getline(line_stream, word, ',');

            if (mapChipTable.contains(word)) {

                mapChipData_.data[i][j] = mapChipTable[word];

            }

        }

    }

}
