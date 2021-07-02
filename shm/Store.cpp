#include "Store.hpp"

Response Store::buy(Cargo* cargo, size_t amount, Player* player) {
    if (!cargo) {
        return Response::lack_of_cargo;
    }
    if (!player) {
        return Response::lack_of_cargo;
    }
    if (!amount) {
        return Response::lack_of_cargo;
    }

    const auto& playerShip = player->getShip();
    if (!playerShip) {
        return Response::lack_of_cargo;
    }

    Cargo* soldPlayerCargo = nullptr;
    for (const auto& el : playerShip->getCargoVec()) {
        Cargo* currentCargo = el.get();

        if (*soldPlayerCargo == *cargo) {
            if (currentCargo->getAmount() < amount) {
                return Response::lack_of_cargo;
            }
            soldPlayerCargo = currentCargo;
        }
    }

    if (!soldPlayerCargo) {
        return Response::lack_of_cargo;
    }
    //Store have unlimited space and money

    //player sell all
    if (soldPlayerCargo->getAmount() == amount) {
        auto ownedCargo = soldPlayerCargo->split(amount);
        //playerShip->unload(soldPlayerCargo);
        auto moneyToPay = ownedCargo->getPrice() * ownedCargo->getAmount();
        //player->giveMoney(moneyToPay);

        load(std::move(ownedCargo));
        return Response::done;
    }

    //player sell less than all
    auto moneyToPay = soldPlayerCargo->getPrice() * amount;
    auto buyedCargoPart = soldPlayerCargo->split(amount);

    if (!buyedCargoPart) {
        return Response::lack_of_cargo;
    }
    //player->giveMoney(moneyToPay);

    load(std::move(buyedCargoPart));
    return Response::done;
}

Response Store::sell(Cargo* cargo, size_t amount, Player* player) {
    if (!cargo) {
        return Response::lack_of_cargo;
    }
    if (!player) {
        return Response::lack_of_space;
    }
    if (!amount) {
        return Response::lack_of_cargo;
    }

    const auto& playerShip = player->getShip();
    if (!playerShip) {
        return Response::lack_of_space;
    }

    //IMPORTANT: diferent meaning of space we got here !!!
    if (player->getAvailableSpace() < amount) {  // player dont have space for that cargo
        return Response::lack_of_space;
    }

    auto storeCargo = findCargoInStore(cargo);

    if (!storeCargo) {  //dont find cargo in store
        return Response::lack_of_cargo;
    }

    if (storeCargo->getAmount() > amount) {  //to much cargo needed
        return Response::lack_of_cargo;
    }

    auto moneyToPay = amount * storeCargo->getPrice();
    if (player->getMoney() < moneyToPay) {  //to expensive for player
        return Response::lack_of_money;
    }

    if (amount == storeCargo->getAmount()) {  //we sall all cargo - remove it from
        try {
            auto soldCargo = storeCargo->split(amount);
            unload(storeCargo);
        } catch (std::logic_error& err) {
            //cargo disapear?
        }
        //player->getShip()->load(soldCargo);
        return Response::done;
    }

    auto soldCargo = storeCargo->split(amount);
    //player->getShip()->load(soldCargo);
    return Response::done;
}

//load will take ownership of cargo
//1 - need not aleredy be its own
//2 - not nullptr
//3 - if have equal type of cargo only add amount
void Store::load(std::unique_ptr<Cargo> cargo) {
    if (!cargo) {
        return;
    }
    Cargo* storedCargo = findCargoInStore(cargo.get());
    if (!storedCargo) {
        for (auto& el : cargoVec_) {
            if (!el) {
                el = std::move(cargo);  //move cargo into empty cargo space
                return;
            }
        }
        cargoVec_.push_back(std::move(cargo));  //move cargo into vector
        return;
    }
    *storedCargo += cargo->getAmount();  //transfer amount into comperable cargo
    //here cargo will be destroyed
}

//ver A - unload will remove cargo
//1 - cargo pointer must exist in cargoVec_
//2 - will throw logic_error otherwise
void Store::unload(const Cargo* const cargo) {  //ver A
    if (!cargo) {
        return;
    }
    for (auto& el : cargoVec_) {
        if (el.get() == cargo) {  //equal pointers -> equal amount
            el.reset();
            //we leave empty cargo space in store here
            cargoVec_.erase(std::remove(begin(cargoVec_), end(cargoVec_), nullptr), end(cargoVec_));
            return;
        }
    }
    throw std::logic_error("Store: Not my Cargo!");
}

Cargo* Store::findCargoInStore(const Cargo* const exampleCargo) const {
    if (!exampleCargo) {
        return nullptr;
    }

    for (const auto& el : cargoVec_) {
        Cargo* targetCargo = el.get();
        if (targetCargo) {
            if (targetCargo == exampleCargo) {  //we dont want to compare same Cargo pointers
                return nullptr;
            }

            if (*targetCargo == *exampleCargo) {  //depend this means equality or comperable
                return targetCargo;
            }
        }
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& out, const Store& store) {
    for (const auto& el : store.cargoVec_) {
        if (el) {
            out << el->getName() << " || "
                << el->getAmount() << " || "
                << el->getPrice() << '\n';
        }
    }
    return out;
}