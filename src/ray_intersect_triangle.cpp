#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  //Uses Cramer's rule to find t, beta and gamma (from textbook pg 79)
  double a = A(0) - B(0), b = A(1) - B(1), c = A(2) - B(2), d = A(0) - C(0), e = A(1) - C(1), f = A(2) - C(2), g = ray.direction(0), h = ray.direction(1), i = ray.direction(2), j = A(0) - ray.origin(0), k = A(1) - ray.origin(1), l = A(2) - ray.origin(2);
  double m_value = ((a * ((e * i) - (h * f))) + (b * ((g * f) - (d * i))) + (c * ((d * h) - (e * g))));
  t = -1 * (((f * ((a * k) - (j * b))) + (e * ((j * c) - (a * l))) + (d * ((b * l) - (k * c)))) / m_value);
  if(t < min_t || t > max_t) {
    return false;
  }
  double gamma = ((i * ((a * k) - (j * b))) + (h * ((j * c) - (a * l))) + (g * ((b * l) - (k * c)))) / m_value;
  if(gamma < 0 || gamma > 1) {
    return false;
  }
  double beta = ((j * ((e * i) - (h * f))) + (k * ((g * f) - (d * i))) + (l * ((d * h) - (e * g)))) / m_value;
  if(beta < 0 || beta > 1 - gamma) {
    return false;
  }
  return true;
  ////////////////////////////////////////////////////////////////////////////
}

