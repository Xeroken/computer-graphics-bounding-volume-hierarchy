#include "AABBTree.h"
#include "insert_box_into_box.h"
#include <iostream>

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  //First make the min and max corners of the box
  Eigen::RowVector3d min_corner, max_corner;
  for(int i = 0; i < 3; i = i + 1) {
    this->box.min_corner(i) = std::numeric_limits<double>::infinity();
    this->box.max_corner(i) = -std::numeric_limits<double>::infinity();
  }
  for(std::shared_ptr<Object> object: objects) {
    insert_box_into_box(object->box, this->box);
  }
  //Find the length of each side and take the longest
  int axis_id;
  if((max_corner(0) - min_corner(0)) >= (max_corner(1) - min_corner(1)) && ((max_corner(0) - min_corner(0)) >= (max_corner(2) - min_corner(2)))) {
    axis_id = 0;
  } else if((max_corner(1) - min_corner(1)) >= (max_corner(0) - min_corner(0)) && ((max_corner(1) - min_corner(1)) >= (max_corner(2) - min_corner(2)))) {
    axis_id = 1;
  } else {
    axis_id = 2;
  }
  //Split objects into two lists dependent on the longest side coordinate
  std::vector<std::shared_ptr<Object> > left_objects = {}, right_objects = {};
  Eigen::RowVector3d center = this->box.center();
  for(std::shared_ptr<Object> object: objects) {
    if(object->box.min_corner(axis_id) < center(axis_id) && object->box.max_corner(axis_id) > center(axis_id)) {
      if(left_objects.size() < right_objects.size()) {
	left_objects.push_back(object);
      } else {
	right_objects.push_back(object);
      }
    } else if(object->box.min_corner(axis_id) < center(axis_id)) {
      left_objects.push_back(object);
    } else {
      right_objects.push_back(object);
    }
  }
  if(left_objects.size() + right_objects.size() != num_leaves) {
    std::cout << "1" << "\n";
  }

  //Check list sizes to dictate whether or not pointers will be AABBTrees or Objects and rearrange for special conditions
  if(left_objects.size() == 0) {
    left_objects.push_back(right_objects[right_objects.size() - 1]);
    right_objects.pop_back();
    this->left = left_objects[0];
  } else if(left_objects.size() == 1) {
    this->left = left_objects[0];
  } else if(left_objects.size() == this->num_leaves) {
      right_objects.push_back(left_objects[left_objects.size() - 1]);
      left_objects.pop_back();
      if(left_objects.size() == 1) {
        this->left = left_objects[0];
      } else {
        this->left = std::make_shared<AABBTree>(left_objects, depth + 1);
      }
  } else {
    this->left = std::make_shared<AABBTree>(left_objects, depth + 1);
  }
  //The first and third case should not exist since it went through left first
  if(right_objects.size() == 1) {
    this->right = right_objects[0];
  } else {
    this->right = std::make_shared<AABBTree>(right_objects, depth + 1);
  }
  if(left_objects.size() + right_objects.size() != num_leaves) {
    std::cout << "2" << "\n";
  }
  ////////////////////////////////////////////////////////////////////////////
}

bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double left_t = min_t - 1, right_t = min_t - 1;
  std::shared_ptr<Object> left_descendant, right_descendant;
  if(ray_intersect_box(ray, this->box, min_t, max_t, t)) {
    if(this->left->ray_intersect(ray, min_t, max_t, t, left_descendant)) {
      if(!(left_descendant)) {
        left_descendant = this->left;
      }
      left_t = t;
    }
    if(this->right->ray_intersect(ray, min_t, max_t, t, right_descendant)) {
      if(!(right_descendant)) {
        right_descendant = this->right;
      }
      right_t = t;
    }
  }
  if(left_t != min_t - 1 && right_t != min_t - 1) {
    if(right_t > left_t) {
      t = left_t;
      descendant = left_descendant;
    } else {
      t = right_t;
      descendant = right_descendant;
    }
    return true;
  } else if(left_t != min_t - 1) {
    t = left_t;
    descendant = left_descendant;
    return true;
  } else if(right_t != min_t - 1) {
    t = right_t;
    descendant = right_descendant;
    return true;
  } else {
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}
