#include "insert_box_into_box.h"

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  //Just expand the box B by changing the min corner of B if A has any coordinates lower in its min corner and same with max corner if it has any higher
  for(int i = 0; i < 3; i = i + 1) {
    if(A.min_corner(i) < B.min_corner(i)) {
      B.min_corner(i) = A.min_corner(i);
    }
    if(A.max_corner(i) > B.max_corner(i)) {
      B.max_corner(i) = A.max_corner(i);
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

