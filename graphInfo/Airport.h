#pragma once

#include <utility>
#include <string>

namespace graphInfo {
    class Airport {
        public:
            Airport();
            Airport(std::pair<double, double> latlng, std::string name, int id);

            //getter functions
            std::pair<double, double> getLatlng() const;
            std::string getName() const;
            int getID() const;

            //operator overload
            bool operator== (Airport const & other) const ;
            bool operator!= (Airport const & other) const ;


        private:
            std::pair<double, double> latlng_;
            std::string name_;
            int id_;
    };
    //std::ostream & operator<<(std::ostream & out, Airport const & pixel);
}
