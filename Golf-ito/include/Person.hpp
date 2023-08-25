#ifndef PERSON_H
#define PERSON_H

#pragma once

#include "Object.hpp"

class Person: public Object
{ 
public:
    Person(string file);

private:
    float r, g, b;
};

#endif