 
#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Resident.hpp"

// 1. The Node here holds the Resident data AND the address to the next box.
 
struct Node {
    Resident data;  // The   person's info
    Node * next;    //A pointer (address) to the next Node in the chain

};

// 2. The LinkedList Class 

class LinkedList {
    private:
       Node * head;       // pointer to hold the address of the very FIRST node.
       int currentSize; // Keeping track of how many people are in the chain.


    public:

    //constructor: Sets up an empty list
    LinkedList();
    
    // destrcutor: Cleans up all the scattered nodes when   done
    ~LinkedList();

    // core functions
    void addResident(Resident newResident);
    void displayAll();
    void sortByAge();
    void searchByDistance(double minDistance);
    void linearSearchByAge(int targetAge);
    void selectionSortByAge();
    void analyzeAgeGroup(int minAge, int maxAge, std::string groupName);

};
#endif
 