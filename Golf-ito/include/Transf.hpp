#ifndef TRANSF_H
#define TRANSF_H

#include <armadillo>
#include "Vertex.hpp"

#pragma once

class Transf
{
public:
    Transf();
    arma::Mat<double> T(double dx, double dy, double dz);
    arma::Mat<double> S(double sx, double sy, double sz);
    arma::Mat<double> Rx(double theta);
    arma::Mat<double> Ry(double theta);
    arma::Mat<double> Rz(double theta);
    arma::Mat<double> Rp1p2(Vertex P1, Vertex P2, double theta);

private:
};

#endif