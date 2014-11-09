//
//  Monopoly.cpp
//  
//
//  Created by Robin Malhotra on 24/10/14.
//
//

#include "Monopoly.h"
void Monopoly::payRent(int playerID, float rent)
{
    players.at(playerID).currentMoney-=rent;
}
void Monopoly::payTaxes(int playerID, float taxes)
{
    players.at(playerID).currentMoney-=taxes;
}

void Monopoly::movePiece(int playerID, int location)
{
    players.at(playerID).currentPosition=location;
}