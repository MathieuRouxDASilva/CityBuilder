#ifndef API_BEHAVIOR_TREE_NODE_H_
#define API_BEHAVIOR_TREE_NODE_H_
#include <vector>

namespace behavior_tree
{
	//enum -> state of node
	enum class Status
	{
		kRunning,
		kSuccess,
		kFailure
	};


	class Node
	{
	private:
		std::vector<Node> all_childrens_;


	public:
		//function that does something depending on the node's task and return a status
		virtual Status Process();

		//add a children to the node
		void AddAChildren(const Node& node);

	};
}

#endif //API_BEHAVIOR_TREE_NODE_H_