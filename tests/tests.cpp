#define CATCH_CONFIG_MAIN
#include "../airportsmap.h"
#include "../graphInfo/Airport.h"
#include "../catch/catch.hpp"
#include "../graph.h"

TEST_CASE("testing") {
    AirportsMap a_map("testAirportBasic.txt");
    a_map.map_routes("testRoutesBasic.txt");

    Graph g = a_map.getGraph();
    REQUIRE(g.getVertices().size() == 3);
}

