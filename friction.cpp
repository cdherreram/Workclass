#include <iostream>
#include <cmath>
#include <vector>

const double dx = 0.01;
const double dt = 0.00013;
const double Tf = 5;
const double l = 2;
const double density = 0.01;
const double tension = 40;
const double viscosity = -10;

void stepfunction (std::vector <double> &past, std::vector <double> &present, std::vector <double> &future );
void init (std::vector  <double> & past, std::vector  <double> & present, double c1, double c2, double kf);
void f( std::vector  <double> & past, std::vector  <double> & present, std::vector  <double> & future, double c1, double c2, double kf);

int main ( void )
{
  int N = l/dx;
  std::vector <double> past(N);
  std::vector <double> present(N);
  std::vector <double> future(N);

  init(past,present,sqrt(tension/density), dx/dt, viscosity);
  f (past,present, future, sqrt(tension/density), dx/dt, viscosity);
  
  return 0;
}

void stepfunction (std::vector <double> &past, std::vector <double> &present, std::vector <double> &future ){
  for (int i = 0; i < past.size() ; i++){
    past[i] = present[i];
    present[i] = future[i];
  }
}

void init (std::vector  <double> & past, std::vector  <double> & present, double c1, double c2, double kf){
  for (int i = 0; i < past.size(); i++){
    double x = i*dx;
    if ( x <= 0.8*l){
      past[i] = (1.25 * x)/l;
    } else {
      past[i] = 5.0*(1 - (x/l));
    }
  }
  
  for (int i= 1; i < present.size(); i++){
    present [0] = 0;
    present[i] = (past[i]+(1/2)*(pow(c1,2)/pow(c2,2))*(past[i+1]+past[i-1]-2*past[i])-(kf*dt*past[i]))/(1-kf*dt);
  }
}

void f( std::vector  <double> & past, std::vector  <double> & present, std::vector  <double> & future, double c1, double c2, double kf){
  int M = Tf/dt;
  
  for(int j = 0; j < M-1; j+=20) //tiempo
    {
      for ( int k = 0; k <= present.size(); k++)
	{
	  std::cout << j*dt << "\t" << k*dx << "\t" << present[k] << std::endl; 
	}
      for( int i = 1; i < past.size() ; i++) //espacio
	{
	  future[i] = 2*present[i]-past[i]+((pow(c1,2)/pow(c2,2))*(present[i+1]+present[i-1]-2*present[i]))-2*kf*dt*(present[i]-past[i]);
	}
      stepfunction( past, present, future);
    }
}
