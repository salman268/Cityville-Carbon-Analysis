#ifndef CSVLOADER_HPP
#define CSVLOADER_HPP

#include <string>
#include "ArrayList.hpp"
#include "LinkedList.hpp"

//   creating a simple class to handle all our file loading   tasks.
class CSVLoader {
public:
    // We use '&' (Pass by Reference) so the bot fills up our real list  instead of creating a useless copy.
   
    void loadToArray(std::string filename, ArrayList& list);
    void loadToLinkedList(std::string filename, LinkedList& list);
};

#endif