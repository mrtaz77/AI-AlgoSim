#include "TerminalNode.hpp"

TerminalNode::TerminalNode(const string& result) : result(result) {}

string
TerminalNode::classify(const vector<string>& instance) const
{
  return result;
}
