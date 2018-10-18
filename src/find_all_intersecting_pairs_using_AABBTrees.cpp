#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  //Initialize type checker and queue for checking pairs
  std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object> > > pair_queue;
  std::shared_ptr<AABBTree> type_checker_one, type_checker_two;
  std::pair<std::shared_ptr<Object>, std::shared_ptr<Object> > current_pair;
  pair_queue.push_back(std::make_pair(rootA, rootB));
  //Check the type of each pair
  while(!(pair_queue.empty())) {
    current_pair = std::make_pair(pair_queue.front().first, pair_queue.front().second);
    pair_queue.pop_front();
    type_checker_one = std::dynamic_pointer_cast<AABBTree>(current_pair.first);
    type_checker_two = std::dynamic_pointer_cast<AABBTree>(current_pair.second);
    if(!(type_checker_one) && !(type_checker_two)) {
      //If both are leaves, add it to the vector (intersection check occurs in other cases)
      leaf_pairs.push_back(std::make_pair(current_pair.first, current_pair.second));
    } else if(!(type_checker_one)) {
      //If only one is a leaf, check if the leaf intersects with any child of the tree and append it to the queue
      if(box_box_intersect(current_pair.first->box, type_checker_two->left->box)) {
	pair_queue.push_back(std::make_pair(current_pair.first, type_checker_two->left));
      }
      if(box_box_intersect(current_pair.first->box, type_checker_two->right->box)) {
        pair_queue.push_back(std::make_pair(current_pair.first, type_checker_two->right));
      }
    } else if(!(type_checker_two)) {
      if(box_box_intersect(current_pair.second->box, type_checker_one->left->box)) {
        pair_queue.push_back(std::make_pair(type_checker_one->left, current_pair.second));
      }
      if(box_box_intersect(current_pair.first->box, type_checker_two->left->box)) {
        pair_queue.push_back(std::make_pair(type_checker_one->right, current_pair.second));
      }
    } else {
      //For last case, check if any children intersect and add them to the queue if they do
      if(box_box_intersect(type_checker_one->left->box, type_checker_two->left->box)) {
        pair_queue.push_back(std::make_pair(type_checker_one->left, type_checker_two->left));
      }
      if(box_box_intersect(type_checker_one->left->box, type_checker_two->right->box)) {
        pair_queue.push_back(std::make_pair(type_checker_one->left, type_checker_two->right));
      }
      if(box_box_intersect(type_checker_one->right->box, type_checker_two->left->box)) {
        pair_queue.push_back(std::make_pair(type_checker_one->right, type_checker_two->left));
      }
      if(box_box_intersect(type_checker_one->right->box, type_checker_two->right->box)) {
        pair_queue.push_back(std::make_pair(type_checker_one->right, type_checker_two->right));
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
