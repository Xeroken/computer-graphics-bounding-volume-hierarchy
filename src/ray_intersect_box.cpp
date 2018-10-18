#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  //Minimum t value for each axis
  double t_min_x = (box.min_corner(0) - ray.origin(0)) / ray.direction(0), t_min_y = (box.min_corner(1) - ray.origin(1)) / ray.direction(1), t_min_z = (box.min_corner(2) - ray.origin(2)) / ray.direction(2);
  //Maximum t value for each axis
  double t_max_x = (box.max_corner(0) - ray.origin(0)) / ray.direction(0), t_max_y = (box.max_corner(1) - ray.origin(1)) / ray.direction(1), t_max_z = (box.max_corner(2) - ray.origin(2)) / ray.direction(2);
  //Record which value is higher or lower for each axis
  Eigen::RowVector3d min_dist, max_dist;
  if(t_max_x > t_min_x) {
    min_dist(0) = t_min_x;
    max_dist(0) = t_max_x;
  } else {
    min_dist(0) = t_max_x;
    max_dist(0) = t_min_x;
  }
  if(t_max_y > t_min_y) {
    min_dist(1) = t_min_y;
    max_dist(1) = t_max_y;
  } else {
    min_dist(1) = t_max_y;
    max_dist(1) = t_min_y;
  }
  if(t_max_z > t_min_z) {
    min_dist(2) = t_min_z;
    max_dist(2) = t_max_z;
  } else {
    min_dist(2) = t_max_z;
    max_dist(2) = t_min_z;
  }
  //To find the minimum t, make sure it hits the box (at least one value for t in an axis is in range for other 2) and take the largest min_t and lowest max_t
  if((min_dist(0) > max_dist(1) || min_dist(0) > max_dist(2)) || (min_dist(1) > max_dist(0) || min_dist(1) > max_dist(2)) || (min_dist(2) > max_dist(0) || min_dist(2) > max_dist(1))) {
    return false;
  }
  double highest_min = min_dist(0), lowest_max = max_dist(0);
  if(highest_min < min_dist(1)) {
    highest_min = min_dist(1);
  }
  if(highest_min < min_dist(2)) {
    highest_min = min_dist(2);
  }
  if(lowest_max > max_dist(1)) {
    lowest_max = max_dist(1);
  }
  if(lowest_max > max_dist(2)) {
    lowest_max = max_dist(2);
  }
  if(highest_min > max_t || lowest_max < min_t) {
    return false;
  } else if(highest_min < min_t) {
    t = min_t;
  } else {
    t = highest_min;
  }
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
