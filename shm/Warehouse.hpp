#include <memory>

class Cargo; 

class Warehouse {
public:
    using CargoVec = std::vector<std::unique_ptr<Cargo>>;

    Warehouse();
    Warehouse(CargoVec cargoVec);

    const CargoVec& getCargoVec() const;

    void load(std::unique_ptr<Cargo>);
    void unload(Cargo*);

private:
    CargoVec cargoVec_ = {};
};


