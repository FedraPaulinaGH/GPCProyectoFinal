#include "../include/OpenGL.hpp"
vector <float> eyes = {0.0, 0.0, 10.0};
vector<float> cams = {0.0, 0.0, 0.0};
double xpos, ypos;
float xx, yy, frc=1.0;
int bul=0;

OpenGL::OpenGL()
{
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        //cout << "Lado izquierdo" << endl;
        eyes = {-10.0, 0.0, 0.0};
        cams = {0.0, 0.0, 0.0};
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        // cout << "Centro" << endl;
        eyes = {0.0, 0.0, 10.0};
        cams = {0.0, 0.0, 0.0};
    }

    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        //cout << "Lado derecho" << endl;
        eyes = {10.0, 0.0, 0.0};
        cams = {0.0, 0.0, 0.0};
    }

    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    {
        //disminuye valor de fuerza
        frc -= 0.15;
        cout << frc << endl;
    }

    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
        //aumenta valor de fuerza
        frc += 0.15;
        cout << frc << endl;
    }
}

void OpenGL::calcXY(double posx, double posy)
{ // 51.2=-0.9
    float r = 0, whole;

    if (posx > 512)
    {
        r = (float(xpos) / 512);
        xx = modf(r, &whole);
    }
    else
    {
        r = ((float(xpos) * (0.1)) / 51.2);
        xx = r - 1;
    }

    if (posy > 374.5)
    {
        r = (float(ypos)/374.5);
        yy = (r - 1) * (-1);
    }
    else
    {
        r = float(ypos)/374.5;
        yy = 1 - r;
    }
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        // getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        cout << "Cursor Position at (" << xpos << " : " << ypos << endl;
        if(frc<=1.0)
            frc = 1.01;
        if(frc>=4)
            frc = 3.9;

        cout << "Fuerza: " << frc << endl;
        bul = 1;
    }
}

void OpenGL::printCommnts()
{
    cout << "Modifique la magnitud de la fuerza utilizando las teclas de flecha (Arrow Keys) " << endl;
    cout << "Presione la tecla de flecha hacia arriba para incrementar la magnitud de la fuerza" << endl;
    cout << "Presione la tecla de flecha hacia abajo para disminuir la magnitud de la fuerza" << endl;
    cout << "De clic sobre el botón izquierdo del mouse para elegir el punto de partida de la pelota (en X)" << endl;
    cout << "Presione la tecla A para cambiar a la vista lateral izquierda" << endl; 
    cout << "Presione la tecla D para cambiar a la vista lateral derecha" << endl;
    cout << "Presione la tecla S para regresar a la vista central" << endl;
}

int OpenGL::open()
{
    xx = 0.0;
    GLFWwindow *window;

    GolfBall ball = GolfBall("models/golfball.ply", 1.0, 1.0, 1.0, 0.9, 0.8); //(file, r, g, b, ka, kd)
    GolfClub club = GolfClub("models/golfclub.ply");
    GolfPole pole = GolfPole("models/golfpole.ply");
    Person person = Person("models/person.ply");

    if (!glfwInit())
    {
        cout << stderr << "Fallo al inicializar GLFW." << endl;
        getchar();
        return -1;
    }

    window = glfwCreateWindow(1024, 768, "Golf-ito", NULL, NULL);
    if (window == NULL)
    {
        cout << stderr << "Fallo al abrir la ventana de GLFW." << endl;
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //  Proyecciones
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    float ar = width / height;

    //  Proyección en paralelo
    glViewport(0, 0, width, height);
    glOrtho(-ar, ar, -1.0, 1.0, -20.0, 20.0);

    //  Proyección en perspectiva
    //glFrustum(-ar, ar, -ar, ar, 2.0, 4.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //ball.estableceCurva(force); // 1.2
    float Ia = 0.9;
    arma::frowvec3 F = {0.0, 10.0, 0.0}; // eje y
    float Ip = 0.8;
    
    

    do
    {
        this->eye = eyes;
        this->camera = cams;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(this->eye[0], this->eye[1], this->eye[2],
                  this->camera[0], this->camera[1], this->camera[2],
                  0.0, 1.0, 0.0);

        //   draw(  r,    g,   b,  tam,   posx, posy, posz,  ka, Ia,  kd, Ip, F)
        club.draw(1.0, 0.0, 1.0, 0.15, -0.75, -0.7, 0.85, 0.5, Ia, 0.6, Ip, F);
        pole.draw(0.0, 0.0, 1.0, 0.037, 0.80, 0.0, -0.9, 0.5, Ia, 0.6, Ip, F);
        person.draw(1.0, 0.0, 0.0, 0.09, -0.85, -0.7, 0.85, 0.6, Ia, 0.9, Ip, F);

        if(bul==0)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetMouseButtonCallback(window, mouse_button_callback);
            glfwSetKeyCallback(window, key_callback);
        }
        else if(bul==1)
        {
            calcXY(xpos, ypos);
            ball.estableceCurva(xx, yy, frc);
            ball.calculaCurva();
            ball.draw(Ia, Ip, F);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    glfwTerminate();

    return 0;
}