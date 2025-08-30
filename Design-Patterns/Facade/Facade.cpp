#include<iostream>
using namespace std;

class PowerSupply{
    public:
        void onSupply(){
            cout << "Power supply is on" << endl;
        }
};

class CoolingSystem{
    public:
        void startFans(){
            cout << "Fans started running" << endl;
        }
};

class CPU {
public:
    void initialize() {
        cout << "CPU: Initialization started..." << endl;
    }
};

class Memory {
public:
    void selfTest() {
        cout << "Memory: Self-test passed..." << endl;
    }
};

class HardDrive {
public:
    void spinUp() {
        cout << "Hard Drive: Spinning up..." << endl;
    }
};

class BIOS{
    public:
        void boot(CPU* cpu, Memory* mem){
            cout << "BIOS: boosting CPU and memory" << endl;
            cpu->initialize();
            mem->selfTest();
        }
};

class OperatingSystem {
public:
    void load() {
        cout << "Operating System: Loading into memory..." << endl;
    }
};


// the facade which does all the work and makes it simple and easy for the client following PLK
class ComputerFacade{
    private:
        PowerSupply ps;
        CoolingSystem cs;
        CPU cpu;
        Memory mem;
        BIOS bios;
        HardDrive hd;
        OperatingSystem os;
    
    public:
        void startComputer(){
            cout << "----- Starting Computer -----" << endl;
            ps.onSupply();
            cs.startFans();
            bios.boot(&cpu,&mem);
            hd.spinUp();
            os.load();
            cout << "Computer Booted Successfully!" << endl;
        }

};


int main(){

    ComputerFacade cf;

    cf.startComputer();

    return 0;
}