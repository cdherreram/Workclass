#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

const double w = 3.1237;
const double dt = 0.01;
const double TF = 4*2*M_PI/w;
const int N = 2;

void initial_conditions(std::vector<double> & y);
void print (const double & time, const std::vector <double> & y);
double f (const double & time, const std::vector <double> & y, int idx);
void time_step (const double & time, std::vector <double> & y, double dt);

int main (void)
{
  std::vector <double> y (N);
  initial_conditions(y);

  double t = 0;
  int nsteps = (TF - 0.0)/dt;
  for (int ii = 0; ii < nsteps; ++ii){
      t = 00+ii*dt;
      time_step(t , y, dt);
      print (t,y);
  }
  return 0;
}

void initial_conditions(std::vector<double> & y)
{
  y[0] = 0.9876;
  y[1] = 0.0;
}

void print (const double & t, const std::vector <double> & y)
{
  std::cout << t << "\t \t \t" << y[0] << "\t\t\t" << y[1] << std::endl;
}

double f (const double & t, const std::vector <double> & y, int idx)
{
  if (0 == idx){
    return y[1];
  } else if (1 == idx){
    return -w*w*std::pow(y[0],3);
  } else {
    std::cerr << "Error: Index not allowed. \n";
    exit(1);
  }
}

void time_step (const double & t, std::vector <double> & y, double dt)
{
  std::vector <double> y1 = y;
  for(int ii = 0; ii < y1.size(); ii++){
    y[ii] += dt*f(t,y1,ii);
  }
}

      
    
