#include <iostream>
#include <eigen3/Eigen/Dense>
#include <Eigen/Eigenvalues>

int main()
{
  Eigen::Matrix2d A;
  A << 1,2,2,3;
  std::cout << "The matrix is: " << A << std::endl;
  Eigen::SelfAdjointEigenSolver<Eigen::Matrix2d> eigensolver(A);
  if (eigensolver.info() != Eigen::Success) abort();
  Eigen::EigenSolver<Eigen::Matrix2d> es;
  Eigen::Vector2d x = Eigen::EigenSolver<Eigen::Matrix2d> es.eigensolver.eigenvalues();
  //x = eigensolver.eigenvalues(A);
  std::cout << "The eigenvalues are: \n" << eigensolver.eigenvalues() << std::endl;

  return 0;
}
