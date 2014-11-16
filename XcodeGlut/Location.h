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
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
class Location {
    
    
public:
    
    float cost[7];
    float rent[6];
        std::string locationOfObjectFile;
    int group;
    int locationNo;
    std::string name;
    int owner;//-1 is owned by bank, otherwise player ID
    int status;//0,1,2,3 for house 1,2,3 adn hotel
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
    	ar & cost;
    	ar & rent;
    	ar & locationOfObjectFile;
    	ar & group;
    	ar &locationNo;
    	ar & name;
    }

};

#endif /* defined(____Location__) */
