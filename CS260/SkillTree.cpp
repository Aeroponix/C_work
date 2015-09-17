#include "SkillTree.h"
#include <ostream>
using namespace std;

/************************
Adam Lindsey
CS260 - LAB #4
SkillTree.cpp
WINTER 2014
**************************
private:
	node * root;
	char*  name;
	int    size;
************************/

SkillTree::SkillTree() : root(NULL), name(NULL), size(0) { }
SkillTree::SkillTree(char* n) : root(NULL), name(NULL), size(0)
{
	name = n;
}
SkillTree::SkillTree(const SkillTree& aTree) : root(NULL), size(aTree.size)
{
	*this = aTree;
}
SkillTree::~SkillTree()
{
	destroyTree(root);
}
void SkillTree::destroyTree(node *& root)
{
	if(root)
	{
		destroyTree(root->left);
		destroyTree(root->right);
		delete root;
		root = NULL;
	}
	if(name) delete[] name;
}

const SkillTree& SkillTree::operator= (const SkillTree& aTree)
{
	if(this == &aTree) return *this;
	else
	{
		destroyTree(root); 
		copyTree(root, aTree.root);
		return *this;
	}
}
void SkillTree::copyTree (node*& newRoot, node * root)
{
	if(root)
	{
		newRoot = new node(root->s);
		copyTree(newRoot->left, root->left);
		copyTree(newRoot->right, root->right);
	} else { newRoot = NULL; }
}

void SkillTree::AddSkill(char* n, char* d, int l)
{
	insert(Skill(n,d,l));
}
void SkillTree::AddSkill(char* n, char* d, int l, char* x)
{
	//needs finished!!!!!!!!!!!!!!!!//
	if(contains(x)) insert(Skill(n,d,l));


	

}
void SkillTree::insert (const Skill& aSkill)
{	
	insert(root, aSkill);
}
void SkillTree::insert (node*& root, const Skill& aSkill)
{
	if(!root)
	{
		root = new node(aSkill);
		size++;
	}
	else if(aSkill < root->s ) insert(root->left, aSkill);
	else insert(root->right, aSkill);
}
Skill* SkillTree::FindSkill(char* name)
{
	bool answer = contains(name);
	return NULL;//fix still!!!!!!!!!!!!!!!!!!!!!!!!!!!










}
bool SkillTree::contains (char* x) const
{
	return contains(*root, x);
}
bool SkillTree::contains(node& root, char* x) const
{
	if(x == root.s.getName()) return true;
	else if(x < root.s.getName()) return root.left  ? contains(*root.left, x)  : false;
	else return root.right ? contains(*root.right, x) : false;
}

static void coolLvlSpacers(ostream& out, int x)
{
	for(int n=0;n<x;n++) out << "  ";
}
void SkillTree::Display(ostream& out)
{
	out << "Skill Tree: " << this->name << endl;
	this->display(out, this->root, 0);
}
void SkillTree::display(ostream& out, node * root, int level)const
{
	if(root) 
	{
		coolLvlSpacers(out, level - 1);
		out << "  " << root->s << endl;
		if(root->left || root->right)
		{
			if(root->left) display(out, root->left, level+1);
			else coolLvlSpacers(out, level);
			if(root->right) display(out, root->right, level + 1);
			else coolLvlSpacers(out, level);
		}
	} else out << "  Empty" << endl;
}
ostream& operator<<(ostream& out, SkillTree& s)
{
	s.display(out,s.root,0);
	return out;
}

int SkillTree::getSize (void) const
{
	return size;
}
bool SkillTree::remove (char* x)
{
	return remove(root, x);
}
bool SkillTree::remove (node*& root, char* x)
{
	if(!root) return false;
	else if(x == root->s.getName()) 
	{
		deleteNode(root);
		return true;
	}
	else if(x < root->s.getName()) return remove(root->left, x);
	else return remove(root->right, x);
}
void SkillTree::deleteNode (node *& target)
{
	node * temp;
	if(!target->left && !target->right)
	{
		delete target;
		target = NULL;
	}
	else if(!target->left)
	{
		temp = target;
		target = target->right;
		temp->right = NULL;
		delete temp;
	}
	else if(!target->right)
	{
		temp = target;
		target = target->left;
		temp->left = NULL;
		delete temp;
	}
	else
	{
		node * prev = NULL;
		node * curr = target->right;
		while(curr->left)
		{
			prev = curr;
			curr = curr->left;
		}
		target->s = curr->s;
		if(!prev) target->right = curr->right;
		else prev->left = curr->right; //the inorder successor could have a right child
		curr->right = NULL;
		delete curr;
	}
	size--;
}

