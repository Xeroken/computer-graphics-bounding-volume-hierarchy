#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include <functional>
#include <utility>
#include <limits>
#include "point_box_squared_distance.h"

//Helper comparison function for priority queue
class Compare
{
public:
    bool operator()
    (
      const std::pair<double, std::shared_ptr<Object> > pair_one,
      const std::pair<double, std::shared_ptr<Object> > pair_two)
    {
      //Since priority queue uses less than to put it in decreasing order, should use greater than symbol to put it in ascending order
      return pair_one.first > pair_two.first;
    }
};

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    Eigen::RowVector3d & projection,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  //Initialize queues and type checker
  sqrd = std::numeric_limits<double>::infinity();
  std::priority_queue<std::pair<double, std::shared_ptr<Object> >, std::vector<std::pair<double, std::shared_ptr<Object> > >, Compare> node_queue;
  std::shared_ptr<AABBTree> type_checker;
  double current_sqrd, other_sqrd;
  Eigen::RowVector3d dummy_projection;
  std::shared_ptr<Object> dummy_descendant;
  std::pair<double, std::shared_ptr<Object> > current_element;
  node_queue.push(std::make_pair(point_box_squared_distance(query, root->box), root));
  //Now go through all nodes using the priority queue and if it finds a leaf, calculate its squared distance and record it if it is the current lowest in distance
  while(!(node_queue.empty())) {
    current_element = std::make_pair(node_queue.top().first, node_queue.top().second);
    node_queue.pop();
    current_sqrd = point_box_squared_distance(query, current_element.second->box);
    if(current_sqrd < sqrd) {
      type_checker = std::dynamic_pointer_cast<AABBTree>(current_element.second);
      if(!(type_checker)) {
        current_element.second->point_squared_distance(query, min_sqrd, max_sqrd, other_sqrd, dummy_projection, dummy_descendant);
        if(other_sqrd < sqrd) {
	  sqrd = other_sqrd;
	  projection = dummy_projection;
          descendant = current_element.second;
        }
      } else {
        other_sqrd = point_box_squared_distance(query, type_checker->left->box);
	node_queue.push(std::make_pair(other_sqrd, type_checker->left));
	other_sqrd = point_box_squared_distance(query, type_checker->right->box);
        node_queue.push(std::make_pair(other_sqrd, type_checker->right));
      }
    }
  }
  if(sqrd == std::numeric_limits<double>::infinity()) {
    return false;
  }
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
