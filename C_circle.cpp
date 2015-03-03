#include <C_circle.h>

C_circle::C_circle():C_edoSolver()
{
}




double* C_circle::F(double x, double y, double z, double t)
{
    double* V = new double[3];
    V[0] = -y/sqrt(SQR(x)+SQR(y));
    V[1] = x/sqrt(SQR(x)+SQR(y));
    V[2] = 0.1;
    return V;
}


std::vector<Point> C_circle::solveCircleEuler(double x0, double y0, double z0, double dt, unsigned long N)
{
    std::vector<Point> myCircle;
    Point p;
    p.x = x0;
    p.y = y0;
    p.z = z0;
    double t = 0.0;
    double* V;
    myCircle.push_back(p);
    for(unsigned long i=0 ; i<N ; i++)
    {
        V = EULERstep(p.x,p.y,p.z,t,dt);
        t += dt;
        p.x += V[0];
        p.y += V[1];
        p.z += V[2];
        myCircle.push_back(p);
        delete V;
    }
    return myCircle;
}

std::vector<Point> C_circle::solveCircleRK4(double x0, double y0, double z0, double dt, unsigned long N)
{
    std::vector<Point> myCircle;
    Point p;
    p.x = x0;
    p.y = y0;
    p.z = z0;
    double t = 0.0;
    double* V;
    myCircle.push_back(p);
    for(unsigned long i=0 ; i<N ; i++)
    {
        V = RK4step(p.x,p.y,p.z,t,dt);
        t += dt;
        p.x += V[0];
        p.y += V[1];
        p.z += V[2];
        myCircle.push_back(p);
        delete V;
    }
    return myCircle;
}
