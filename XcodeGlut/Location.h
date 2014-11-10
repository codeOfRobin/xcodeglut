//
//  Location.h
//  
//
//  Created by Robin Malhotra on 24/10/14.
//
//

#ifndef ____Location__
#define ____Location__

#include <iostream>
class Location {
    
    
public:
    
    float cost[7];
    float rent[6];
    std::string* locationOfObjectFile;
    int group;
    int locationNo;
    std::string* name;
    int owner;//-1 is owned by bank, otherwise player ID
    int status;//0,1,2,3 for house 1,2,3 adn hotel
    
};

#endif /* defined(____Location__) */
