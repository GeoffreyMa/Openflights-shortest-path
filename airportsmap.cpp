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
            //std::cout << line << std::endl;
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
    if (ss.get(c) && c == 32){
        getline(ss, temp, ',');
        result += temp;
    }
    return result;
}