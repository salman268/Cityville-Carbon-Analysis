#include "LinkedList.hpp"
#include <iostream>
#include <iomanip> 

// ---------------------------------------------------------
// 1. CONSTRUCTOR & DESTRUCTOR
// ---------------------------------------------------------
LinkedList::LinkedList() {
    head = nullptr; // Start with a completely empty list
}

LinkedList::~LinkedList() {
    Node* current = head;
    
    // Go through every node one by one and delete it to free up memory
    while (current != nullptr) {
        Node* nextNode = current->next; // Remember the next node before deleting this one
        delete current; 
        current = nextNode; // Move to the next node
    }
}

// ---------------------------------------------------------
// 2. CORE LINKED LIST FUNCTIONS
// ---------------------------------------------------------
void LinkedList::addResident(Resident newResident) {
    // Create a new node and put the data inside it
    Node* newNode = new Node;
    newNode->data = newResident;
    newNode->next = nullptr; // It will be at the end, so it points to nothing

    // If the list is empty, this new person becomes the head of the list
    if (head == nullptr) {
        head = newNode;
    } 
    // Otherwise, walk down the list until we find the end, then attach the new node
    else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next; // Keep moving to the next one
        }
        current->next = newNode; // Attach it at the very end
    }
}

void LinkedList::displayAll() {
    Node* current = head;
    int count = 0;
    
    // Walk down the list and print the first 5 people
    while (current != nullptr && count < 5) {
        std::cout << "Resident: " << current->data.residentID 
                  << " | Age: " << current->data.age 
                  << " | Transport: " << current->data.modeOfTransport << "\n";
        current = current->next; // Move to the next node
        count++;
    }
}

// ---------------------------------------------------------
// 3. CARBON EMISSION ANALYTICS
// ---------------------------------------------------------
void LinkedList::analyzeAgeGroup(int minAge, int maxAge, std::string groupName) {
    int residentCount = 0;
    double totalEmissions = 0.0;
    
    // Parallel arrays to help us count cuz we can't use built-in maps
    std::string modes[6] = {"Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"};
    int modeCounts[6] = {0, 0, 0, 0, 0, 0};
    double modeEmissions[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; 

    Node* current = head; // Start at the beginning of the list
    
    // Walk through every node in the linked list
    while (current != nullptr) {
        // Check if this person is in the right age group
        if (current->data.age >= minAge && current->data.age <= maxAge) {
            residentCount++;
            
            // Calculate emissions for this specific person
            double residentEmission = current->data.dailyDistance * current->data.carbonEmissionFactor * current->data.averageDayPerMonth;
            totalEmissions += residentEmission;

            // Find their mode of transport and add it to our counters
            for (int j = 0; j < 6; j++) {
                if (current->data.modeOfTransport == modes[j]) {
                    modeCounts[j]++;
                    modeEmissions[j] += residentEmission; 
                    break; 
                }
            }
        }
        current = current->next; // Move to the next person
    }

    std::cout << "\nAge Group: " << minAge << "-" << maxAge << " (" << groupName << ")\n";
    
    // If no one is in this group, stop to prevent dividing by zero
    if (residentCount == 0) {
        std::cout << "No residents in this age group.\n";
        return; 
    }

    // Set up the fixed-width columns for the table
    std::cout << std::left << std::setw(18) << "Mode of Transport" << " | "
              << std::setw(7) << "Count" << " | "
              << std::setw(25) << "Total Emission (kg CO2)" << " | "
              << "Average per Resident\n";
    std::cout << "--------------------------------------------------------------------------------\n";
    
    for (int j = 0; j < 6; j++) {
        // Calculate the average safely
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

// Bubble Sort for Linked List
void LinkedList::sortByAge() {
    // If the list is empty or only has one thing, it's already sorted
    if (head == nullptr || head->next == nullptr) {
        return; 
    }

    bool swapped;
    Node* current;
    Node* last = nullptr; // Helps us not check the end of the list once it's sorted

    do {
        swapped = false;
        current = head;

        while (current->next != last) {
            // If the current person is older than the next person, swap them
            if (current->data.age > current->next->data.age) {
                // Swapping the actual data inside the nodes is much easier than changing pointers
                Resident temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
        last = current; // The last person we checked is now in the correct spot
    } while (swapped);
}

// Selection Sort for Linked List
void LinkedList::selectionSortByAge() {
    Node* current = head;
    
    while (current != nullptr) {
        Node* minNode = current; // Assume the current spot is the youngest
        Node* nextNode = current->next;
        
        // Scan the rest of the list to find the actual youngest person
        while (nextNode != nullptr) {
            if (nextNode->data.age < minNode->data.age) {
                minNode = nextNode; // Found someone younger, remember their node
            }
            nextNode = nextNode->next;
        }
        
        // If we found someone younger, swap their data with the current spot
        if (minNode != current) {
            Resident temp = current->data;
            current->data = minNode->data;
            minNode->data = temp;
        }
        current = current->next; // Move forward one step and repeat
    }
}

// ---------------------------------------------------------
// 5. SEARCHING ENGINES 
// ---------------------------------------------------------

// Linear Search: Walks down the list to check the distance
void LinkedList::searchByDistance(double minDistance) {
    int matchCount = 0;
    Node* current = head;
    
    // Set up the table layout
    std::cout << std::left << std::setw(15) << "Resident ID" << " | "
              << std::setw(5) << "Age" << " | "
              << std::setw(15) << "Transport" << " | "
              << "Distance\n";
    std::cout << "------------------------------------------------------------\n";
    
    // Walk through the list
    while (current != nullptr) {
        if (current->data.dailyDistance > minDistance) {
            // Only print the first 5 matches
            if (matchCount < 5) {
                std::cout << std::left << std::setw(15) << current->data.residentID << " | "
                          << std::setw(5) << current->data.age << " | "
                          << std::setw(15) << current->data.modeOfTransport << " | "
                          << current->data.dailyDistance << " km\n";
            }
            matchCount++;
        }
        current = current->next; // Move to the next person
    }
    std::cout << "------------------------------------------------------------\n";
    std::cout << "Total Matches: " << matchCount << " residents (Showing top 5)\n";
}

// Linear Search: Walks down the list to find an exact age match
void LinkedList::linearSearchByAge(int targetAge) {
    Node* current = head;
    bool found = false;
    
    while (current != nullptr) {
        if (current->data.age == targetAge) {
            std::cout << "Match Found via Linear Search! Resident ID: " << current->data.residentID 
                      << " | Age: " << current->data.age << "\n";
            found = true;
            break; // We found what we need, so we can stop searching early
        }
        current = current->next;
    }
    
    // If we reached the end of the list (nullptr) and found nothing
    if (!found) {
        std::cout << "No resident found with Age " << targetAge << "\n";
    }
}