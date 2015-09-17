#ifndef SKILLTREE_H
#define SKILLTREE_H

#include <ostream>
#include "Skill.h"

/**************************
Adam Lindsey
CS260 - LAB #4
SkillTree.h
WINTER 2014
**************************/

class SkillTree
{
public:
	SkillTree();
	SkillTree(char* n);
	SkillTree(const SkillTree& aTree);
	~SkillTree();

	const SkillTree& operator= (const SkillTree& aTree);

	void Display(ostream& out);
	void insert(const Skill& aSkill);
	void AddSkill(char* n, char* d, int l);
	void AddSkill(char* n, char* d, int l, char* x);
	bool remove(char* x);
	bool contains(char* x) const;
	Skill* FindSkill(char* name);
	int getSize(void) const;

	friend ostream& operator<<(ostream& out, SkillTree& aTree);

private:
	struct node
	{
		Skill s;
		node * left, * right;
		node(const Skill& aSkill) :
			s(aSkill), left(0), right(0)
		{
		}
	};
	node * root;
	char*  name;
	int    size;
	
	void insert(node*& root, const Skill& aSkill);
	bool contains(node& root, char* x) const;
	bool remove(node*& root, char* x);
	void deleteNode(node *& target);
	void display(ostream& out, node * root, int level) const;
	void destroyTree(node*& root);
	void copyTree(node*& newRoot, node * root);
};

#endif