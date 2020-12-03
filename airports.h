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
        string rmvcomma(stringstream & ss, string result, string temp);

    private:
        vector<pair<pair<double, double>, unsigned>> airportmap;
 };
