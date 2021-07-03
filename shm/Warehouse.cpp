#include <vector>
#include <algorithm>

#include "Warehouse.hpp"
#include "Cargo.hpp"


Warehouse::Warehouse() 
{}

Warehouse::Warehouse(CargoVec cargoVec) : cargoVec_(std::move(cargoVec))
{}

const Warehouse::CargoVec& Warehouse::getCargoVec() const {
       return cargoVec_;
}

void Warehouse::load(std::unique_ptr<Cargo> cargo) {
    if (!cargo) {
        return;
    }
    for (auto& cargoInStock : cargoVec_) {
        if (*cargoInStock == *cargo) {
            *cargoInStock += cargo->getAmount();
            return;
        }
    }
    cargoVec_.push_back(std::move(cargo));
}

void Warehouse::unload(Cargo* cargo) {
    if (!cargo) {
        return;
    }
    for (auto& cargoInStock : cargoVec_) {
        if (*cargoInStock == *cargo) {
            if (cargoInStock->getAmount() > cargo->getAmount()) {
                *cargoInStock -= cargo->getAmount();
                return;
            if (cargoInStock->getAmount() < cargo->getAmount()) {
                // to figureout how to inform player that he got less than expected
            }
            cargoVec_.erase(std::remove_if(cargoVec_.begin(), cargoVec_.end(),
                                        [&cargo](std::unique_ptr<Cargo>& cargoInStock) {
                                            return *cargo == *cargoInStock;
                                        }),
                            cargoVec_.end());
            return;
            }
        }
    }
}
