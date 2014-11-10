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

void Monopoly::mortgage(int playerID, int location)
{
    players.at(playerID).currentMoney-=locations.at(location).cost[locations.at(location).status];
    locations.at(location).owner=-1;
}

void Monopoly::payJailFine(int playerID)
{
    players.at(playerID).currentMoney-=jailFine;
}