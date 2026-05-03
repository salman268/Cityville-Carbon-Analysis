#include <iostream>
#include "CSVLoader.hpp"
#include "LinkedList.hpp"
#include <chrono> // C++ library used as a stopwatch for our speed tests

int main() {
    std::cout << "--- Cityville LINKED LIST Program Starting ---\n";
    CSVLoader dataBot;
    
    // Create three separate Linked Lists
    LinkedList cityA_LinkedList, cityB_LinkedList, cityC_LinkedList;
    
    
    // We load all three datasets to prove our Linked List works for everything
    std::cout << "\n=== LOADING ALL DATASETS INTO LINKED LISTS ===\n";
    
    dataBot.loadToLinkedList("dataset1-cityA.csv", cityA_LinkedList);
    std::cout << "Dataset 1 (City A) Linked List loaded successfully.\n";
    
    dataBot.loadToLinkedList("dataset2-cityB.csv", cityB_LinkedList);
    std::cout << "Dataset 2 (City B) Linked List loaded successfully.\n";
    
    dataBot.loadToLinkedList("dataset3-cityC.csv", cityC_LinkedList);
    std::cout << "Dataset 3 (City C) Linked List loaded successfully.\n";
    
    // ==========================================
   // SORTING PERFORMANCE (ALL CITIES)
    // ==========================================
    std::cout << "\n=== SORTING PERFORMANCE EXPERIMENT (SECTION 6) ===\n";
    
    // Load fresh unsorted copies just for Selection Sort so it's a fair race
    LinkedList cityA_Sel, cityB_Sel, cityC_Sel;
    dataBot.loadToLinkedList("dataset1-cityA.csv", cityA_Sel);
    dataBot.loadToLinkedList("dataset2-cityB.csv", cityB_Sel);
    dataBot.loadToLinkedList("dataset3-cityC.csv", cityC_Sel);

    // --- BUBBLE SORT TIMERS ---
    // Start stopwatch, run sort, stop stopwatch
    auto sBA = std::chrono::high_resolution_clock::now(); cityA_LinkedList.sortByAge(); auto eBA = std::chrono::high_resolution_clock::now();
    auto durBA = std::chrono::duration_cast<std::chrono::microseconds>(eBA - sBA);
    
    auto sBB = std::chrono::high_resolution_clock::now(); cityB_LinkedList.sortByAge(); auto eBB = std::chrono::high_resolution_clock::now();
    auto durBB = std::chrono::duration_cast<std::chrono::microseconds>(eBB - sBB);
    
    auto sBC = std::chrono::high_resolution_clock::now(); cityC_LinkedList.sortByAge(); auto eBC = std::chrono::high_resolution_clock::now();
    auto durBC = std::chrono::duration_cast<std::chrono::microseconds>(eBC - sBC);

    // --- SELECTION SORT TIMERS ---
    auto sSA = std::chrono::high_resolution_clock::now(); cityA_Sel.selectionSortByAge(); auto eSA = std::chrono::high_resolution_clock::now();
    auto durSA = std::chrono::duration_cast<std::chrono::microseconds>(eSA - sSA);

    auto sSB = std::chrono::high_resolution_clock::now(); cityB_Sel.selectionSortByAge(); auto eSB = std::chrono::high_resolution_clock::now();
    auto durSB = std::chrono::duration_cast<std::chrono::microseconds>(eSB - sSB);

    auto sSC = std::chrono::high_resolution_clock::now(); cityC_Sel.selectionSortByAge(); auto eSC = std::chrono::high_resolution_clock::now();
    auto durSC = std::chrono::duration_cast<std::chrono::microseconds>(eSC - sSC);

    // Print the results. Memory is bigger here because nodes have pointers
    std::cout << "Dataset \t| Algorithm \t| Execution Time (us) \t| Memory (Bytes)\n";
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "City A (200) \t| Bubble Sort \t| " << durBA.count() << " \t\t\t| " << sizeof(Node) * 200 << "\n";
    std::cout << "City A (200) \t| Selection Sort| " << durSA.count() << " \t\t\t| " << sizeof(Node) * 200 << "\n";
    std::cout << "City B (178) \t| Bubble Sort \t| " << durBB.count() << " \t\t\t| " << sizeof(Node) * 178 << "\n";
    std::cout << "City B (178) \t| Selection Sort| " << durSB.count() << " \t\t\t| " << sizeof(Node) * 178 << "\n";
    std::cout << "City C (122) \t| Bubble Sort \t| " << durBC.count() << " \t\t\t| " << sizeof(Node) * 122 << "\n";
    std::cout << "City C (122) \t| Selection Sort| " << durSC.count() << " \t\t\t| " << sizeof(Node) * 122 << "\n";
    std::cout << "--------------------------------------------------------------------------------\n";

    // ==========================================
    //  SEARCHING EXPERIMENTS (ALL CITIES)
    // ==========================================
    std::cout << "\n=== SEARCH EXPERIMENTS (SECTION 7) ===\n";
    double threshold = 15.0; 

    std::cout << "\n--- TEST 1: Linear Search (> 15 km) across all cities ---\n";
    auto sSearchA = std::chrono::high_resolution_clock::now(); cityA_LinkedList.searchByDistance(threshold); auto eSearchA = std::chrono::high_resolution_clock::now();
    auto durSearchA = std::chrono::duration_cast<std::chrono::microseconds>(eSearchA - sSearchA);

    auto sSearchB = std::chrono::high_resolution_clock::now(); cityB_LinkedList.searchByDistance(threshold); auto eSearchB = std::chrono::high_resolution_clock::now();
    auto durSearchB = std::chrono::duration_cast<std::chrono::microseconds>(eSearchB - sSearchB);

    auto sSearchC = std::chrono::high_resolution_clock::now(); cityC_LinkedList.searchByDistance(threshold); auto eSearchC = std::chrono::high_resolution_clock::now();
    auto durSearchC = std::chrono::duration_cast<std::chrono::microseconds>(eSearchC - sSearchC);

    std::cout << "\n--- TEST 2: Linear Search (Target Age: 34) across all cities ---\n";
    // We can't use Binary Search on a Linked List, so we use Linear Search for both tests
    auto sLinA = std::chrono::high_resolution_clock::now(); cityA_LinkedList.linearSearchByAge(34); auto eLinA = std::chrono::high_resolution_clock::now();
    auto durLinA = std::chrono::duration_cast<std::chrono::microseconds>(eLinA - sLinA);

    auto sLinB = std::chrono::high_resolution_clock::now(); cityB_LinkedList.linearSearchByAge(34); auto eLinB = std::chrono::high_resolution_clock::now();
    auto durLinB = std::chrono::duration_cast<std::chrono::microseconds>(eLinB - sLinB);

    auto sLinC = std::chrono::high_resolution_clock::now(); cityC_LinkedList.linearSearchByAge(34); auto eLinC = std::chrono::high_resolution_clock::now();
    auto durLinC = std::chrono::duration_cast<std::chrono::microseconds>(eLinC - sLinC);

    std::cout << "\nSearch Performance Summary (LINKED LIST):\n";
    std::cout << "Dataset \t| Target \t| Linear Search >15km (us) \t| Linear Search Age 34 (us) \t| Memory (Bytes)\n";
    std::cout << "-------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << "City A \t\t| >15km / Age 34| " << durSearchA.count() << " \t\t\t\t| " << durLinA.count() << " \t\t\t\t| " << sizeof(Node) * 200 << "\n";
    std::cout << "City B \t\t| >15km / Age 34| " << durSearchB.count() << " \t\t\t\t| " << durLinB.count() << " \t\t\t\t| " << sizeof(Node) * 178 << "\n";
    std::cout << "City C \t\t| >15km / Age 34| " << durSearchC.count() << " \t\t\t\t| " << durLinC.count() << " \t\t\t\t| " << sizeof(Node) * 122 << "\n";
    std::cout << "-------------------------------------------------------------------------------------------------------------------------\n";

    return 0; // End of the linked list program
}