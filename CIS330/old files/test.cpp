#include "card.hpp"
#include "deck.hpp"
#include <iostream>
#include <string>

int main() {
	Card c(25);
	c.printCard();
	
	Card s(25);
	s.printCard();	

	Card col(25);
	col.printCard();

	Deck d(25);
	
	if(c == s) {
		std::cout << "true" << std::endl;
	}else {
		std::cout << "false" << std::endl;
	}
	
	if(c < s) {
		std::cout << "true" << std::endl;
	}else {
		std::cout << "false" << std::endl;
	}
	
	d.printDeck();
	std::cout << "\n" << std::endl;
	
	d.shuffle();
	d.printDeck();
}
