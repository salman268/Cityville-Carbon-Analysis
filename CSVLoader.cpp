#include "CSVLoader.hpp"
#include <fstream>  // fstream = File Stream (Allows us to open and read files)
#include <sstream>  // sstream = String Stream (Allows us to chop strings up)
#include <iostream> // For printing error messages

// Function to load CSV into our custom Array
void CSVLoader::loadToArray(std::string filename, ArrayList& list) {
    
    // 1. Open the file
    std::ifstream file(filename);
    
    // Safety check: Did the file actually open?
    if (!file.is_open()) {
        std::cout << "Error: Could not open the file " << filename << "\n";
        return; // Stop the bot
    }

    std::string line;
    
    // 2. Skip the first row (The Header)
    
    std::getline(file, line); 

    // 3. Loop through every other line in the file until the end
    while (std::getline(file, line)) {
        
        std::stringstream ss(line); // Turn the line into a stream we can chop up
        std::string dataPiece;
        Resident newResident;
        
        // 4. Chop by commas (',') and store in our Resident struct
        
        // Get Resident ID (String)
        std::getline(ss, dataPiece, ',');
        newResident.residentID = dataPiece;

        // Get Age (Convert String to Integer using stoi)
        std::getline(ss, dataPiece, ',');
        newResident.age = std::stoi(dataPiece);

        // Get Mode of Transport (String)
        std::getline(ss, dataPiece, ',');
        newResident.modeOfTransport = dataPiece;

        // Get Daily Distance (Convert String to Double using stod)
        std::getline(ss, dataPiece, ',');
        newResident.dailyDistance = std::stod(dataPiece);

        // Get Carbon Emission Factor (Convert String to Double)
        std::getline(ss, dataPiece, ',');
        newResident.carbonEmissionFactor = std::stod(dataPiece);

        // Get Average Days Per Month (Convert String to Integer)
        std::getline(ss, dataPiece, ',');
        newResident.averageDayPerMonth = std::stoi(dataPiece);

        // 5. Add this fully packaged Resident into   Array 
        list.addResident(newResident);
    }

    file.close(); // Close the file when done  
}

// Function to load CSV into our custom Linked List
 
void CSVLoader::loadToLinkedList(std::string filename, LinkedList& list) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open the file " << filename << "\n";
        return;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string dataPiece;
        Resident newResident;
        
        std::getline(ss, dataPiece, ',');
        newResident.residentID = dataPiece;

        std::getline(ss, dataPiece, ',');
        newResident.age = std::stoi(dataPiece);

        std::getline(ss, dataPiece, ',');
        newResident.modeOfTransport = dataPiece;

        std::getline(ss, dataPiece, ',');
        newResident.dailyDistance = std::stod(dataPiece);

        std::getline(ss, dataPiece, ',');
        newResident.carbonEmissionFactor = std::stod(dataPiece);

        std::getline(ss, dataPiece, ',');
        newResident.averageDayPerMonth = std::stoi(dataPiece);

        // Add to our Linked List
        list.addResident(newResident);
    }
    file.close();
}
 