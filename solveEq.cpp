#include <iostream>
#include <eigen3/Eigen/Dense>

int main()
{
  Eigen::Matrix3d A;
  Eigen::VectorXd b(3);
  A << 1,2,3,4,5,6,7,8,10;
  b << 3,3,4;
  std::cout << " A = " << std::endl << A << std::endl;
  std::cout << "b = " << std::endl << b << std::endl;

  Eigen::Vector3d x;

  Eigen::ColPivHouseholderQR<Eigen::Matrix3d> dec(A);
  x = dec.solve(b);

  std::cout << "Solucion \n " << x << std::endl;
  std::cout << "la comprobacion es \n"<< (A*x-b).norm() << std::endl;

  float l1 = x(0);
  float l2 = x(1);
  float l3 = x(2);
  std::cout << "los valores de x son: " << l1 << ", " << l2 << ", " << l3 << std::endl;
  
}
  
