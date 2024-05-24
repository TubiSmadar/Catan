#ifndef HEXTILE_HPP
#define HEXTILE_HPP
using namespace std;
namespace ariel {
    enum TerrainType {
        FOREST, //woods
        FIELD, //grain
        PASTURE, //goats
        MOUNTAIN, //rocks
        HILL, //blocks
        DESERT //robber
    };

    const char* terrainNames[] = {
        "Forest",
        "Field",
        "Pasture",
        "Mountain",
        "Hill",
        "Desert"
    };

    class Hextile {
        public:
            TerrainType terrain;
            int number; // Number for the production roll (0 if Desert)

            Hextile(TerrainType t, int n = 0) : terrain(t), number(n) {}
    };
}

#endif