#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include "Resident.hpp"

class ArrayList {
    private:

    Resident* arr;
    int capacity;
    int currentSize;

    public:
    ArrayList();

    ~ArrayList();

    void addResident(Resident newResident);
    void displayAll();
    void analyzeAgeGroup(int minAge, int maxAge, std::string groupName);
    void sortByAge();
    void searchByDistance(double minDistance);
    double calculateTotalCityEmissions();
    void binarySearchByAge(int targetAge);
    void selectionSortByAge();

};
#endif