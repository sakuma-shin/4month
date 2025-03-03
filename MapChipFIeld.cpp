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
}
