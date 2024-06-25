// Tuvia Smadar
// gunslokij@gmail.com

#ifndef ROAD_HPP
#define ROAD_HPP

#pragma once
#include "land.hpp"

using namespace std;
class Land;

class Road
{
public:
    Road(const Land*, const Land*, size_t);
    Road(size_t);
    Road(const Road&); // Copy constructor

    Road &operator=(const Road&);
    bool operator==(const Road&) const;
    // Getters and Setters
    size_t getIndex() const;
    void setOwner(int);
    int getOwner() const;
    const Land &getLand1() const;
    const Land &getLand2() const;

    void setLands(Land*, Land*);

private:
    const Land *land1;  // Pointer to the first land
    const Land *land2;  // Pointer to the second land
    size_t index; // Index of the road
    int owner;         // Owner of the road
};
#endif