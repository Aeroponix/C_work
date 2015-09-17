//
//  card.cpp
//  
//
//  Created by Kadi on 2/8/15.
//
//

#include "card.hpp"
#include <string>
#include <iostream>

extern "C"
Card::Card(int cardId) : id(cardId), color('0'), value(0), type('0') {
	suits = "HDSC"; // 
	ranks = "2345678910JQKA";
	colors = "RB";
	value = 'Q';
	type = 'H';
	color = 'B';
}

Card::~Card() {

}

std::string
Card::getFile() { 
	std::string other = ".gif";
	std::string thingy = "assets/" + type + value + color + other;
	return thingy;
}

int
Card::rank() {
	if(id <= 12) {
		return id;
	}else if(id > 12 && id <= 25) {
		return id - 13;
	}else if(id > 25 && id <= 38) {
		return id - 26;
	}else if(id > 38 && id <= 51) {
		return id - 39;
	}
}

int
Card::suit() {
	if(id <= 12) {
		return 0;
	}else if(id > 12 && id <= 25) {
		return 1;
	}else if(id > 25 && id <= 38) {
		return 2;
	}else if(id > 38 && id <= 51) {
		return 3;
	}
}

int
Card::Color() { 
	if(id <= 25 && id >= 0) { 
		return 0;
	}else if(id > 25 && id <= 51) {
		return 1;
	} 
}
void
Card::printCard() {
	std::cout << this->getvalue() << this->gettype()<<this->getcolor() << std::endl;
}

int
Card::operator==(const Card &other) const {
	int score = 0;	
	if(value == other.value) {
		score++;
	}
	if(type == other.type) {
		score++;
	}
	if(color == other.color) {
		score++;
	}
	return score;
}

bool
Card::operator<(const Card &other) const{
	return id < other.id;
}

void 
Card::setcolor( char &color )
{
    color = color;
}

void 
Card::setvalue( char &value)
{
    value = value;
}

void 
Card::settype( char &type)
{
    type = type;
}

char 
Card::getcolor()
{
    return color;
}

char
Card::getvalue()
{
    return value;
}

char 
Card::gettype()
{
    return type;
}

