#ifndef OPENGL_H
#define OPENGL_H
#include <stdio.h>
#include <stdlib.h>
#include <armadillo>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include "Transf.hpp"
#include "GolfBall.hpp" 
#include "GolfClub.hpp"
#include "GolfPole.hpp"
#include "Person.hpp"

#pragma once

class OpenGL
{
public:
    OpenGL();
    int open();
    void printCommnts();

private:
    float Ip;
    float Ia;
    arma::frowvec eye;
    arma::frowvec camera;
    void calcXY(double posx, double posy);
};

#endif