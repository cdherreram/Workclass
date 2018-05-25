#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <algorithm>

const double W = 2.98768765; // omega in rad

void euler(double ta, double tb, double h, std::vector < double> & y);

double f(double t, const std::vector <double> & y, int id);

void rk4 (double ta, double tb, std::vector <double> & data, double h);


int main ( void )
{
  const double N = 2;
  const double TA = 0;
  const double TB = 16.4;
  const double H = 0.01;

  std::vector < double > y = {0.12,0}; // {x0,v0]

  //  euler ( TA, TB, H,y);
  rk4 ( TA, TB, y, H);

  return 0;
}

void euler(double ta, double tb, double h, std::vector < double> & y)
{
  const double N = (tb-ta)/h;
  std::vector <double> yaux(y.size());
  for (int nt = 0; nt < N; ++nt)
    {
      double t = ta + h*nt;
      std::copy(y.begin(), y.end(), yaux.begin());
      for(int id = 0; id < y.size(); ++id){
	y[id] = y[id] + h*f(t,yaux,id);
      }
      std::cout << t << "\t" << y[0] << "\t" << y[1] << std::endl;
    }
}

double f(double t, const std::vector <double> & y, int id){
  if ( 0== id){
    return y[1];
  } else if (1 == id){
    return -W*W*y[0] - 1.23*y[1];
  } else{
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
      std::cout << t << "\t" << data[0] << "\t" << data[1] << std::endl;
    }
}
