#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  //Just check both at least one box has a min or max coordinate in range of the other for each coordinate
  int counter = 0;
  for(int i = 0; i < 3; i = i + 1) {
    if((A.min_corner(i) >= B.min_corner(i) && A.min_corner(i) <= B.max_corner(i)) || (B.min_corner(i) >= A.min_corner(i) && B.min_corner(i) <= A.max_corner(i))) {
      counter = counter + 1;
    }
  }
  if(counter == 3) {
    return true;
  } else {
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}

