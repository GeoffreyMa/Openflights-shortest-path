
#include "airportsmap.h"
#include <iostream>

int main (int argc, const char * argv[]) {
    if (argc < 2){
        std::cout << "Missing arguments" << std::endl;
        return 0;
    }
    std::string airport_file = argv[1];
    AirportsMap a_map(airport_file);
    return 0;
}