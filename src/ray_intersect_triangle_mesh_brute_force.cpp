#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  int counter = 0;
  double t_holder;
  //Holders for each point in triangle to help put into triangle intersect function
  Eigen::RowVector3d a_holder, b_holder, c_holder;
  for(int i = 0; i < F.rows(); i = i + 1) {
    a_holder = V.row(F(i, 0));
    b_holder = V.row(F(i, 1));
    c_holder = V.row(F(i, 2));
    if(ray_intersect_triangle(ray, a_holder, b_holder, c_holder, min_t, max_t, t_holder)) {
      if(counter == 0 || t_holder < hit_t) {
        hit_t = t_holder;
        hit_f = i;
      }
      counter = counter + 1;
    }
  }
  //If counter is at 0, that means no hits were found
  if(counter == 0) {
    return false;
  } else {
    return true;
  }
  ////////////////////////////////////////////////////////////////////////////
}
