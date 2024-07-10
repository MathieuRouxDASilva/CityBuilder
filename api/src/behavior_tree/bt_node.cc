#include "behavior_tree/bt_node.h"

using namespace behavior_tree;

Status Node::Process()
{
	return Status::kFailure;
}

void Node::AddAChildren(const Node& node)
{
	//controls of the node ??? if needed


	all_childrens_.emplace_back(node);
}
