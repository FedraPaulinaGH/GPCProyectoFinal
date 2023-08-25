#ifndef GOLFBALL_H
#define GOLFBALL_H

#pragma once

#include <armadillo>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <vector> 

#include "Object.hpp"
#include "Transf.hpp"

class GolfBall: public Object
{
public:
    GolfBall(string file, float r, float g, float b, float ka, float kd);
    void draw(float Ia, float Ip, arma::frowvec3 F);
    void estableceCurva(float x, float y,float force);
    void calculaCurva();

private:
    float r,g,b;
    float ka;
    float kd;
    float xx, yy;
    int pos_curva;
    vector<Vertex> curva;
    Transf Tr = Transf();
    arma::Mat<double> matrix;
    void set_transf(arma::Mat<double> transf);
};

#endif