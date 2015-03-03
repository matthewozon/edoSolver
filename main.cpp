#include <iostream>
#include <string.h>
#include <sstream>
#include <C_circle.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc!=6)
    {
        std::cout << "command " << argv[0] << " x0<double> y0<double> z0<double> dt<double> nb iteration<unsigned long>" << std::endl;
        return -1;
    }
    C_circle myCircle;
    std::vector<Point> myCurve = myCircle.solveCircleEuler(atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]));
    myCircle.saveCurve("myCircle", myCurve);
    myCurve.clear();
    myCurve = myCircle.solveCircleRK4(atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]));
    myCircle.saveCurve("myCircleRK4", myCurve);

    return 25;
}
