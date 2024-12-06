#include "InternalNode.hpp"

InternalNode::InternalNode(int attribute_index) : attribute_index(attribute_index) {}

void
InternalNode::add_child(const string& attribute_value, shared_ptr<DecisionTree> subtree)
{
  children[attribute_value] = subtree;
}

string 
InternalNode::classify(const vector<string>& instance) const
{
  auto it = children.find(instance[attribute_index]);
  if (it != children.end())
    return it->second->classify(instance);
  return "unknown";
}

void
InternalNode::print(ostream& os, int depth) const
{
  for(const auto& [attribute_value, subtree] : children)
  {
    os << string(depth, ' ');
    os << "<" << attribute_name(attribute_index) << ":" << attribute_value << "> -> ";
    os << (dynamic_cast<InternalNode*>(subtree.get()) ? "\n" : "");
    subtree->print(os, depth+4);
  }
}
