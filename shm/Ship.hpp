#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Warehouse.hpp"

class Cargo;

class Ship : public Warehouse {
public:
    Ship() = default;
    Ship(CargoVec cargovec, size_t capacity, size_t maxCrew, size_t speed, const std::string& name, const size_t id);
    Ship(size_t maxCrew, size_t speed, size_t id);
 
    void setName(const std::string& name);
 
    Ship& operator-=(size_t num);
    Ship& operator+=(size_t num);
 
    size_t getCapacity() const;  
    size_t getMaxCrew() const;   
    size_t getSpeed() const;   
    const std::string& getName() const;  
    size_t getId() const;
     
private:
    size_t capacity_ = 0;
    size_t maxCrew_ = 0;
    size_t crew_ = 0;
    size_t speed_ = 0;
    std::string name_ = "";
    size_t id_ = -1;
};
