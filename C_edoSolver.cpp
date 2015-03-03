#include <C_edoSolver.h>

C_edoSolver::C_edoSolver()
{
    //ctor
}

C_edoSolver::~C_edoSolver()
{
    //dtor
}




//double* C_streamline::F(double x, double y, double z, double t) ///dr(x,y,z,t)/dt = F(x,y,z,t)
//{
//    double* v = new double[3];
//    v[0] = 0.0;
//    v[1] = 0.0;
//    v[2] = 0.0;
//    return v;
//}

double* C_edoSolver::EULERstep(double x, double y, double z, double t, double dt)
{
    double* dr = F(x,y,z,t);
    dr[0] = dt*dr[0];
    dr[1] = dt*dr[1];
    dr[2] = dt*dr[2];
    return dr;
}
double* C_edoSolver::RK4step(double x, double y, double z, double t, double dt)
{
    double* K1 = RK4K1(x, y, z, t, dt);
    double* K2 = RK4K2(x, y, z, K1[0], K1[1], K1[2], t, dt);
    double* K3 = RK4K3(x, y, z, K2[0], K2[1], K2[2], t, dt);
    double* K4 = RK4K4(x, y, z, K3[0], K3[1], K3[2], t, dt);
    double* dr = new double[3];
    dr[0] = (1.0/6.0)*(K1[0] + 2.0*K2[0] + 2*K3[0] + K4[0]);
    dr[1] = (1.0/6.0)*(K1[1] + 2.0*K2[1] + 2*K3[1] + K4[1]);
    dr[2] = (1.0/6.0)*(K1[2] + 2.0*K2[2] + 2*K3[2] + K4[2]);
    delete K1;
    delete K2;
    delete K3;
    delete K4;
    return dr;
}
double* C_edoSolver::RK4K1(double x, double y, double z, double t, double dt)
{
    double* K1 = F(x,y,z,t);
    K1[0] *= dt;
    K1[1] *= dt;
    K1[2] *= dt;
    return K1;
}
double* C_edoSolver::RK4K2(double x, double y, double z, double k1x, double k1y, double k1z, double t, double dt)
{
    double* K2 = F(x+0.5*k1x,y+0.5*k1y,z+0.5*k1z,t+0.5*dt);
    K2[0] *= dt;
    K2[1] *= dt;
    K2[2] *= dt;
    return K2;
}
double* C_edoSolver::RK4K3(double x, double y, double z, double k2x, double k2y, double k2z, double t, double dt)
{
    double* K3 = F(x+0.5*k2x,y+0.5*k2y,z+0.5*k2z,t+0.5*dt);
    K3[0] *= dt;
    K3[1] *= dt;
    K3[2] *= dt;
    return K3;
}
double* C_edoSolver::RK4K4(double x, double y, double z, double k3x, double k3y, double k3z, double t, double dt)
{
    double* K4 = F(x+k3x,y+k3y,z+k3z,t+dt);
    K4[0] *= dt;
    K4[1] *= dt;
    K4[2] *= dt;
    return K4;
}



bool C_edoSolver::saveCurve(std::string fileNameCurve, std::vector<Point> curve)
{
    //file names
    std::string sourceFile = fileNameCurve;

    //filestreams
    std::fstream filestrSRC;
    filestrSRC.open (sourceFile.data(), std::ofstream::out);
    if(filestrSRC.is_open()!=true) return false;

    //fill in the allocated bundle
    for(unsigned long r=0 ; r<curve.size() ; r++)
    {
        //fill fibers
        filestrSRC << curve.at(r).x << " " << curve.at(r).y << " " << curve.at(r).z << std::endl;
    }

    //close files
    filestrSRC.close();


    return true;
}

bool C_edoSolver::saveCurves(std::string fileNameCurve, std::vector< std::vector<Point> > curve)
{
    //file names
    std::string headerFile = fileNameCurve + ".fibHDR";
    std::string sourceFile = fileNameCurve + ".fibSRC";

    //filestreams
    std::fstream filestrSRC, filestrHDR;
    filestrHDR.open (headerFile.data(), std::ofstream::binary | std::ofstream::out); //should check if ok
    filestrSRC.open (sourceFile.data(), std::ofstream::binary | std::ofstream::out); //should check if ok

    //get number of bundles
    unsigned long NB = curve.size();
    filestrHDR.write((char*) &NB, sizeof(unsigned long)); //write it in header file

    //declare a buffer to store and write
    Point* b_curve;

    unsigned long maxN;
    //for each bundle
    for(unsigned long u=0 ; u<NB ; u++)
    {
        //get the size of the current bundle and save it in header file
        maxN = curve.at(u).size();
        filestrHDR.write((char*) &maxN, sizeof(unsigned long));

        //allocate bundle
        b_curve = new Point[maxN]; //should check if allocation doesn't fail

        //fill in the allocated bundle
        for(unsigned long r=0 ; r<maxN ; r++)
        {
            //fill fibers
            b_curve[r].x = curve.at(u).at(r).x;
            b_curve[r].y = curve.at(u).at(r).y;
            b_curve[r].z = curve.at(u).at(r).z;
        }

        //write data in source file
        filestrSRC.write((char*) b_curve, maxN*sizeof(Point));
        delete b_curve;
    }

    //close files
    filestrSRC.close();
    filestrHDR.close();


    return true;
}
