#ifndef API_BEHAVIOR_TREE_TREE_H_
#define API_BEHAVIOR_TREE_TREE_H_
#include <memory>

#include "bt_node.h"

namespace behavior_tree
{
	class Tree
	{
	private:
		Node* root_;

	public:

		Tree() { root_ = nullptr; }
		~Tree() { delete root_; }

		//tree's tick
		void Tick();

		//add a node to children list of the root
		void AddNode(Node* node);

	};
}
#endif//API_BEHAVIOR_TREE_TREE_H_