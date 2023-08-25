#include "../include/Object.hpp"
#include "../include/Transf.hpp"
#include "../include/GolfBall.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

Object::Object(string file)
{
    string line;
    this->nom = file;
    vector<Vertex> vertices = {};
    vector<Face> faces = {};
    int nVer, nFaces;

    ifstream archivo(file);
    while (getline(archivo, line))
    {
        vector<string> elems = split(line, " ");
        if (!elems.empty())
        {
            if ((elems[0].compare("element") == 0) && (elems[1].compare("vertex")==0))
            {
                nVer = stoi(split(elems[2], " ")[0]);
                this->numVertices = nVer;            
            }
            else if ((elems[0].compare("element") == 0 && elems[1].compare("face")==0))
            {
                nFaces = stoi(split(elems[2], " ")[0]);
                this->numCaras = nFaces;                
            }

            if(elems[0].compare("end_header")==0)
            {
                getline(archivo, line);
                elems = split(line, " ");
                while (nVer > 0)
                {
                    float x = stof(elems[0]);
                    float y = stof(elems[1]);
                    float z = stof(elems[2]);
                    Vertex v(x, y, z);
                    vertices.push_back(v);
                    getline(archivo, line);
                    elems = split(line, " ");
                    nVer--;
                }
                while(nFaces>0)
                {
                    int va1 = stoi(elems[1]);
                    int va2 = stoi(elems[2]);
                    int va3 = stoi(elems[3]);
                    Vertex v1 = vertices[va1];
                    Vertex v2 = vertices[va2];
                    Vertex v3 = vertices[va3];

                    Face f(v1, v2, v3, {va1 , va2 , va3});
                    f.calcEcPlano(v1, v2, v3);

                    faces.push_back(f);
                    getline(archivo, line);
                    elems = split(line, " ");
                    nFaces--;
                }
            }
        }
    }
    this->vertices = vertices;
    this->faces = faces;
}

vector<string> Object::split(const string &str, const string &delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos)
            pos = str.length();
        string token = str.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

void Object::print()
{
    cout << "Archivo: " << this->nom << endl;
    cout << "vertices: " << this->numVertices << endl;
    cout << "caras: " << this->numCaras << endl;

    for (Vertex v : vertices)
    {
        v.print();
    }
    for (Face F : faces)
    {
        F.print();
    }
    cout << endl;
}

vector<Face> Object::get_faces()
{
    return this->faces;
}

vector<Vertex> Object::get_vertices()
{
    return this->vertices;
}

void Object::draw(float r, float g, float b, float tam, float posx, float posy, float posz, float ka, float Ia, float kd, float Ip, arma::frowvec3 F)
{
    Transf Tr = Transf();

    arma::Mat<double> s_transf = Tr.S(1, 1, 1);
    arma::Mat<double> t_transf = s_transf * Tr.T(posx, posy, posz) * Tr.S(tam, tam, tam);

    vector<Face> faces = this->get_faces();
    vector<Vertex> vertices = this->get_vertices();

    
    glBegin(GL_TRIANGLES);
    for (Face f : faces)
    {
        arma::frowvec3 N = f.get_normal();

        arma::frowvec3 V = {this->vertices[0].getX(), 
                            this->vertices[0].getY(), 
                            this->vertices[0].getZ()};

        arma::frowvec3 L = F - V;
        L = arma::normalise(L);
        float costheta = arma::dot(N, L);
        float I = (Ia * ka) + (Ip * kd * costheta);

        float rn = r * I;
        float gn = g * I;
        float bn = b * I;

        glColor3f(rn, gn, bn);
        // Recorrer los vértices de la cara
        for (long v_ind : f.getVertexIndx())
        {
            // Dibujar el objeto....
            arma::Col<double> vp = t_transf * vertices[v_ind].homg();
            glVertex3f(vp.at(0), vp.at(1), vp.at(2));
        }
    }
    glEnd(); 
}