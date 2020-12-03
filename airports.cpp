#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "airports.h"

using namespace std;

Airports::Airports(string txt){
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
            // get latitude / longitude
            getline(ss, latitude, ',');
            getline(ss, longitude, ',');
            // skip to next airport
            for (int i = 0; i < 6; i++){
                getline(ss, temp, ',');
            }
            // convert
            double lat = stod(latitude, NULL);
            double lon = stod(longitude, NULL);
            unsigned ID1 = stoul(ID, NULL, 10);
            pair<double, double> latlng(lat,lon);
            pair<pair<double, double>, unsigned> airport(latlng, ID1);
            airportmap.push_back(airport);
            // std::cout << airportmap[airportmap.size() - 1].second << " " << airportmap[airportmap.size() - 1].first.first << " " << airportmap[airportmap.size() - 1].first.second << std::endl;
        }
    }
}

/* 
    We are using airports.txt as a comma separated value file, but there are some entries
    with commas in them. Commas within entries are followed by a space instead of by a quotation
    mark. This function catches commas followed by spaces and processes them accordingly.
*/
string Airports::rmvcomma(stringstream & ss, string result, string temp){
    char c;
    if (ss.get(c) && c == 32){
        getline(ss, temp, ',');
        result += temp;
    }
    return result;
}