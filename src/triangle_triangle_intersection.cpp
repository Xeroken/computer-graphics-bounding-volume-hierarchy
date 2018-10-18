#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"
#include "Ray.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  //Strategy is to create a ray using one point as an orgin and a vector from it to another point and check if it intersects the other triangle with t between 0 and 1 for both triangles
  Ray ray(A0, A1 - A0);
  double dummy_t;
  if(ray_intersect_triangle(ray, B0, B1, B2, 0, 1, dummy_t)) {
    return true;
  }
  ray.origin = A1;
  ray.direction = A2 - A1;
  if(ray_intersect_triangle(ray, B0, B1, B2, 0, 1, dummy_t)) {
    return true;
  }
  ray.origin = A2;
  ray.direction = A0 - A2;
  if(ray_intersect_triangle(ray, B0, B1, B2, 0, 1, dummy_t)) {
    return true;
  }
  ray.origin = B0;
  ray.direction = B1 - B0;
  if(ray_intersect_triangle(ray, A0, A1, A2, 0, 1, dummy_t)) {
    return true;
  }
  ray.origin = B1;
  ray.direction = B2 - B1;
  if(ray_intersect_triangle(ray, A0, A1, A2, 0, 1, dummy_t)) {
    return true;
  }
  ray.origin = B2;
  ray.direction = B0 - B2;
  if(ray_intersect_triangle(ray, A0, A1, A2, 0, 1, dummy_t)) {
    return true;
  }
  //If it reaches here, then none of the 6 edges pass through the triangle
  return false; 
  ////////////////////////////////////////////////////////////////////////////
}
