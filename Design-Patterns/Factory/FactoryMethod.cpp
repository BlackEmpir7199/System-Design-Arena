#include <iostream>
#include <string>

// Step 1: Product Interface (Abstract Base Class)
class Vehicle {
public:
    virtual ~Vehicle() = default;  // Virtual destructor
    virtual std::string describe() const = 0;  // Pure virtual method
};

// Step 2: Concrete Products
class Car : public Vehicle {
public:
    std::string describe() const override {
        return "Car: 4 wheels, seats 5 people, fuel-efficient.";
    }
};

class Bike : public Vehicle {
public:
    std::string describe() const override {
        return "Bike: 2 wheels, eco-friendly, great for cities.";
    }
};

class Truck : public Vehicle {
public:
    std::string describe() const override {
        return "Truck: 6 wheels, heavy cargo capacity, diesel-powered.";
    }
};

// Step 3: Creator (Abstract Factory)
class VehicleFactory {
public:
    virtual ~VehicleFactory() = default;
    virtual Vehicle* createVehicle() const = 0;  // Factory method (pure virtual)

    void manufactureAndTest() const {
        Vehicle* v = createVehicle();
        std::cout << "Manufacturing: " << v->describe() << std::endl;
        delete v;  
    }
};

// Step 4: Concrete Creators
class CarFactory : public VehicleFactory {
public:
    Vehicle* createVehicle() const override {
        return new Car();
    }
};

class BikeFactory : public VehicleFactory {
public:
    Vehicle* createVehicle() const override {
        return new Bike();
    }
};

class TruckFactory : public VehicleFactory {
public:
    Vehicle* createVehicle() const override {
        return new Truck();
    }
};

// Step 5: Usage in main (Client Code)
int main() {
    // Client chooses factories
    VehicleFactory* carFactory = new CarFactory();
    VehicleFactory* bikeFactory = new BikeFactory();
    VehicleFactory* truckFactory = new TruckFactory();

    // Use factories to create and describe vehicles
    carFactory->manufactureAndTest();
    bikeFactory->manufactureAndTest();
    truckFactory->manufactureAndTest();

    // Clean up
    delete carFactory;
    delete bikeFactory;
    delete truckFactory;

    return 0;
}
