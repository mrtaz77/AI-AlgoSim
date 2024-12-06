#include "TerminalNode.hpp"

TerminalNode::TerminalNode(const string& result) : result(result) {}

string
TerminalNode::classify(const vector<string>& /*instance*/) const
{
  return result;
}

void
TerminalNode::print(ostream &os, int /*depth*/) const
{
  os << result << endl;
}
