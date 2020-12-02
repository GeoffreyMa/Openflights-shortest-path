/**
 * @file Airports.h
 */

 #include <stdlib.h>
 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <vector>
 #include <utility>

 using namespace std;

 class Airports {
    public:
        Airports(string txt);

    private:
        vector<pair<pair<double, double>, unsigned>> airportmap;
 };
