#include "Cargo.hpp"
#include "Ship.hpp"

Ship::Ship()
{}

Ship::Ship(CargoVec cargoVec, size_t capacity, size_t maxCrew, size_t speed, const std::string& name, size_t id)
    : Warehouse::Warehouse(std::move(cargoVec)), capacity_(capacity), maxCrew_(maxCrew), crew_(0), speed_(speed), name_(name), id_(id)
{}

Ship::Ship(size_t maxCrew, size_t speed,size_t id)
   : Warehouse::Warehouse(), capacity_(0), maxCrew_(maxCrew), crew_(0), speed_(speed), name_(""), id_(id)
{}

void Ship::setName(const std::string& name) { 
    name_ = name; 
}

Ship& Ship::operator-=(size_t num) {
    crew_ -= num;
    return *this;
}

Ship& Ship::operator+=(size_t num) {
    crew_ += num;
    return *this;
}

size_t Ship::getCapacity() const { 
    return capacity_; 
}

size_t Ship::getMaxCrew() const { 
    return maxCrew_; 
}

size_t Ship::getSpeed() const { 
    return speed_; 
}

const std::string& Ship::getName() const { 
    return name_; 
}

size_t Ship::getId() const { 
    return id_; 
}
