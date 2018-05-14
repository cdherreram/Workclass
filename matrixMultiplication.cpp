#include <iostream>
#include <eigen3/Eigen/Dense>

int main()
{
  Eigen::MatrixXd m = Eigen::MatrixXd::Constant (3,3,1);
  std::cout << "m = " << std::endl << m << std::endl;
  m = (m+ Eigen::MatrixXd::Random(3,3)*3);
  std::cout << "m= " << std::endl << m << std::endl;
  Eigen::VectorXd v = Eigen::VectorXd::Constant (3,2);
  Eigen::VectorXd u(3);
  u << 2,3,1;
  std::cout << "u = " << std::endl << u << std::endl;
 
  u = u+v;
  std::cout << "u = " << std::endl << u << std::endl;
  std::cout << "v = " << std::endl << v << std::endl;
  
  std::cout << "m*v= " << std::endl << m*v << std::endl;
}
