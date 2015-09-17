#include "Skill.h"
#include <iostream>
#include <iomanip>
using namespace std;

/**************************
Adam Lindsey
CS260 - LAB #4
Skill.cpp
WINTER 2014
***************************
private:
	char* name;
	char* description;
	int   level;
**************************/

Skill::Skill() : name(NULL), description(NULL), level(0) { }
Skill::Skill(char* n, char*d, int l) : 
	name(NULL), 
	description(NULL), 
	level(l)
{
	setName(n);
	setDesc(d);
}
Skill::Skill(const Skill& aSkill) : name(NULL), description(NULL){
	setName(aSkill.name);
	setDesc(aSkill.description);
	setLevel(aSkill.level);
}
Skill::~Skill()
{
	if(name) delete[] name;
	if(description) delete[] description;
}

char* Skill::getName(void)const{return name;}
char* Skill::getDesc(void)const{return description;}
int  Skill::getLevel(void)const{return level;}

void Skill::setName(char* n){this->name = n;}
void Skill::setDesc(char* d){this->description = d;}
void Skill::setLevel(int l){this->level = l;}

const Skill& Skill::operator=(const Skill& aSkill)
{
	if(this == &aSkill) return *this;
	else
	{
		setName(aSkill.name);
		setDesc(aSkill.description);
		setLevel(aSkill.level);
		return *this;
	}
}
bool operator<(const Skill& s1, const Skill& s2)
{
	return s1.getLevel() < s2.getLevel();
}
bool operator==(const Skill& s1, const Skill& s2)
{
	return s1.getName() == s2.getName();
}

ostream& operator<<(ostream& out, const Skill& aSkill)
{
	out << "- " << aSkill.getName()
		<< " -- " << aSkill.getDesc()
		<< " [lvl: " << aSkill.getLevel() << "]";
	return out;
}