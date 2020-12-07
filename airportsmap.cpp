#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <map>

#include "airportsmap.h"
#include "graph.h"
#include "graphInfo/Airport.h"

using namespace std;

AirportsMap::AirportsMap() :
    g_(Graph(true, true)) {
    airports = std::map<int, graphInfo::Airport>();
}

AirportsMap::AirportsMap(string txt) : 
    g_(Graph(true, true)){
    airports = std::map<int, graphInfo::Airport>();
    airport_reader(txt);  
}

void AirportsMap::airport_reader(string txt) {
    ifstream inFile(txt);
    if (inFile.is_open()){
        string line;
        while (getline(inFile, line)){
            stringstream ss(line);
            /*
                airportID / name / city / county / IATA / ICAO / latitude / longitude /
                altitude / timezone / DST / tz / type / source
            */
            string ID, name, latitude, longitude, temp;
            /* 
                read ID, name, latitude, longitude of each airport, convert them to 
                double (latitude and longitude) or unsigned (ID), then push them to
                airportmap
            */
            getline(ss, ID, ',');
            getline(ss, name, ',');
            name = rmvcomma(ss, name, temp);
            // skip to latitude
            for (int i = 0; i < 4; i++){
                getline(ss, temp, ',');
                rmvcomma(ss, temp, temp);
            }
            getline(ss, latitude, ',');
            getline(ss, longitude, ',');
            for (int i = 0; i < 6; i++){
                getline(ss, temp, ',');
            }
            // convert
            double lat = stod(latitude, NULL);
            double lon = stod(longitude, NULL);
            int ID1 = stoul(ID, NULL, 10);
            pair<double, double> latlng(lat,lon);
            graphInfo::Airport cur_airport(latlng, name, ID1);

            //add the airport to the map
            if (airports.empty()) {
                airports[ID1] = cur_airport;
            } else {
                map<int, graphInfo::Airport>::iterator lookup = airports.find(ID1);
                if (lookup == airports.end()) {
                    airports[ID1] = cur_airport;
                }
            }
        }
    }    
}

/* 
    We are using airports.txt as a comma separated value file, but there are some entries
    with commas in them. Commas within entries are followed by a space instead of by a quotation
    mark. This function catches commas followed by spaces and processes them accordingly.
*/
string AirportsMap::rmvcomma(stringstream & ss, string result, string temp){
    char c;
    ss.get(c);
    if (c == 32){
        getline(ss, temp, ',');
        result += temp;
    } else {
        ss.unget();
    }
    return result;
}

void AirportsMap::map_routes(string txt){
    // initialize graph
    ifstream inFile(txt);
    if (inFile.is_open()){
        string line;
        while (getline(inFile, line)){
            stringstream ss(line);
            string temp, airlineID, ID1, ID2;
            /*  
                - / AirlineID / - / ID1 / - / ID2 / - / - / -
                9 in one line, take 4th and 6th
            */
            for (int i = 0; i < 9; i++){
                if (i == 1) {
                    getline(ss, airlineID, ',');
                } else if (i == 3){
                    getline(ss, ID1, ',');
                } else if (i == 5){
                    getline(ss, ID2, ',');
                } else {
                    getline(ss, temp, ',');
                }
            }
            /* 
                some routes are missing starting IDs or destination IDs
                we skip these routes
            */
            if (ID1 == "\\N" || ID2 == "\\N"){
                continue;
            }
            
            if (g_.vertexExists(ID1) == false){
                g_.insertVertex(ID1);
            }
            if (g_.vertexExists(ID2) == false){
                g_.insertVertex(ID2);
            }

            if (g_.edgeExists(ID1, ID2) == false){
                g_.insertEdge(ID1, ID2);
                g_.setEdgeWeight(ID1, ID2, 0);
                if (airlineID != "\\N")  {
                    g_.setEdgeLabel(ID1, ID2, airlineID);
                }
                
            }
        }
    }
}

// the shortest path is represented by a vector of variable type int
vector<int> AirportsMap::dijkstra(int startID, int destID){
    string start = to_string(startID);
    string dest = to_string(destID);
    vector<int> path;
    if (g_.vertexExists(start) == false || g_.vertexExists(dest) == false){
        return path;
    }
    path.push_back(startID);
    return path;
}

// DFS traversal helper
void AirportsMap::DFSHelper(int startID, vector<bool>& visited) { // call visited with reference?? checkcheckcheckcheck here.
    visited[startID] = true;
    traversal_.push_back(to_string(startID)); // Since we want to traversal vertices, I convert the int type to Vertex type for convinence.
    vector<Vertex>::iterator it;
    for (it = g_.getAdjacent(to_string(startID)).begin(); it != g_.getAdjacent(to_string(startID)).end(); ++it) {
        Vertex at = *it;
        int atNum = stoi(at); // checkcheckcheck here;  not sure if this conversion is right. 
        if (!visited[atNum]) { // if unvisited, recursive call.
            DFSHelper(atNum, visited);
        }
    }
}

// DFS main function
void AirportsMap::DFS(int startID) {
    vector<bool> visited;
    if (traversal_.size() != 0) {
    traversal_.erase(traversal_.begin(), traversal_.end());
    }
    visited.resize(airports.size(), false);
    DFSHelper(startID, visited);
}


//getter function
Graph AirportsMap::getGraph() {
    return g_;
}