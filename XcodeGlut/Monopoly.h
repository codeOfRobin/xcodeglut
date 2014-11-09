//
//  Monopoly.h
//  
//
//  Created by Robin Malhotra on 24/10/14.
//
//

#ifndef ____Monopoly__
#define ____Monopoly__

#include <iostream>
#include <string>
#include <vector>
#include "Location.h"
#include "Player.h"
const int MAX_NO_OF_CITIES=50;
using namespace std;

class Monopoly
{
public:
    string* currency;
    float startingMoney;
    float jailFine;
    float taxPercent;
    bool graph[MAX_NO_OF_CITIES][MAX_NO_OF_CITIES];
    vector <Location> locations;
    vector <Player> players;
    
    void payRent(int playerID);
    void payTaxes(int playerID);
    void movePiece(int playerID, int location);
};
#endif /* defined(____Monopoly__) */
