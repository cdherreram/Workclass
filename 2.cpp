#include <iostream>
#include <eigen3/Eigen/Dense>

const double A0 = 20;
const double TAU = 5;
const double K = 0.12;

void initMatrixVector (double t, double k, double init, Eigen::MatrixXd& A, Eigen::VectorXd& b);
void solveSystem (Eigen::MatrixXd A, Eigen::VectorXd b );

int main()
{
  Eigen::MatrixXd A(4,4);
  Eigen::VectorXd b(4);
  initMatrixVector(TAU, K, A0, A, b);

  std::cout << " A = " << std::endl << A << std::endl;
  std::cout << "b = " << std::endl << b << std::endl;

  solveSystem (A, b);
  
}

void initMatrixVector (double t, double k, double init, Eigen::MatrixXd& A, Eigen::VectorXd& b)
{
  A << (-1/t)-k,0,0,0,k,-(1/t),0,0,1/t,0,(-1/t)-k,0,0,1/t,k,-1/t;
  b << init/t,0,0,0;
}
void solveSystem (Eigen::MatrixXd A, Eigen::VectorXd b )
{  
   Eigen::ColPivHouseholderQR<Eigen::Matrix4d> dec(A);
   Eigen::VectorXd x = dec.solve(-b);
  
  std::cout << "Solucion \n " << x << std::endl;
  std::cout << "la comprobacion es \n"<< (A*x+b).norm() << std::endl;
}
