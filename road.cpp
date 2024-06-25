// Tuvia Smadar
// gunslokij@gmail.com
#include "road.hpp"
#include "land.hpp"

Road::Road(const Land* land1, const Land* land2, size_t index) : land1(land1), land2(land2), index(index), owner(-1) {}

Road::Road(size_t index) : index(index), owner(-1) {}

Road::Road(const Road& other) {
    this->land1 = other.land1;
    this->land2 = other.land2;
    this->index = other.index;
    this->owner = other.owner;
}

Road& Road::operator=(const Road& other) {
    if (this != &other) {
        this->land1 = other.land1;
        this->land2 = other.land2;
        this->index = other.index;
        this->owner = other.owner;
    }
    return *this; 
}
bool Road::operator==(const Road& other)const{
    if (this->getIndex() == other.getIndex() && this->getLand1() == other.getLand1() && this->getLand2() == other.getLand2())
    {
        return true;
    }
    return false;
}

size_t Road::getIndex() const {
    return index;
}

void Road::setOwner(int playerId) {
    owner = playerId;
}

int Road::getOwner() const {
    return owner;
}

const Land& Road::getLand1() const {
    return *land1;
}

const Land& Road::getLand2() const {
    return *land2;
}

void Road::setLands(Land* land1, Land* land2) {
    this->land1 = land1;
    this->land2 = land2;
}
