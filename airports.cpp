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
            for (int i = 0; i < 4; i++){
                getline(ss, temp, ',');
            }
            getline(ss, latitude, ',');
            getline(ss, longitude, ',');
            for (int i = 0; i < 6; i++){
                getline(ss, temp, ',');
            }
            // convert
            double lat = stod(latitude, NULL);
            double lon = stod(longitude, NULL);
            unsigned ID1 = stoul(ID, NULL, 10);
            airportmap.push_back(pair<pair<double, double>(lat, lon), unsigned ID1>);
        }
    }

}