#ifndef OBJECT_H
#define OBJECT_H
#pragma once

#include <string>
#include <vector>
#include <armadillo>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "Vertex.hpp"
#include "Face.hpp"


using namespace std;

class Object
{
private:
    vector<Face> faces;
    vector<Vertex> vertices;
    vector<string> split(const string &str, const string &delim);
    int numVertices=0;
    int numCaras=0;
    string nom;


public:
    Object(string file);
    void print();
    vector<Face> get_faces();
    vector<Vertex> get_vertices();
    void draw(float r, float g, float b, float tam, float posx, float posy, float posz, float ka, float Ia, float kd, float Ip, arma::frowvec3 F);
};
#endif