#include "point_box_squared_distance.h"
#include <cmath>

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  //If a coordinate is in range of a box coordinate, set the difference to 0 to minimize distance since it does not have to move along that axis
  double result;
  Eigen::RowVector3d differences;
  for(int i = 0; i < 3; i = i + 1) {
    if(query(i) >= box.min_corner(i) && query(i) <= box.max_corner(i)) {
      differences(i) = 0;
    } else if(query(i) < box.min_corner(i)) {
      differences(i) = box.min_corner(i) - query(i);
    } else {
      differences(i) = query(i) - box.max_corner(i);
    }
  }
  result = pow(differences(0), 2) + pow(differences(1), 2) + pow(differences(2), 2);
  return result;
  ////////////////////////////////////////////////////////////////////////////
}
