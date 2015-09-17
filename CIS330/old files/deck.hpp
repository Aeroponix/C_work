#ifndef DECK_HPP_
#define DECK_HPP_

#include "card.hpp"

class Deck {
public:
	Deck();
	Deck(int deck_size);
	~Deck();
	Card& operator[](int i);
	void shuffle(); 
	void printDeck();
private:
	Card *deck;
	int deck_size;
};

#endif /* DECK_HPP_ */
