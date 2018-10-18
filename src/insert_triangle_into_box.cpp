#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  //Just find the lowest and highest value for each axis coordinate for all 3 points and expand B to fit them
  double min_coordinate, max_coordinate;
  for(int i = 0; i < 3; i = i + 1) {
    min_coordinate = a(i);
    max_coordinate = a(i);
    if(min_coordinate > b(i)) {
      min_coordinate = b(i);
    }
    if(min_coordinate > c(i)) {
      min_coordinate = c(i);
    }
    if(max_coordinate < b(i)) {
      max_coordinate = b(i);
    }
    if(max_coordinate < c(i)) {
      max_coordinate = c(i);
    }
    if(B.min_corner(i) > min_coordinate) {
      B.min_corner(i) = min_coordinate;
    }
    if(B.max_corner(i) < max_coordinate) {
      B.max_corner(i) = max_coordinate;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}


