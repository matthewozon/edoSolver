#ifndef C_CIRCLE_H
#define C_CIRCLE_H

#include <C_edoSolver.h>

class C_circle : public C_edoSolver
{
public:
    C_circle();
    virtual double* F(double x, double y, double z, double t);

    std::vector<Point> solveCircleEuler(double x0, double y0, double z0, double dt, unsigned long N);
    std::vector<Point> solveCircleRK4(double x0, double y0, double z0, double dt, unsigned long N);
};

#endif // C_CIRCLE_H
