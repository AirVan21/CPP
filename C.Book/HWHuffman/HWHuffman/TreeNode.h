#pragma once

#include "Symbol.h"

struct tree_node
{
	unsigned int  left_child;
	unsigned int  right_child;
	symbol        character;
};

class compare_tree_node
{
public:
	inline bool operator()(const tree_node &tree_one, const tree_node &tree_two)
	{
		return tree_one.character.frequnecy > tree_two.character.frequnecy;
	}
};

