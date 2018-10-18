#include "point_triangle_squared_distance.h"
#include <Eigen/Geometry>
#include "ray_intersect_triangle.h"
#include <limits>
#include <cmath>

double point_triangle_squared_distance(
  const Eigen::RowVector3d & query,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  Eigen::RowVector3d & bary)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  //First find where the query point intersects the triangle plane (cribbed from A2)
  //Uses A as the point for the plane, calculates its normal and uses query for its questioning point and the same normal for its direction
  Eigen::RowVector3d normal = (B - A).cross(C - A), plane_point, plane_point_bary;
  double t = (((normal(0) - A(0)) * (A(0) - query(0))) + ((normal(1) - A(1)) * (A(1) - query(1))) + ((normal(2) - A(2)) * (A(2) - query(2)))) / ((normal(0) * (normal(0) - A(0))) + (normal(1) * (normal(1) - A(1))) + (normal(2) * (normal(2) - A(2))));
  plane_point = query + (t * normal);
  //Now we solve for the barycentric coordinates on the plane using systems solving
  //The results are from rearranging algebra using plane_point and the three points in a linear system (sorry about how bad this looks)
  double alpha = (plane_point(0) - ((plane_point(1) * B(0)) / (B(1) - (B(2) * C(1) / C(2)))) + ((plane_point(2) * C(1) * B(0)) / ((C(2) * B(1)) - (B(2) * C(1)))) - (plane_point(2) * C(0) / C(2)) + ((plane_point(1) * B(2) * C(0)) / ((C(2) * B(1)) - (B(2) * C(1)))) - ((plane_point(2) * C(1) * B(2) * C(0)) / ((C(2) * C(2) * B(1)) - (C(2) * B(2) * C(1))))) / (A(0) - ((A(1) * B(0)) / (B(1) - (B(2) * C(1) / C(2)))) + ((A(2) * C(1) * B(0)) / ((C(2) * B(1)) - (B(2) * C(1)))) - (A(2) * C(0) / C(2)) + (A(1) * B(2) * C(0) / ((C(2) * B(1)) - (B(2) * C(1)))) - (A(2) * C(1) * B(2) * C(0) / ((C(2) * C(2) * B(1)) - (C(2) * B(2) * C(1)))));
  double beta = (plane_point(1) - (alpha * A(1)) + (alpha * A(2) * C(1) / C(2)) - (plane_point(2) * C(1) / C(2))) / (B(1) - (B(2) * C(1) / C(2)));
  double gamma = (plane_point(2) - (alpha * A(2)) - (beta * B(2))) / C(2);
  //Now check each value to determine special cases
  int counter = 0;
  if(alpha < 0) {
    counter = counter + 1;
  }
  if(beta < 0) {
    counter = counter + 1;
  }
  if(gamma < 0) {
    counter = counter + 1;
  }
  //If all are positive, it landed within the triangle
  if(counter == 0) {
    bary(0) = alpha;
    bary(1) = beta;
    bary(2) = gamma;
    return pow(plane_point(0) - query(0), 2) + pow(plane_point(1) - query(1), 2) + pow(plane_point(2) - query(2), 2);
  } else if(counter == 1) {
    //If it has one negative value, then that means a vector perpendicular to the edge formed by the two non-negative barycentric vertices would be the shortest distance from the point on the plane
    //The normal from that edge can be formed by the vector from the center of the triangle to the midpoint of the edge
    Eigen::RowVector3d center = (A / 3) + (B / 3) + (C / 3), midpoint, edge_normal, contact_point;
    if(alpha < 0) {
      midpoint = (B + C) / 2;
    } else if(beta < 0) {
      midpoint = (A + C) / 2;
    } else {
      midpoint = (A + B) / 2;
    }
    edge_normal = midpoint - center;
    //Now use ray_intersect_triangle with that plane point as an origin with edge_normal to find the lowest absolute t value from there (should always return true)
    Ray plane_ray(plane_point, edge_normal);
    double t_holder;
    ray_intersect_triangle(plane_ray, A, B, C, -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(), t_holder);
    contact_point = plane_point + (t_holder * edge_normal);
    //Then use the same way as calculating alpha, beta and gamma to get the barycentric coordinates of the resulting point (sorry you had to see these ugly calculations again)
    bary(0) = (contact_point(0) - ((contact_point(1) * B(0)) / (B(1) - (B(2) * C(1) / C(2)))) + ((contact_point(2) * C(1) * B(0)) / ((C(2) * B(1)) - (B(2) * C(1)))) - (contact_point(2) * C(0) / C(2)) + ((contact_point(1) * B(2) * C(0)) / ((C(2) * B(1)) - (B(2) * C(1)))) - ((contact_point(2) * C(1) * B(2) * C(0)) / ((C(2) * C(2) * B(1)) - (C(2) * B(2) * C(1))))) / (A(0) - ((A(1) * B(0)) / (B(1) - (B(2) * C(1) / C(2)))) + ((A(2) * C(1) * B(0)) / ((C(2) * B(1)) - (B(2) * C(1)))) - (A(2) * C(0) / C(2)) + (A(1) * B(2) * C(0) / ((C(2) * B(1)) - (B(2) * C(1)))) - (A(2) * C(1) * B(2) * C(0) / ((C(2) * C(2) * B(1)) - (C(2) * B(2) * C(1)))));
    bary(1) = (contact_point(1) - (bary(0) * A(1)) + (bary(0) * A(2) * C(1) / C(2)) - (contact_point(2) * C(1) / C(2))) / (B(1) - (B(2) * C(1) / C(2)));
    bary(2) = (contact_point(2) - (bary(0) * A(2)) - (bary(1) * B(2))) / C(2);
    //Then return the distance between contact_point and query
    return pow(contact_point(0) - query(0), 2) + pow(contact_point(1) - query(1), 2) + pow(contact_point(2) - query(2), 2);
  } else {
    //If anything else, the closest point is one of the vertices
    double current_min, sqrd_holder;
    current_min = pow(A(0) - query(0), 2) + pow(A(1) - query(1), 2) + pow(A(2) - query(2), 2);
    bary(0) = 1;
    bary(1) = 0;
    bary(2) = 0;
    sqrd_holder = pow(B(0) - query(0), 2) + pow(B(1) - query(1), 2) + pow(B(2) - query(2), 2);
    if(sqrd_holder < current_min) {
      current_min = sqrd_holder;
      bary(0) = 0;
      bary(1) = 1;
      bary(2) = 0;
    }
    sqrd_holder = pow(C(0) - query(0), 2) + pow(C(1) - query(1), 2) + pow(C(2) - query(2), 2);
    if(sqrd_holder < current_min) {
      current_min = sqrd_holder;
      bary(0) = 0;
      bary(1) = 0;
      bary(2) = 1;
    }
    return current_min;
  }
  ////////////////////////////////////////////////////////////////////////////
}
