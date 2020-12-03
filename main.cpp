
#include "airportsmap.h"
#include <iostream>

int main (int argc, const char * argv[]) {
    std::string airport_file = argv[1];
    AirportsMap a_map(airport_file);
    return 0;
}