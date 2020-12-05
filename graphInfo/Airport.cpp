#include "Airport.h"

#include <utility>
#include <string>


namespace graphInfo {
    Airport::Airport() : 
      latlng_({0,0}), name_(""), id_(0) {

    }

    Airport::Airport(std::pair<double, double> latlng, std::string name, int id) : 
      latlng_(latlng), name_(name), id_(id) {
    }

    std::pair<double, double> Airport::getLatlng() const{
        return latlng_;
    }

    std::string Airport::getName() const{
        return name_;
    }

    int Airport::getID() const{
        return id_;
    }

    bool Airport::operator!= (Airport const & other) const {
        return !(*this == other);
    }

    bool Airport::operator== (Airport const & other) const {
        return this->getID() == other.getID();
    }
}