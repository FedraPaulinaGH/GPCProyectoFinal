#ifndef FACE_H
#define FACE_H
#pragma once

#include <vector>
#include "Vertex.hpp"

using namespace std; 

class Face
{
private:
    vector<int> vertex_ind;
    vector<Vertex> fverts;
    Vertex v1, v2, v3;
    float A, B, C, D;

public:
    Face(Vertex V1, Vertex V2, Vertex V3, vector<int> vertex_ind);
    void print();
    vector<int> getVertexIndx();
    void set_fverts();
    vector<Vertex> get_fverts();
    void calcEcPlano(Vertex v1, Vertex v2, Vertex v3);
    arma::frowvec3 get_normal();
};
#endif