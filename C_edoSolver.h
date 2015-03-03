#ifndef C_EDOSOLVER_H
#define C_EDOSOLVER_H

//#include <rawData.h>

#include <sstream>
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>


#define MINIMAL   0
#define EVOLUTION 1


#define SQR(x) ((x)*(x))
#define Pi 3.141592653589793238462643383279502884197169399375105820974944592L

typedef struct _Point{
    double x;
    double y;
    double z;
} Point;


class C_edoSolver
{
    public:
        /** Default constructor */
        C_edoSolver();
        /** Default destructor */
        virtual ~C_edoSolver();

        bool saveCurves(std::string fileNameCurve, std::vector< std::vector<Point> > curve); //OK
        bool saveCurve(std::string fileNameCurve, std::vector<Point> curve);


        ///real streamline
        virtual double* F(double x, double y, double z, double t)=0; ///dr(x,y,z,t)/dt = F(x,y,z,t) //re-implemented
        double* EULERstep(double x, double y, double z, double t, double dt); //OK
        double* RK4step(double x, double y, double z, double t, double dt); //OK
        double* RK4K1(double x, double y, double z, double t, double dt); //OK
        double* RK4K2(double x, double y, double z, double k1x, double k1y, double k1z, double t, double dt); //OK
        double* RK4K3(double x, double y, double z, double k2x, double k2y, double k2z, double t, double dt); //OK
        double* RK4K4(double x, double y, double z, double k3x, double k3y, double k3z, double t, double dt); //OK

};

#endif // C_STREAMLINE_H
