#include "airportsmap.h"
#include <iostream>

int main (int argc, const char * argv[]) {
    if (argc < 3){
        std::cout << "Default" << std::endl;
        AirportsMap a_map("data/airports.txt");
        a_map.map_routes("data/routes.txt");
        return 0;
    }
    std::string airport_file = argv[1];
    AirportsMap a_map(airport_file);
    std::string route_file = argv[2];
    a_map.map_routes(route_file);
    return 0;
}