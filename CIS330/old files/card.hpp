//
//  card.hpp
//  
//
//  Created by Kadi on 2/8/15.
//
//

#ifndef CARD_H_
#define CARD_H_

#include <string>

class Card
{
public:
  	Card() {};
    	Card(int cardId);
	~Card();
	std::string getFile();
	int rank();
	int suit();
	int Color();
	void printCard();
	bool operator<(const Card &other) const;
	int operator==(const Card &other) const;
    void setcolor( char &color );
    void setvalue( char &value);
    void settype( char &type);
    char getcolor();
    char getvalue();
    char gettype();
private:
	std::string ranks;
	std::string suits;
	std::string colors;
	int id;
    char color;
    char value;
    char type;

};
#endif /* defined(____card__) */
