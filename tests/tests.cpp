#define CATCH_CONFIG_MAIN
#include "../airportsmap.h"
#include "../graph.h"
#include "../edge.h"
//#include "../graphInfo/Airport.h"
#include "../catch/catch.hpp"

//using graphInfo::Airport;

TEST_CASE("Creates the correct vertices") {
    
    AirportsMap a_map("tests/testAirportBasic.txt");
    a_map.map_routes("tests/testRoutesBasic.txt");

    Graph g = a_map.getGraph();
    REQUIRE(g.getVertices().size() == 3);
    REQUIRE(g.vertexExists("1"));
}

