#ifndef SKILL_H
#define SKILL_H

#include <iostream>
using namespace std;

/**************************
Adam Lindsey
CS260 - LAB #4
Skill.h
WINTER 2014
**************************/

class Skill
{
public:
	Skill();
	Skill(char* n, char* d, int l);
	Skill(const Skill& aSkill);
	~Skill();

	void Display(ostream& out)
	{
		out << this;
	}

	char* getName(void)const;
	char* getDesc(void)const;
	int  getLevel(void)const;

	const Skill& operator=(const Skill& aSkill);

	void setName(char* n);
	void setDesc(char* d);
	void setLevel(int l);

	friend bool operator< (const Skill& d1, const Skill& d2);
	friend bool operator== (const Skill& d1, const Skill& d2);
	friend ostream& operator<<(ostream& out, const Skill& d);

	friend class SkillTree;

private:
	char* name;
	char* description;
	int   level;
};


#endif