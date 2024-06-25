// Tuvia Smadar
// gunslokij@gmail.com
#pragma once
#include <string>
#include <array>
#include "land.hpp"
#include "road.hpp"

using namespace std;
class Land;
class Road;
class Hextile {
public:
    Hextile(const string& resource, int number, size_t index);

    void setLand(Land& land);
    void setRoad(int position, const Road& road);

    string getResource() const;
    int getNumber() const;
    size_t getIndex() const;

    vector<Land*>& getLands();
    const vector<Road>& getRoads() const;

private:
    string resource;
    int number;
    size_t index;
    vector<Land*> lands;
    vector<Road> roads;
    
};
