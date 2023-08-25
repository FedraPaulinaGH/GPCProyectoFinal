#include "../include/GolfBall.hpp"
#include "../include/Transf.hpp"
#include "../include/Bezier.hpp"
#include "../include/Line.hpp"
#include "../include/Vertex.hpp"

GolfBall::GolfBall(string file, float r, float g, float b, float ka, float kd) : Object(file)
{
    this->r=r; 
    this->g=g;    
    this->b=b;
    this->matrix = arma::eye(4, 4);
    this->curva = {};
    this->pos_curva = 0;
    this->ka=ka;
    this->kd = kd;
}

void GolfBall::set_transf(arma::Mat<double> transf)
{
    this->matrix = transf;
}


void GolfBall::draw(float Ia, float Ip, arma::frowvec3 F)
{
    arma::Mat<double> s_transf = this->Tr.S(1, 1, 1);         
    arma::Mat<double> t_transf = s_transf * this->Tr.T(this->xx, this->yy, 0.80) * this->Tr.S(0.015, 0.015, 0.015);

    vector<Face> gball_faces = this->get_faces();
    vector<Vertex> gball_vertices = this->get_vertices();

    glBegin(GL_TRIANGLES);
    for (Face f : gball_faces) 
    {
        arma::frowvec3 N = f.get_normal();

        arma::frowvec3 V = {gball_vertices[0].getX(), gball_vertices[0].getY(), gball_vertices[0].getZ()};
        arma::frowvec3 L = F - V;
        L = arma::normalise(L);
        float costheta = arma::dot(N, L);
        float I = (Ia * this->ka) + (Ip * this->kd * costheta);

        float rn = this->r * I;
        float gn = this->g * I;
        float bn = this->b * I;
        glColor3f(rn, gn, bn);

        // Recorrer los vértices de la cara
        for (long v_ind : f.getVertexIndx())
        {
            // Dibujar el objeto....
            arma::Col<double> vp = this->matrix * gball_vertices[v_ind].homg();
            glVertex3f(vp.at(0), vp.at(1), vp.at(2));
        }
    }
    glEnd();
}

void GolfBall::estableceCurva(float x, float y, float force)
{
    this->xx=x;
    this->yy=y;
    float aux = abs((this->yy) * force / 100);

    Vertex v1(this->xx, -0.7, 0.80);
    Vertex v2(0.0, aux, -0.1); // 
    double t = force;

    Vertex P1 = v1;
    Line l;
    Vertex P2 = l.line_t(v1, v2, t);
    Vertex P3(P2.getX() * t, P2.getY(), P2.getZ());
    Vertex P4(P2.getX() * (2 * t), 0.0, P2.getZ());

    Bezier bz(P1, P2, P3, P4);
    this->curva = bz.curva();
}

void GolfBall::calculaCurva() 
{
    arma::Mat<double> S = this->Tr.S(0.015, 0.015, 0.015);
    arma::Mat<double> T1 = this->Tr.T(curva[this->pos_curva].getX(),
                                    curva[this->pos_curva].getY(),
                                    curva[this->pos_curva].getZ());
    if (this->pos_curva < curva.size() - 1)
        this->pos_curva++;

    set_transf(T1*S);
}
  