#include <iostream>
#include <vector>
#include "../include/Face.hpp"
#include "../include/Vertex.hpp"

using namespace std;


Face::Face(Vertex V1, Vertex V2, Vertex V3, vector<int> vertex_ind)
{
    this->v1=V1;    
    this->v2=V2;
    this->v3 = V3;
    this->vertex_ind=vertex_ind;
    set_fverts();
}

vector<int> Face::getVertexIndx()
{
    return this->vertex_ind;
}

void Face::set_fverts()
{
    this->fverts = {this->v1, this->v2, this->v3};
}

vector<Vertex> Face::get_fverts()
{
    return (this->fverts);
}

void Face::calcEcPlano(Vertex v1, Vertex v2, Vertex v3)
{
    Vertex v2v1 = Vertex(v2.getX() - v1.getX(), v2.getY() - v1.getY(), v2.getZ() - v1.getZ());
    Vertex v3v1 = Vertex(v3.getX() - v1.getX(), v3.getY() - v1.getY(), v3.getZ() - v1.getZ());
    this->A = (v2v1.getY() * v3v1.getZ()) - (v2v1.getZ() * v3v1.getY());
    this->B = (v2v1.getZ() * v3v1.getX()) - (v2v1.getX() * v3v1.getZ());
    this->C = (v2v1.getX() * v3v1.getY()) - (v2v1.getY() * v3v1.getX());
    this->D = -((A * v1.getX()) + (B * v1.getY()) + (C * v1.getZ()));
}

arma::frowvec3 Face::get_normal()
{
    arma::frowvec3 N = {this->A, this->B, this->C};
    N = arma::normalise(N);
    return (N);
}

void Face::print()
{
    // for (size_t i = 0; i < this->vertex_ind.size();i++)
    //{
    //     cout << this->vertex_ind.at(i) << " ";
    // }
    // cout << endl;
    cout << "\t Ecuacion del plano: ";
    cout << this->A << "x + ";
    cout << this->B << "y + ";
    cout << this->C << "z + ";
    cout << this->D << " = 0" << endl;
    cout << endl;
}