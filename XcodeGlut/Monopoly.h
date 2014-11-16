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
#include <boost/serialization/vector.hpp>
const int MAX_NO_OF_CITIES=50;
using namespace std;

class Monopoly
{
public:
    string currency;
    float startingMoney;
    float jailFine;
    float taxPercent;
    int taxAmount;
    bool graph[MAX_NO_OF_CITIES][MAX_NO_OF_CITIES];
    vector <Location> locations;
    vector <Player> players;
    vector<int> skipCheats;
    vector<int> rentCheats;
    
    int currentTurn;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
    	ar & currency;
    	ar & startingMoney;
    	ar & jailFine;
    	ar & taxPercent;
    	ar &graph;
    	ar & locations;
    	ar & players;
        ar & currentTurn;
        ar & skipCheats;
        ar & rentCheats;
    }

    
    void payRent(int playerID, float rent);
    void payTaxes(int playerID, float taxes);//taxes in amount
    void movePiece(int playerID, int location);
    void mortgage(int playerID, int location);
    void payJailFine(int playerID);
};
#endif /* defined(____Monopoly__) */
