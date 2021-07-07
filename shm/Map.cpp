#include "Map.hpp"
#include <algorithm>

constexpr auto defaultIslandsNumber = 10u;

Island::coordinateType generatePosition() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 10);

    return distrib(gen);
}

void Map::fillWithRandomIslands() {
    const size_t capacity = islandVec_.capacity();
    while (islandVec_.size() <= capacity) {
        auto posX = generatePosition();
        auto posY = generatePosition();
        Island::Coordinates newCoordinate(posX, posY);
        auto check = std::find_if(islandVec_.begin(), islandVec_.end(),
                                  [&newCoordinate](const Island& island) {
                                      return island.getPosition() == newCoordinate;
                                  });
        if (check == islandVec_.end()) {
            islandVec_.emplace_back(posX, posY);
        }
    }
}

Map::Map() {
    islandVec_.reserve(defaultIslandsNumber);
    fillWithRandomIslands();
}

const std::vector<Island>& Map::getIslandVec() const {
    return islandVec_;
}

Island* Map::getCurrentPosition() const {
    return currentPosition_;
}

Island* Map::getIsland(const Island::Coordinates& coordinate) {
    auto it = std::find_if(islandVec_.begin(), islandVec_.end(),
                                [&coordinate](const Island& island) {
                                    return island.getPosition() == coordinate;
                                });
    if (it != islandVec_.end()) {
        return &*it;
    } 
        return nullptr;
}