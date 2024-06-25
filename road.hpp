// Tuvia Smadar
// gunslokij@gmail.com
#ifndef ROAD_HPP
#define ROAD_HPP
#pragma once
#include "land.hpp"
using namespace std;
// Forward declaration of Land class
class Land;
class Road
{
public:
Road(const Land*, const Land*, size_t);
Road(size_t);
Road(const Road&); // Copy constructor
Road &operator=(const Road&);
bool operator==(const Road&) const;

// Accessor methods
size_t getIndex() const;
void setOwner(int);
int getOwner() const;
const Land &getLand1() const;
const Land &getLand2() const;
void setLands(Land*, Land*);

private:
const Land *land1; // First connected land
const Land *land2; // Second connected land
size_t index; // Unique identifier for the road
int owner; // Player ID of the road's owner
};
#endif