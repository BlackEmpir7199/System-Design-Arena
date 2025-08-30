#include <bits/stdc++.h>
using namespace std;


// helps to create a template where the order of exection stays same but the executing methods make change between objects
class CarMaker
{
public:
    virtual void attachEngine() = 0;
    // CarMaker(){};
    void makeBody()
    {
        cout << "Body has been attached" << endl;
    }
    void testCar(){
        cout << "Car is running" << endl;
    }
    void attachTiers(){
        cout << "Tiers are attached" << endl;
    }
    void dispatchCar(){
        cout << "Car Dispactched successfully" << endl;
    }

    // the template method
    void assembleCar(){
        makeBody();
        attachEngine();
        attachTiers();
        testCar();
        dispatchCar();
    }
};

class ElectricCar : public CarMaker{
    public:
        ElectricCar(){
            cout << "Electric car has been created" << endl;
        }
        void attachEngine() override{
            cout << "Attached electric engine" << endl;
        }
};

class PetrolCar : public CarMaker{
    public:
        PetrolCar(){
            cout << "Petrol car has been created" << endl;
        }
        void attachEngine() override{
            cout << "Attached petrol engine" << endl;
        }
};

int main()
{
    ElectricCar ec;

    ec.assembleCar();

    PetrolCar pc;

    pc.assembleCar();

    return 0;
}