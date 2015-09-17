/*
//  card.h
//  
//
//  Created by Kadi on 2/8/15.
//  Edited by Adam
*/

#ifndef CARD_H_
#define CARD_H_

#include <string.h>

//card object
typedef struct 
Card
{
	//card suit value
	int type; 
	//card face value
	int value;
	//card color
	int color;
	//filename for card graphic
	char file[14];
} CARD;

#endif
