#ifndef GOLFCLUB_H
#define GOLFCLUB_H

#pragma once

#include "Object.hpp"

class GolfClub: public Object
{
public:
    GolfClub(string file);
 
private:
    float r, g, b;
};

#endif