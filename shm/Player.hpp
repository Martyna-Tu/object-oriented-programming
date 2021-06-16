#pragma once

#include <memory>

// Forward declaration, include Ship/Cargo class once they are ready
class Ship;
class Cargo;

class Player {
    std::unique_ptr<Ship> ship_;
    size_t money_;
    size_t availableSpace_;

    void calculateAvailableSpace();

public:
    Player(std::unique_ptr<Ship> ship, const size_t& money, const size_t& availableSpace);
    const std::unique_ptr<Ship>& getShip() const;
    size_t getMoney() const;
    size_t getAvailableSpace() const;
    size_t getSpeed() const;
    Cargo* getCargo(size_t index) const;
};