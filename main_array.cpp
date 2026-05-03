#include <iostream>
#include "CSVLoader.hpp"
#include "ArrayList.hpp"
#include <chrono> // C++ library used as a stopwatch for our speed tests

int main() {
    std::cout << "--- Cityville ARRAY Program Starting ---\n";
    CSVLoader dataBot; // This is our helper object that reads the CSV files

    // ==========================================
    //  CARBON ANALYSIS (ALL CITIES/datasets)
    // ==========================================
    // Create three separate array lists, one for each city
    ArrayList cityA_Array, cityB_Array, cityC_Array;
    
    // --- CITY A ---
    std::cout << "\n=== CITY A (METROPOLITAN) CARBON ANALYSIS ===\n";
    dataBot.loadToArray("dataset1-cityA.csv", cityA_Array); // Load the data from the file
    std::cout << "GRAND TOTAL CITY A EMISSIONS: " << cityA_Array.calculateTotalCityEmissions() << " kg CO2\n";
    
    // Runnnig the analytics for each specific age group asked by the assignment
    cityA_Array.analyzeAgeGroup(6, 17, "Children & Teenagers");
    cityA_Array.analyzeAgeGroup(18, 25, "University Students / Young Adults");
    cityA_Array.analyzeAgeGroup(26, 45, "Working Adults (Early Career)");
    cityA_Array.analyzeAgeGroup(46, 60, "Working Adults (Late Career)");
    cityA_Array.analyzeAgeGroup(61, 100, "Senior Citizens / Retirees");

    // --- CITY B ---
    std::cout << "\n=== CITY B (UNIVERSITY TOWN) CARBON ANALYSIS ===\n";
    dataBot.loadToArray("dataset2-cityB.csv", cityB_Array);
    std::cout << "GRAND TOTAL CITY B EMISSIONS: " << cityB_Array.calculateTotalCityEmissions() << " kg CO2\n";
    cityB_Array.analyzeAgeGroup(6, 17, "Children & Teenagers");
    cityB_Array.analyzeAgeGroup(18, 25, "University Students / Young Adults");
    cityB_Array.analyzeAgeGroup(26, 45, "Working Adults (Early Career)");
    cityB_Array.analyzeAgeGroup(46, 60, "Working Adults (Late Career)");
    cityB_Array.analyzeAgeGroup(61, 100, "Senior Citizens / Retirees");

    // --- CITY C ---
    std::cout << "\n=== CITY C (SUBURBAN/RURAL) CARBON ANALYSIS ===\n";
    dataBot.loadToArray("dataset3-cityC.csv", cityC_Array);
    std::cout << "GRAND TOTAL CITY C EMISSIONS: " << cityC_Array.calculateTotalCityEmissions() << " kg CO2\n";
    cityC_Array.analyzeAgeGroup(6, 17, "Children & Teenagers");
    cityC_Array.analyzeAgeGroup(18, 25, "University Students / Young Adults");
    cityC_Array.analyzeAgeGroup(26, 45, "Working Adults (Early Career)");
    cityC_Array.analyzeAgeGroup(46, 60, "Working Adults (Late Career)");
    cityC_Array.analyzeAgeGroup(61, 100, "Senior Citizens / Retirees");

    // ==========================================
    //   SORTING PERFORMANCE (ALL CITIES)
    // ==========================================
    std::cout << "\n=== SORTING PERFORMANCE EXPERIMENT (SECTION 6) ===\n";
    
    // using unsorted copies of the cities for Selection Sort. 
    // Need to do this cuz otherwise Selection Sort will mess up by running on an already-sorted list
    ArrayList cityA_Sel, cityB_Sel, cityC_Sel;
    dataBot.loadToArray("dataset1-cityA.csv", cityA_Sel);
    dataBot.loadToArray("dataset2-cityB.csv", cityB_Sel);
    dataBot.loadToArray("dataset3-cityC.csv", cityC_Sel);

    // --- BUBBLE SORT TIMERS ---
    // Start the stopwatch, run Bubble Sort, stop the stopwatch, and calculate the time taken
    auto sBA = std::chrono::high_resolution_clock::now(); cityA_Array.sortByAge(); auto eBA = std::chrono::high_resolution_clock::now();
    auto durBA = std::chrono::duration_cast<std::chrono::microseconds>(eBA - sBA);
    
    auto sBB = std::chrono::high_resolution_clock::now(); cityB_Array.sortByAge(); auto eBB = std::chrono::high_resolution_clock::now();
    auto durBB = std::chrono::duration_cast<std::chrono::microseconds>(eBB - sBB);
    
    auto sBC = std::chrono::high_resolution_clock::now(); cityC_Array.sortByAge(); auto eBC = std::chrono::high_resolution_clock::now();
    auto durBC = std::chrono::duration_cast<std::chrono::microseconds>(eBC - sBC);

    // --- SELECTION SORT TIMERS ---
    // Doing the  same stopwatch process for our unsorted Selection Sort lists
    auto sSA = std::chrono::high_resolution_clock::now(); cityA_Sel.selectionSortByAge(); auto eSA = std::chrono::high_resolution_clock::now();
    auto durSA = std::chrono::duration_cast<std::chrono::microseconds>(eSA - sSA);

    auto sSB = std::chrono::high_resolution_clock::now(); cityB_Sel.selectionSortByAge(); auto eSB = std::chrono::high_resolution_clock::now();
    auto durSB = std::chrono::duration_cast<std::chrono::microseconds>(eSB - sSB);

    auto sSC = std::chrono::high_resolution_clock::now(); cityC_Sel.selectionSortByAge(); auto eSC = std::chrono::high_resolution_clock::now();
    auto durSC = std::chrono::duration_cast<std::chrono::microseconds>(eSC - sSC);

    // Print the results in a nice text table. We calculate memory size dynamically using sizeof()
    std::cout << "Dataset \t| Algorithm \t| Execution Time (us) \t| Memory (Bytes)\n";
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "City A (200) \t| Bubble Sort \t| " << durBA.count() << " \t\t\t| " << sizeof(Resident) * 200 << "\n";
    std::cout << "City A (200) \t| Selection Sort| " << durSA.count() << " \t\t\t| " << sizeof(Resident) * 200 << "\n";
    std::cout << "City B (178) \t| Bubble Sort \t| " << durBB.count() << " \t\t\t| " << sizeof(Resident) * 178 << "\n";
    std::cout << "City B (178) \t| Selection Sort| " << durSB.count() << " \t\t\t| " << sizeof(Resident) * 178 << "\n";
    std::cout << "City C (122) \t| Bubble Sort \t| " << durBC.count() << " \t\t\t| " << sizeof(Resident) * 122 << "\n";
    std::cout << "City C (122) \t| Selection Sort| " << durSC.count() << " \t\t\t| " << sizeof(Resident) * 122 << "\n";
    std::cout << "--------------------------------------------------------------------------------\n";

    // ==========================================
    //   SEARCHING EXPERIMENTS (ALL CITIES)
    // ==========================================
    std::cout << "\n=== SEARCH EXPERIMENTS (SECTION 7) ===\n";
    double threshold = 15.0; 
    
    std::cout << "\n--- TEST 1: Linear Search (> 15 km) across all cities ---\n";
    // Using Linear Search to find anyone traveling more than 15 km
    auto sSearchA = std::chrono::high_resolution_clock::now(); cityA_Array.searchByDistance(threshold); auto eSearchA = std::chrono::high_resolution_clock::now();
    auto durSearchA = std::chrono::duration_cast<std::chrono::microseconds>(eSearchA - sSearchA);

    auto sSearchB = std::chrono::high_resolution_clock::now(); cityB_Array.searchByDistance(threshold); auto eSearchB = std::chrono::high_resolution_clock::now();
    auto durSearchB = std::chrono::duration_cast<std::chrono::microseconds>(eSearchB - sSearchB);

    auto sSearchC = std::chrono::high_resolution_clock::now(); cityC_Array.searchByDistance(threshold); auto eSearchC = std::chrono::high_resolution_clock::now();
    auto durSearchC = std::chrono::duration_cast<std::chrono::microseconds>(eSearchC - sSearchC);

    std::cout << "\n--- TEST 2: Binary Search (Target Age: 34) across all cities ---\n";
    // Our arrays are already sorted from the Bubble Sort test so Binary Search should be is safe to use here
    auto sBinA = std::chrono::high_resolution_clock::now(); cityA_Array.binarySearchByAge(34); auto eBinA = std::chrono::high_resolution_clock::now();
    auto durBinA = std::chrono::duration_cast<std::chrono::microseconds>(eBinA - sBinA);

    auto sBinB = std::chrono::high_resolution_clock::now(); cityB_Array.binarySearchByAge(34); auto eBinB = std::chrono::high_resolution_clock::now();
    auto durBinB = std::chrono::duration_cast<std::chrono::microseconds>(eBinB - sBinB);

    auto sBinC = std::chrono::high_resolution_clock::now(); cityC_Array.binarySearchByAge(34); auto eBinC = std::chrono::high_resolution_clock::now();
    auto durBinC = std::chrono::duration_cast<std::chrono::microseconds>(eBinC - sBinC);

    // Final summary table comparing the speeds
    std::cout << "\nSearch Performance Summary (ARRAY):\n";
    std::cout << "Dataset \t| Target \t| Linear Search (us) \t| Binary Search (us)\t| Memory (Bytes)\n";
    std::cout << "-------------------------------------------------------------------------------------------------\n";
    std::cout << "City A \t\t| >15km / Age 34| " << durSearchA.count() << " \t\t\t| " << durBinA.count() << " \t\t\t| " << sizeof(Resident) * 200 << "\n";
    std::cout << "City B \t\t| >15km / Age 34| " << durSearchB.count() << " \t\t\t| " << durBinB.count() << " \t\t\t| " << sizeof(Resident) * 178 << "\n";
    std::cout << "City C \t\t| >15km / Age 34| " << durSearchC.count() << " \t\t\t| " << durBinC.count() << " \t\t\t| " << sizeof(Resident) * 122 << "\n";
    std::cout << "-------------------------------------------------------------------------------------------------\n";

    return 0; // End of the array program
}