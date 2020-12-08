#include "airportsmap.h"
#include <iostream>

int main (int argc, const char * argv[]) {
    if (argc < 3){
        std::cout << "Default" << std::endl;
       /* map<int, int> test;
        test[0] = 1;
        test[5] = 3;
        for (size_t i = 0; i< test.size(); i++) {
            cout<< i << "is:"<< test[i] << endl;
        }*/
        AirportsMap a_map("data/airports.txt");
        a_map.map_routes("data/routes.txt");
        a_map.dijkstra(3682);
        return 0;
    }
    std::string airport_file = argv[1];
    AirportsMap a_map(airport_file);
    std::string route_file = argv[2];
    a_map.map_routes(route_file);
    
    return 0;
}