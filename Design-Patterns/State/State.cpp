#include <iostream>
using namespace std;

// Forward declaration of VendingMachine
class VendingMachine;

// Abstract state
class VendingMachineState
{
public:
    virtual void insertCoin(VendingMachine *machine) = 0;
    virtual void selectItem(VendingMachine *machine) = 0;
    virtual void dispense(VendingMachine *machine) = 0;
    virtual void returnCoin(VendingMachine *machine) = 0;
    virtual string getName() = 0;
    virtual ~VendingMachineState() = default;
};

// Concrete states
class NoMoneyState : public VendingMachineState
{
public:
    void insertCoin(VendingMachine *machine) override;
    void selectItem(VendingMachine *machine) override;
    void dispense(VendingMachine *machine) override;
    void returnCoin(VendingMachine *machine) override;
    string getName() override;
};

class HasMoneyState : public VendingMachineState
{
public:
    void insertCoin(VendingMachine *machine) override;
    void selectItem(VendingMachine *machine) override;
    void dispense(VendingMachine *machine) override;
    void returnCoin(VendingMachine *machine) override;
    string getName() override;
};

class DispensingState : public VendingMachineState
{
public:
    void insertCoin(VendingMachine *machine) override;
    void selectItem(VendingMachine *machine) override;
    void dispense(VendingMachine *machine) override;
    void returnCoin(VendingMachine *machine) override;
    string getName() override;
};

class OutOfStockState : public VendingMachineState
{
public:
    void insertCoin(VendingMachine *machine) override;
    void selectItem(VendingMachine *machine) override;
    void dispense(VendingMachine *machine) override;
    void returnCoin(VendingMachine *machine) override;
    string getName() override;
};

// Context
class VendingMachine
{
private:
    VendingMachineState *state;
    int inventory;

public:
    VendingMachine(int inv);
    ~VendingMachine();

    void insertCoin();
    void selectItem();
    void dispense();
    void returnCoin();

    void setState(VendingMachineState *newState);
    int getInventory();
    void decreaseInventory();
};

// Implementations of concrete state methods
void NoMoneyState::insertCoin(VendingMachine *machine)
{
    cout << "Money inserted.\n";
    machine->setState(new HasMoneyState());
}

void NoMoneyState::selectItem(VendingMachine *machine)
{
    cout << "Error: Insert money first.\n";
}

void NoMoneyState::dispense(VendingMachine *machine)
{
    cout << "Error: Insert money and select item first.\n";
}

void NoMoneyState::returnCoin(VendingMachine *machine)
{
    cout << "Error: No money to return.\n";
}

string NoMoneyState::getName()
{
    return "NoMoneyState";
}

void HasMoneyState::insertCoin(VendingMachine *machine)
{
    cout << "Error: Money already inserted.\n";
}

void HasMoneyState::selectItem(VendingMachine *machine)
{
    cout << "Item selected.\n";
    machine->setState(new DispensingState());
}

void HasMoneyState::dispense(VendingMachine *machine)
{
    cout << "Error: Select item first.\n";
}

void HasMoneyState::returnCoin(VendingMachine *machine)
{
    cout << "Money returned.\n";
    machine->setState(new NoMoneyState());
}

string HasMoneyState::getName()
{
    return "HasMoneyState";
}

void DispensingState::insertCoin(VendingMachine *machine)
{
    cout << "Error: Dispensing in progress.\n";
}

void DispensingState::selectItem(VendingMachine *machine)
{
    cout << "Error: Dispensing in progress.\n";
}

void DispensingState::dispense(VendingMachine *machine)
{
    if (machine->getInventory() > 0)
    {
        cout << "Dispensing item.\n";
        machine->decreaseInventory();
        if (machine->getInventory() > 0)
        {
            machine->setState(new NoMoneyState());
        }
        else
        {
            machine->setState(new OutOfStockState());
        }
    }
    else
    {
        cout << "Error: Product out of stock.\n";
        machine->setState(new OutOfStockState());
    }
}

void DispensingState::returnCoin(VendingMachine *machine)
{
    cout << "Error: Dispensing in progress.\n";
}

string DispensingState::getName()
{
    return "DispensingState";
}

void OutOfStockState::insertCoin(VendingMachine *machine)
{
    cout << "Error: Out of stock. Money returned.\n";
}

void OutOfStockState::selectItem(VendingMachine *machine)
{
    cout << "Error: Out of stock.\n";
}

void OutOfStockState::dispense(VendingMachine *machine)
{
    cout << "Error: Out of stock.\n";
}

void OutOfStockState::returnCoin(VendingMachine *machine)
{
    cout << "No money to return (out of stock).\n";
}

string OutOfStockState::getName()
{
    return "OutOfStockState";
}

// VendingMachine methods
VendingMachine::VendingMachine(int inv)
{
    inventory = inv;
    if (inventory > 0)
    {
        state = new NoMoneyState();
    }
    else
    {
        state = new OutOfStockState();
    }
}

VendingMachine::~VendingMachine()
{
    delete state;
}

void VendingMachine::insertCoin()
{
    state->insertCoin(this);
}

void VendingMachine::selectItem()
{
    state->selectItem(this);
}

void VendingMachine::dispense()
{
    state->dispense(this);
}

void VendingMachine::returnCoin()
{
    state->returnCoin(this);
}

void VendingMachine::setState(VendingMachineState *newState)
{
    cout << "State Transition: " << state->getName() << " -> " << newState->getName() << endl;
    delete state;
    state = newState;
}

int VendingMachine::getInventory()
{
    return inventory;
}

void VendingMachine::decreaseInventory()
{
    inventory--;
}

int main()
{
    VendingMachine machine(2);
    machine.insertCoin();
    machine.selectItem();
    machine.dispense();
    machine.insertCoin();
    machine.selectItem();
    machine.dispense();
    machine.insertCoin();
    return 0;
}
