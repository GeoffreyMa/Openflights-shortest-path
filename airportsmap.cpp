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
            double distance = getDis(stoi(ID1), stoi(ID2)); // calculate the distance between two airport.
            if (g_.vertexExists(ID1) == false){
                g_.insertVertex(ID1);
            }
            if (g_.vertexExists(ID2) == false){
                g_.insertVertex(ID2);
            }

            if (g_.edgeExists(ID1, ID2) == false){
                g_.insertEdge(ID1, ID2);
                g_.setEdgeWeight(ID1, ID2, distance); // get distance for weight. weight存放了 vertex之间的距离
                if (airlineID != "\\N")  {
                    g_.setEdgeLabel(ID1, ID2, airlineID);
                }
                
            }
        }
    }
}

// the shortest path is represented by a vector of variable type int
vector<pair<int, int>> AirportsMap::dijkstra(int startID){
    vector<pair<int, int>> table;
    vector<double> shortestDis;
    vector<bool> visited;
    string start = to_string(startID);  
    //string dest = to_string(destID);
    if (g_.vertexExists(start) == false){
        return table;
    }
    // set table, visited, shortestDis vectors
    for (int i = 0; i <= airports.size(); i++){
        table.push_back(pair<int, int> (i, 0));//////////cehcccckccccccccccckkkkkkkkkkk
        visited[i] = false;
        shortestDis[i] = 32767;
        if (i == startID){
            visited[i] = true;
        }
    }
    shortestDis[startID] = 0;

    // set knownmin to startID
    //--------------------------------------------------晚上写的 帮忙check一下谢啦w(ﾟДﾟ)w， 不一定对ooooooooooooo；两个loop应该可以精简一下但是我懒得弄了
    map<int, int> mapTable; // creatd a map for returning all the vertex and previous vertex;这里我用map存了路径 因为我在想如果输入一个起始的点不一定和整个graph连接？？ 不太确定；
    mapTable[startID] = 0; // initilize the previous vertex For startID；
    queue<int> q;
    q.push(startID);
    while(!q.empty()) {
        int tempID  = q.front(); //current visiting ID;
        q.pop();
        vector<Vertex> IDs = g_.getAdjacent(to_string(tempID));
        for (Vertex lookup: IDs) {
        if (shortestDis[tempID] + g_.getEdgeWeight(to_string(tempID), lookup) < shortestDis[stoi(lookup)] && !visited[stoi(lookup)]) {
            shortestDis[stoi(lookup)] = shortestDis[tempID] + g_.getEdgeWeight(to_string(tempID), lookup); //update shortest path
            mapTable[stoi(lookup)] = tempID; //update previous vertex;
            }

        }



        vector<Vertex> adjIDs = g_.getAdjacent(to_string(tempID)); //current vertex周围所有的vertices；
        double mindis = shortestDis[stoi(adjIDs[0])]; //initialize 最小距离
        int nextVertex = -1; //initialize 下一个visited的vertex；
        for (int i = 0; i < adjIDs.size(); i++) {
            if (shortestDis[stoi(adjIDs[i])] <= mindis && !visited[stoi(adjIDs[i])]) { //找到最小距离的vertex 并且没有visited过；
                mindis = shortestDis[stoi(adjIDs[i])]; //有可能出现第一个最短但是是visited过的现象， 所以check <= mindis;
                nextVertex = stoi(adjIDs[i]);
            }
        }
        if (nextVertex != -1) { //
            visited[nextVertex] = true;
            q.push(nextVertex);
        }
    }
    //最后return mapTable；
//-----------------------------------------------------------------------------------------------------------------------------------------以上


    int knownmin = startID;

    while (knownmin != 0){
        vector<Vertex> v = g_.getAdjacent(to_string(knownmin));
        for (int i = 0; i < v.size(); i++){
            int weight = g_.getEdgeWeight(to_string(knownmin), v[i]);
            
        }
        knownmin = 0;
    }

    
    return table;
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
    traversal_.clear();
    }
    visited.resize(airports.size(), false);
    DFSHelper(startID, visited);
}


//getter function
Graph AirportsMap::getGraph() {
    return g_;
}

double AirportsMap::getDis(int startID, int destID) { //stoi会把-的string convert成 -int吗 答案：会； ok
// 地球是个圆圈 convert latlng 需要check经度 180 -180        纬度没差 90-90
    pair<double, double> pair1 = airports.find(startID)->second.getLatlng();
    pair<double, double> pair2 = airports.find(destID)->second.getLatlng();
    double lat1 = pair1.first;
    double lat2 = pair2.first;
    double latdiff = 0;
    if (lat1 * lat2 >= 0) {
        latdiff = lat1 - lat2;
    } else {
       latdiff =  min(abs(lat1 - lat2), 360 - abs(lat1-lat2));
    }
    double dis = latdiff * latdiff + (pair1.second - pair2.second)*(pair1.second - pair2.second);
    dis  = sqrt(dis);
    return dis;
}