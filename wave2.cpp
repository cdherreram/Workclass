#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdlib>

const double dx = 0.005;
const double dt = 0.00006;
const double Tf = 0.8;
const double l = 1;
const double density = 0.01;
const double tension = 40;

void stepfunction (std::vector <double> &past, std::vector <double> &present, std::vector <double> &future );
void init (std::vector  <double> & past, std::vector  <double> & present, double c1, double c2);
void f( std::vector  <double> & past, std::vector  <double> & present, std::vector  <double> & future, double c1, double c2);

int main ( void )
{
  int N = l/dx;
  std::vector <double> past(N);
  std::vector <double> present(N);
  std::vector <double> future(N);

  init(past,present,sqrt(tension/density), dx/dt);
  f (past,present, future, sqrt(tension/density), dx/dt);
  
  return 0;
}

void stepfunction (std::vector <double> &past, std::vector <double> &present, std::vector <double> &future ){
  for (int i = 0; i < past.size() ; i++){
    past[i] = present[i];
    present[i] = future[i];
  }
}

void init (std::vector  <double> & past, std::vector  <double> & present, double c1, double c2){
  std::ofstream ofs ("inicial.txt", std::ofstream::out);
  for (int i = 0; i < past.size(); i++){
    double x = i*dx;
    if ((0.0 <= x) && (x <= 0.1*l)){
      past[i] = 0;
    } else if ((0.1*l < x) && (x<= 0.2*l)){
      past[i] = ((10*x)-1)*0.005;
    } else if ((0.2*l < x) && (x <= 0.3*l)){
      past[i] = ((-10*x)+3)*0.005;
    } else if ((0.3*l < x) && (x <= 0.7*l)){
      past[i] = 0;
    } else if ((0.7*l < x) && (x <= 0.8*l)){
      past[i] = ((10*x)-7)*0.005;
    } else if ((0.8*l < x) && (x <= 0.9*l)){
      past[i] = ((-10*x)+9)*0.005;
    } else if ((0.9*l < x) && (x <= 1.0*l)){
      past[i] = 0;
    }
  }
  
  for (int i= 1; i < present.size(); i++){
    present [0] = 0;
    present[i] = past[i]+(1/2)*(pow(c1,2)/pow(c2,2))*(past[i+1]+past[i-1]-2*past[i]);
    ofs << i*dx << "\t\t" << present[i] << std::endl;
  }
  ofs.close();
  
}

void f( std::vector  <double> & past, std::vector  <double> & present, std::vector  <double> & future, double c1, double c2){
  int M = Tf/dt;
  
  for(int j = 0; j < M-1; j+=40) //tiempo
    {
      for ( int k = 0; k <= present.size(); k++)
	{
	  std::cout << j*dt << "\t" << k*dx << "\t" << present[k] << std::endl; 
	}
      for( int i = 1; i < past.size() ; i++) //espacio
	{
	  future[i] = 2*present[i]-past[i]+((pow(c1,2)/pow(c2,2))*(present[i+1]+present[i-1]-2*present[i]));
	}
      stepfunction( past, present, future);
    }
}
