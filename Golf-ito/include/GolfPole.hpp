#ifndef GOLFPOLE_H
#define GOLFPOLE_H

#pragma once

#include "Object.hpp"

class GolfPole: public Object
{
public:
    GolfPole(string file);

private:
    float r, g, b;
};

#endif