#include "ArrayList.hpp"
#include <iostream>
#include <iomanip> // to make the console tables look nice

// ---------------------------------------------------------
// 1. CONSTRUCTOR & DESTRUCTOR
// ---------------------------------------------------------
ArrayList::ArrayList() {
    capacity = 10;                   // Start with a small array of 10 spaces
    currentSize = 0;                 // Currently, there is no one in the array
    arr = new Resident[capacity];    // Create the actual array in the computer's memory
}

ArrayList::~ArrayList(){
    delete[] arr;                    // Clean up the memory when we are done so it doesn't leak
}

// ---------------------------------------------------------
// 2. CORE ARRAY FUNCTIONS
// ---------------------------------------------------------
void ArrayList::addResident(Resident newResident) {
    // Check if the array is completely full
    if (currentSize == capacity) {
        int newCapacity = capacity * 2; // Double the size for the new array
        Resident* newArr = new Resident[newCapacity]; // Create the bigger array

        // Copy everyone from the old array into the new bigger array
        for (int i = 0; i < currentSize; i++){
            newArr[i] = arr[i];
        }

        delete[] arr; // Delete the old, small array
        arr = newArr; // Point to the new array
        capacity = newCapacity; // Update our capacity tracker
    }
    
    // Put the new person in the next available empty slot
    arr[currentSize] = newResident;
    currentSize++; // Increase our headcount
}

void ArrayList::displayAll() {
    // Only print the first 5 people so we don't spam the terminal
    int limit = (currentSize < 5) ? currentSize : 5; 
    
    for (int i = 0; i < limit; i++) {
        std::cout << "Resident: " << arr[i].residentID 
                  << " | Age: " << arr[i].age 
                  << " | Transport: " << arr[i].modeOfTransport << "\n";
    }
}

// ---------------------------------------------------------
// 3. CARBON EMISSION ANALYTICS 
// ---------------------------------------------------------
double ArrayList::calculateTotalCityEmissions() {
    double grandTotal = 0.0;
    // Loop through every single person and add up their emissions
    for (int i = 0; i < currentSize; i++) {
        grandTotal += (arr[i].dailyDistance * arr[i].carbonEmissionFactor * arr[i].averageDayPerMonth);
    }
    return grandTotal;
}

void ArrayList::analyzeAgeGroup(int minAge, int maxAge, std::string groupName) {
    int residentCount = 0;
    double totalEmissions = 0.0;

    // We can't use standard libraries like maps, so we use parallel arrays to count things
    std::string modes[6] = {"Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"};
    int modeCounts[6] = {0, 0, 0, 0, 0, 0};
    double modeEmissions[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; 

    // Loop through every person in the array
    for (int i = 0; i < currentSize; i++) {
        // Check if they belong in the age group we are looking for
        if (arr[i].age >= minAge && arr[i].age <= maxAge) {
            residentCount++; // Count them
            
            // Calculate this specific person's emission
            double residentEmission = arr[i].dailyDistance * arr[i].carbonEmissionFactor * arr[i].averageDayPerMonth;
            totalEmissions += residentEmission; // Add it to the group's total

            // Figure out which transport mode they use and update our parallel arrays
            for (int j = 0; j < 6; j++) {
                if (arr[i].modeOfTransport == modes[j]) {
                    modeCounts[j]++; // Add 1 to the count for this mode
                    modeEmissions[j] += residentEmission; // Add to the total emissions for this mode
                    break; // Stop looking once we find the match
                }
            }
        }
    }

    std::cout << "\nAge Group: " << minAge << "-" << maxAge << " (" << groupName << ")\n";
    
    // If no one is in this age group, stop here so we don't divide by zero later
    if (residentCount == 0) {
        std::cout << "No residents in this age group.\n";
        return; 
    }

    // Print the table headers using setw to keep columns perfectly straight
    std::cout << std::left << std::setw(18) << "Mode of Transport" << " | "
              << std::setw(7) << "Count" << " | "
              << std::setw(25) << "Total Emission (kg CO2)" << " | "
              << "Average per Resident\n";
    std::cout << "--------------------------------------------------------------------------------\n";
    
    // Print the data for each mode of transport
    for (int j = 0; j < 6; j++) {
        // Calculate the average, making sure we don't divide by zero if count is 0
        double avgMode = (modeCounts[j] > 0) ? (modeEmissions[j] / modeCounts[j]) : 0.0;
        
        std::cout << std::left << std::setw(18) << modes[j] << " | " 
                  << std::setw(7) << modeCounts[j] << " | " 
                  << std::setw(25) << modeEmissions[j] << " | " 
                  << avgMode << "\n";
    }
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "Total Emission for Age Group: " << totalEmissions << " kg CO2\n";
}

// ---------------------------------------------------------
// 4. SORTING ENGINES 
// ---------------------------------------------------------

// Bubble Sort: Compares side-by-side elements and pushes the highest value to the end
void ArrayList::sortByAge() {
    for (int i = 0; i < currentSize - 1; i++) {
        for (int j = 0; j < currentSize - i - 1; j++) {
            // If the person on the left is older, swap them to the right
            if (arr[j].age > arr[j+1].age) {
                Resident temp = arr[j]; 
                arr[j] = arr[j+1]; 
                arr[j+1] = temp; 
            }
        }
    }
}

// Selection Sort: Finds the youngest person and brings them to the front
void ArrayList::selectionSortByAge() {
    for (int i = 0; i < currentSize - 1; i++) {
        int minIndex = i; // Assume the first unsorted person is the youngest
        
        // Check the rest of the array to see if anyone is actually younger
        for (int j = i + 1; j < currentSize; j++) {
            if (arr[j].age < arr[minIndex].age) {
                minIndex = j; // We found someone younger, remember where they are
            }
        }
        
        // If we found someone younger, swap them to the front of the unsorted section
        if (minIndex != i) {
            Resident temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

// ---------------------------------------------------------
// 5. SEARCHING ENGINES 
// ---------------------------------------------------------

// Linear Search: Checks every single person one by one
void ArrayList::searchByDistance(double minDistance) {
    int matchCount = 0;
    
    // Set up the table format
    std::cout << std::left << std::setw(15) << "Resident ID" << " | "
              << std::setw(5) << "Age" << " | "
              << std::setw(15) << "Transport" << " | "
              << "Distance\n";
    std::cout << "------------------------------------------------------------\n";
    
    // Loop through everyone
    for (int i = 0; i < currentSize; i++) {
        // If they travel further than the minimum distance, we found a match
        if (arr[i].dailyDistance > minDistance) {
            if (matchCount < 5) { // Only print the first 5 so the console stays clean
                std::cout << std::left << std::setw(15) << arr[i].residentID << " | "
                          << std::setw(5) << arr[i].age << " | "
                          << std::setw(15) << arr[i].modeOfTransport << " | "
                          << arr[i].dailyDistance << " km\n";
            }
            matchCount++;
        }
    }
    std::cout << "------------------------------------------------------------\n";
    std::cout << "Total Matches: " << matchCount << " residents (Showing top 5)\n";
}

// Binary Search: Cuts the array in half to find the target much faster
 
void ArrayList::binarySearchByAge(int targetAge) {
    int left = 0;
    int right = currentSize - 1;
    bool found = false;
    
    while (left <= right) {
        int mid = left + (right - left) / 2; // Find the middle person
        
        // Check if the middle person is the age we want
        if (arr[mid].age == targetAge) {
            std::cout << "Match Found via Binary Search! Resident ID: " << arr[mid].residentID 
                      << " | Age: " << arr[mid].age << "\n";
            found = true;
            break; // Stop searching once we find someone
        }
        
        // If the middle person is younger than the target, search the right side
        if (arr[mid].age < targetAge) {
            left = mid + 1; 
        } 
        // If the middle person is older, search the left side
        else {
            right = mid - 1; 
        }
    }
    
    // If we checked everywhere and found nothing
    if (!found) {
        std::cout << "No resident found with Age " << targetAge << "\n";
    }
}