#include <iostream>
#include <cmath>

int main ( int argc, char *argv[ ]){
  const int N = 100000000;
  int i = 0;
  double *a;
  a = new double [N];
  double suma = 0;

#pragma omp parallel for reduction(+:suma)// se puede adicionar num_threads(4) para elegir el numero de nucleos
  for (i = 0; i< N; i++){
    a[i] = 2*std::sin(i/32.6)*std::cos(i/32.6);
    suma += a[i];
  }

  std::cout << suma << std::endl;
  delete [] a;
  return 0;
}
