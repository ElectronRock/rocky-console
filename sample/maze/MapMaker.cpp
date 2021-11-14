#include "MapMaker.h"
#include <random>

MapMaker::TMap MapMaker::Make(unsigned w, unsigned h)
{
    TMap result;
    
    std::random_device dev;
    std::mt19937 rng(dev());
    const std::uniform_int_distribution<std::mt19937::result_type> dist100(0, 100);

    for (unsigned i = 0; i < w; ++i) 
    {
        std::vector<EntityType> line;
        for (unsigned j = 0; j < h; ++j) 
        {
            const auto r = dist100(rng);
            const auto type = r % 100 < 32 ? EntityType::Wall : EntityType::Field;
            line.emplace_back(type);
        }
        result.push_back(line);
    }
    
    return result;
}
