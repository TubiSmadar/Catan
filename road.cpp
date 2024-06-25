// Tuvia Smadar
// gunslokij@gmail.com
#include "road.hpp"
#include "land.hpp"

// Constructor with lands and index
Road::Road(const Land* land1, const Land* land2, size_t index) : land1(land1), land2(land2), index(index), owner(-1) {}

// Constructor with only index
Road::Road(size_t index) : index(index), owner(-1) {}

// Copy constructor
Road::Road(const Road& other) {
    this->land1 = other.land1;
    this->land2 = other.land2;
    this->index = other.index;
    this->owner = other.owner;
}

// Assignment operator
Road& Road::operator=(const Road& other) {
    if (this != &other) {
        this->land1 = other.land1;
        this->land2 = other.land2;
        this->index = other.index;
        this->owner = other.owner;
    }
    return *this;
}

// Equality operator
bool Road::operator==(const Road& other) const {
    if (this->getIndex() == other.getIndex() && this->getLand1() == other.getLand1() && this->getLand2() == other.getLand2())
    {
        return true;
    }
    return false;
}

// Get the index of the road
size_t Road::getIndex() const {
    return index;
}

// Set the owner of the road
void Road::setOwner(int playerId) {
    owner = playerId;
}

// Get the owner of the road
int Road::getOwner() const {
    return owner;
}

// Get the first land connected to the road
const Land& Road::getLand1() const {
    return *land1;
}

// Get the second land connected to the road
const Land& Road::getLand2() const {
    return *land2;
}

// Set both lands connected to the road
void Road::setLands(Land* land1, Land* land2) {
    this->land1 = land1;
    this->land2 = land2;
}