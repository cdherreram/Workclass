#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

const double dx = 0.01;
const double dt = 0.00013;
const double Tf = 3;
const double l = 1;
const double P0 = 0.01;
const double T0 = 40;
const double alpha = 0.5;


void stepfunction (std::vector <double> &past, std::vector <double> &present, std::vector <double> &future );
void init (std::vector  <double> & past, std::vector  <double> & present, double T, double D, double a);
void f( std::vector  <double> & past, std::vector  <double> & present, std::vector  <double> & future, double T, double D, double a);

int main ( void )
{
  int N = l/dx;
  std::vector <double> past(N);
  std::vector <double> present(N);
  std::vector <double> future(N);

  init(past,present,T0,P0,alpha);
  f (past,present, future,T0, P0,alpha);
  
  return 0;
}

void stepfunction (std::vector <double> &past, std::vector <double> &present, std::vector <double> &future ){
  for (int i = 0; i < past.size() ; i++){
    past[i] = present[i];
    present[i] = future[i];
  }
}

void init (std::vector  <double> & past, std::vector  <double> & present, double T, double D, double a){
  for (int i = 0; i < past.size(); i++){
    double x = i*dx;
    if ( x <= 0.5*l){
      past[i] =  x/l;
    } else {
      past[i] = - (x/l);
    }
  }
  
  for (int i= 1; i < present.size(); i++){
    present [0] = 0;
    present[i] = past[i]+pow(dt/dx,2)*(T/(2*D))*(past[i+1]+past[i-1]-2*past[i])+(1/2)*(a*dt*dt*T/(D*dx))*(past[i+1]-past[i]);
  }
}

void f( std::vector  <double> & past, std::vector  <double> & present, std::vector  <double> & future, double T, double D, double a){
  int M = Tf/dt;
  
  for(int j = 0; j < M-1; j++) //tiempo
    {
      for ( int k = 0; k <= present.size(); k++)
	{
	  std::cout <<j*dt << "\t\t" <<  k*dx << "\t\t" << present[k] << std::endl;    
	}
      
      /*if ( j == 1){
	std::ofstream var1 ("var1.txt", std::ofstream::out);
	for ( int k = 0; k <= present.size(); k++)
	  {
	    var1 << k*dx << "\t" << present[k] << std::endl;    
	  }
	var1.close();
      } else if ( j == 50000){
	std::ofstream var6 ("var6.txt", std::ofstream::out);
	for ( int k = 0; k <= present.size(); k++)
	  {
	    var6 << k*dx << "\t" << present[k] << std::endl;    
	  }
	var6.close();
      } else if (j == 100000){
	std::ofstream var11 ("var11.txt", std::ofstream::out);
	for ( int k = 0; k <= present.size(); k++)
	  {
	    var11 << k*dx << "\t" << present[k] << std::endl;    
	  }
	var11.close();
      } else if (j == 120000){
	std::ofstream var16 ("var16.txt", std::ofstream::out);
	for ( int k = 0; k <= present.size(); k++)
	  {
	    var16 << k*dx << "\t" << present[k] << std::endl;    
	  }
	var16.close();
	}*/
      
      for( int i = 1; i < past.size() ; i++) //espacio
	{
	  future[i] = 2*present[i]-past[i]+(a*dt*dt*T/(D*dx))*(present[i+1]-present[i])+pow(dt/dx,2)*(T/D)*(present[i+1]+present[i-1]-2*present[i]);
	}
      stepfunction( past, present, future);
    }
}
