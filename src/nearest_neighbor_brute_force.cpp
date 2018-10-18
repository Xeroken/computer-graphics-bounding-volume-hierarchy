#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();
#include <cmath>

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  //Should compare distances between query and all points and record the lowest
  sqrD = std::numeric_limits<double>::infinity();
  double distance_holder;
  for(int j = 0; j < points.rows(); j = j + 1) {
    distance_holder = pow(points.row(j)(0) - query(0), 2) + pow(points.row(j)(1) - query(1), 2) + pow(points.row(j)(2) - query(2), 2);
    if(sqrD > distance_holder) {
      I = j;
      sqrD = distance_holder;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
