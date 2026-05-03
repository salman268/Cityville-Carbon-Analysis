#ifndef Resident_HPP
#define Resident_HPP
#include <string>

struct Resident {
std::string residentID;           
    int age;                          
    std::string modeOfTransport;       
    double dailyDistance;              
    double carbonEmissionFactor;        
    int averageDayPerMonth;            
};
#endif
