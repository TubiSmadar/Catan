// Tuvia Smadar
// gunslokij@gmail.com
#include "hextile.hpp"

Hextile::Hextile(const string& resource, int number, size_t index)
    : resource(resource), number(number), index(index), lands{}, roads{} {}


void Hextile::setLand(Land& land) {
    {
        lands.push_back(&land);
    }
}

void Hextile::setRoad(int position, const Road& road) {
    if (position >= 0 && position < 6) {
        roads[position] = road; 
    }
}

string Hextile::getResource() const {
    return resource;
}

int Hextile::getNumber() const {
    return number;
}

size_t Hextile::getIndex() const {
    return index;
}

 vector< Land*>& Hextile::getLands() {
    return lands;
}

const vector<Road>& Hextile::getRoads() const {
    return roads;
}