#include<iostream>
#include<cstdio>
#include<math.h>

int main() {

  int min = 500;
  int max = 1400;      
  long int contador = 0;
  long int suma = 0;
    
  for (min; min<=max;++min) {
    for(int j=1; j<=sqrt(min) && contador <=1 ;j++){
      if((min%j)== 0){
	contador = contador+1;
      }
    }
    
    if(contador==1 & min!=1){
      std::cout << min << "\n";
    }
    contador = 0;
  }

  return 0;
}
