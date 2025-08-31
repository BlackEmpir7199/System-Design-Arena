#include <iostream>
using namespace std;

// product
class Computer
{
private:
    string cpu_;
    string gpu_;
    string ram_;
    string ssd_;

public:
    // should not have a constructor
    void addCPU(string cpu)
    {
        cpu_ = cpu;
    }

    void addGPU(string gpu)
    {
        gpu_ = gpu;
    }

    void addRAM(string ram)
    {
        ram_ = ram;
    }

    void addSSD(string ssd)
    {
        ssd_ = ssd;
    }

    void display()
    {
        cout << "RAM : " << ram_ << endl;
        cout << "CPU : " << cpu_ << endl;
        cout << "GPU : " << (gpu_.empty() ? "None" : gpu_) << endl;
        cout << "SSD : " << ssd_ << endl;
    }
};

// builder interface
class ComputerBuilder
{
public:
    virtual void buildCPU(string cpu) = 0;
    virtual void buildGPU(string gpu) = 0;
    virtual void buildSSD(string ssd) = 0;
    virtual void buildRAM(string ram) = 0;
    virtual Computer getBuild() = 0;
    virtual ~ComputerBuilder() = default;
};

// concrete builders
class GamingPCBuilder : public ComputerBuilder
{
private:
    Computer computer_;

public:
    GamingPCBuilder()
    {
        computer_ = Computer();
    }
    void buildCPU(string cpu)
    {
        computer_.addCPU(cpu);
    }
    void buildGPU(string gpu)
    {
        computer_.addGPU(gpu);
    }
    void buildSSD(string sdd)
    {
        computer_.addSSD(sdd);
    }
    void buildRAM(string ram)
    {
        computer_.addRAM(ram);
    }
    Computer getBuild()
    {
        return computer_;
    }
};

class DesktopPCBuilder : public ComputerBuilder
{
private:
    Computer computer_;

public:
    DesktopPCBuilder()
    {
        computer_ = Computer();
    }
    void buildCPU(string cpu)
    {
        computer_.addCPU(cpu);
    }
    void buildGPU(string gpu)
    {
        computer_.addGPU(gpu);
    }
    void buildSSD(string sdd)
    {
        computer_.addSSD(sdd);
    }
    void buildRAM(string ram)
    {
        computer_.addRAM(ram);
    }
    Computer getBuild()
    {
        return computer_;
    }
};

// the director
class ComputerAssembler
{
public:
    Computer assemblePC()
    {
        ComputerBuilder *builder = nullptr;
        int choice;
        cout << "Enter the type of comp you want to build : " << endl;
        cout << "1. Desktop " << endl;
        cout << "2. Gaming " << endl;
        cin >> choice;

        if (choice == 1)
            builder = new DesktopPCBuilder();
        else if (choice == 2)
            builder = new GamingPCBuilder();
        else
            throw logic_error("Invalid option entered");

        builder->buildCPU("Intel i7");
        builder->buildSSD("crucial nvme 512gb");
        builder->buildRAM("crucial 16gb");
        if (choice == 2)
            builder->buildGPU("Nvdia 3060rtx");
        else
            builder->buildGPU("");

        return builder->getBuild();
        delete builder;
        builder = nullptr;
    }
};

int main()
{
    ComputerAssembler assembler;
    Computer newComp = assembler.assemblePC();
    newComp.display();
    return 0;
}