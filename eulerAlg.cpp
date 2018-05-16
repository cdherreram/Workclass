#include <iostream>
#include <Eigen/Dense>
#include <cmath>
#include <cstdlib>

const double w = 3.1237; //frecuency
const int N = 2; //Vector size
const double dt = 0.1;
const double final = 4*2*M_PI/w; //final time to finish proccess

void initial_conditions (Eigen::VectorXd & y);
void time_step(double t, Eigen::VectorXd & y, double dt);
void print (const double & time, Eigen::VectorXd & y);
double f (const double & t, const Eigen::VectorXd & y, int idx);

int main()
{
  double t = 0.0;
  Eigen::VectorXd y(N);

  initial_conditions (y);
  int nsteps = final/dt;
  
  for (int ii = 0; ii<nsteps; ii++){
    t += ii*dt;
    time_step(t , y , dt);
    print (t, y);
  }
  return 0;  
}

void initial_conditions (Eigen::VectorXd & y)
{
  y[0] = 0.9876;
  y[1] = 0.0;
}

void time_step(double t, Eigen::VectorXd & y, double dt)
{
  Eigen::VectorXd y1 = y;
  for(int ii = 0; ii<=1; ii++){
    y[ii] += dt*f(t,y1,ii);
  }
}
  
void print (const double & time, Eigen::VectorXd & y)
{
  std::cout << time << "\t" << y[0] << "\t" << y[1] << std::endl;
}

double f (const double & t, Eigen::VectorXd & y, int idx)
{
  if (0 == idx){
    return y[1];
  } else if (1 == idx){
    return -w*w*y[0];
  } else {
    std::cerr << "Error: Index not allowed. \n";
    exit(1);
  }
}
  
