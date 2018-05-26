#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>

const double A0 = 20;
const double TAU = 5;
const double K = 0.12;

void rk4 (double ta, double tb, std::vector <double> & data, double h);
double f(double t, const std::vector <double> & y, int id);

int main (void)
{
  const double TA = 0;
  const double TB = 50.0;
  const double H = 0.01;
  std::vector < double> y = {0.0, 0.0,0.0,0.0}; // {A10 A20 B10 B20}

  rk4 (TA, TB, y, H);
  
  return 0;
}

double f(double t, const std::vector <double> & y, int id){
  if ( 0 == id){
    return (1/TAU)*(A0 -y[0])-K*y[0];
  } else if (1 == id){
    return (-1/TAU) *y[1]+K*y[0];
  } else if (2 == id){
    return (1/TAU)*(y[0]-y[2])-K*y[2];
  } else if (3 == id){
    return (1/TAU)*(y[1]-y[3])+K*y[2];
  } else {
    std::cerr << "Error!!! Id does not exist ->" << id << std::endl;
    exit(1);
  }
}

void rk4 (double ta, double tb, std::vector <double> & data, double h)
{
  std::vector < double > k1,k2,k3,k4, yaux;
  k1.resize(data.size());
  k2.resize(data.size());
  k3.resize(data.size());
  k4.resize(data.size());
  yaux.resize(data.size());

  const double N = (tb-ta)/h;
  std::ofstream ofs ("datos.txt", std::ofstream::out);
  for (int nt = 0; nt < N; ++nt)
    {
      double t = ta + h*nt;
      
      //k1
      for (int ii= 0; ii < data.size(); ++ii){
	k1[ii] = h*f(t, data, ii);
      }
      //k2 aux
      for (int ii = 0; ii < data.size(); ++ii){
	yaux[ii] = data[ii] + k1[ii]/2;
      }
      //k2
      for (int ii= 0; ii< data.size(); ++ii){
	k2[ii] = h*f( t+ h/2 , yaux, ii);
      }
      //k3 aux
      for (int ii = 0; ii < data.size(); ++ii){
	yaux[ii] = data[ii] + k2[ii]/2;
      }
      //k3
      for (int ii = 0; ii < data.size(); ++ii){
	k3[ii] = h*f( t+ h/2 , yaux, ii);
      }
      //k4 aux
      for (int ii = 0; ii < data.size(); ++ii){
	yaux[ii] = data[ii] + k3[ii];
      }
      //k4
      for (int ii = 0; ii < data.size(); ++ii){
	k4[ii] = h*f(t+h, yaux, ii);
      }
      
      //write new data
      for ( int ii =0; ii < data.size(); ++ii){
	data[ii] += (k1[ii] + 2*k2[ii] + 2*k3[ii] + k4[ii])/6.0;	
      }
     
      ofs << t << "\t\t" << data[0] << "\t\t" <<  data[1] << "\t\t" <<  data[2] << "\t\t" <<  data[3] << "\t\t" << std::endl;
    }
  ofs.close();
}
