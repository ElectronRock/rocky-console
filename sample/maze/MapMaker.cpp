#include "MapMaker.h"
#include <random>

#define CHAR_BORDER '#'
#define CHAR_FIELD  ' '
#define COLOR_BORDER 1
#define COLOR_FIELD  2

MapMaker::tmap MapMaker::Make()
{
	tmap result;
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist100(0, 100);
        int i, j;
        for (i = 0; i < width; ++i) 
        {
            std::vector<EntityType> line;
            for (j = 0; j < height; ++j) {
                int r = dist100(rng);
                if ((r%100)<32) {
                    line.emplace_back(MapMaker::EntityType::Wall);
                }
                else {
                    line.emplace_back(MapMaker::EntityType::Field);
                }
            }
            result.push_back(line);
        }
    }
	return result;
}
