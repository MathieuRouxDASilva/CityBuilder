#include "behavior_tree/bt_tree.h"

#include <iostream>

using namespace behavior_tree;

//what happens every frame
void Tree::Tick()
{
	Status status;

	if(root_ != nullptr)
	{
		status = root_->Process();
	}

	switch (status)
	{
	case Status::kSuccess:
		break;
	case Status::kFailure:
		break;
	case Status::kRunning:
		break;
	default:
		std::cout << "ah\n";
		break;
	}

}

//add node to root
void Tree::AddNode(Node* node)
{
	root_ = node;
}