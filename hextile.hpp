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

// Represents a hexagonal tile on the Catan board
class Hextile {
public:
    // Constructor: initializes a Hextile with a resource type, number, and index
    Hextile(const string& resource, int number, size_t index);

    // Adds a land vertex to this Hextile
    void setLand(Land& land);

    // Sets a road at a specific position around this Hextile
    void setRoad(int position, const Road& road);

    // Returns the resource type of this Hextile
    string getResource() const;

    // Returns the number token of this Hextile
    int getNumber() const;

    // Returns the index of this Hextile on the board
    size_t getIndex() const;

    // Returns a reference to the vector of Land pointers associated with this Hextile
    vector<Land*>& getLands();

    // Returns a const reference to the vector of Roads associated with this Hextile
    const vector<Road>& getRoads() const;

private:
    string resource;  // The resource type of this Hextile (e.g., "Wheat", "Ore", etc.)
    int number;       // The number token on this Hextile (2-12, except 7)
    size_t index;     // The index of this Hextile on the board
    vector<Land*> lands;  // The land vertices surrounding this Hextile
    vector<Road> roads;   // The roads bordering this Hextile
};