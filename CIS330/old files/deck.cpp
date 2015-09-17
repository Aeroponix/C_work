/*
//  deck.cpp
//
//
//
//
//
//
*/

#include "deck.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Deck::Deck() {
	deck = new Card[52];
	
	for(int i = 0; i < 52; i++) {
		deck[i] = Card(i);
	}
}

Deck::Deck(int size) : deck_size(size) {
	deck = new Card[deck_size];
	
	for(int i = 0; i < deck_size; i++) {
		deck[i] = Card(i);
	}
}

Deck::~Deck() {
	delete []deck;
}

Card&
Deck::operator[] (int i) {
	return deck[i];
}

void
Deck::printDeck() {
	for(int i = 0; i < deck_size; i++) {
		deck[i].printCard();
	}
}

void
Deck::shuffle() {
	srand(time(0));
	for(int i = 0; i < deck_size; i++) {
		int j = std::rand() % deck_size;
		Card temp = deck[i];
		deck[i] = deck[j];
		deck[j] = temp;
	}
}
