#include<iostream>
#include<cmath>
#include<omp.h>

using fptr = double (double);

double f (double x);
double integral_serial (double a, double b, int N, fptr f);
double integralomp (double a, double b, int N, fptr f);


int main(){
  
  const int N = 1000000000;
  const double a = 0.0;
  const double b = 10.0;

  //for NTHREADS in 1 2 3 4 5 6 7 8; do export OMP_NUM_THREADS=$NTHREADS; ./a.out; done

  //std::cout << "#Integral serial: " << integral_serial(a,b,N,f) << std::endl;
  //  std::cout << "#Integral paralelo: " << integralomp(a,b,N,f) << std::endl;
  double t1 = omp_get_wtime();
  integralomp(a,b,N,f);
  double t2 = omp_get_wtime();

  #pragma omp parallel 
  {
    if(0 == omp_get_thread_num()){
      int nthreads = omp_get_num_threads();
      double time= t2-t1;
	std::cout << nthreads << "\t" << time << std::endl;
    }
  }
}

double f (double x ){
  return x*x;
}

double integral_serial (double a, double b, int N, fptr f){
  const double dx = (b-a)/N;

  double sum=0, x;

  for(int ii=0; ii < N; ++ii){
    x = a + ii*dx;
    sum += dx*f(x);
  }
  return sum;
}

double integralomp (double a, double b, int N, fptr f){
  const double dx = (b-a)/N;

  double sum=0, x;

#pragma omp parallel for reduction (+:sum) private (x)
  for(int ii=0; ii < N; ++ii){
    x = a + ii*dx;
    sum += dx*f(x);
  }
  return sum;
}
