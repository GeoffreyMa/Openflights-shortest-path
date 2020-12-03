/**
 * @file airportsmap.h
 */

 #pragma once

 #include <stdlib.h>
 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <vector>
 #include <utility>
 #include <map>

 #include "graph.h"
 #include "edge.h"
 #include "graphInfo/Airport.h"

 using namespace std;

 class AirportsMap {
    public:
        AirportsMap(string txt);
        AirportsMap();
        void map_routes(string txt);
        vector<int> dijkstra(int startID, int destID);

        void DFSHelper(int startID, vector<bool>& visited);
        void DFS(int startID);

    private:

        /*
        * The graph that represents each airport as a vertex and each route as an edge.
        */
        Graph g_;

        /*
        * A map that maps the ID of airports to the Airport object.
        */
        std::map<int, graphInfo::Airport> airports;


        /*
        * Helper functions that reads the airports file.
        * @param the name of the file to be read.
        */
        void airport_reader(string txt);
        string rmvcomma(stringstream & ss, string result, string temp);

        /**
         * DFS traversal, record the whole graph traversed.
        */
        vector<Vertex> traversal_;
 };
