#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

// Memento - Stores database state snapshot
class Memento
{
private:
    unordered_map<string, string> state;

public:
    Memento(unordered_map<string, string> dump)
    {
        state = dump;
    }

    unordered_map<string, string> getState()
    {
        return state;
    }

    void setState(unordered_map<string, string> dump)
    {
        state = dump;
    }
};

// Originator - The database whose state we want to save/restore
class Database{
    private:
        unordered_map<string,string> mpp;
    public:
        Database(){

        }
        void create(string key, string val){
            mpp[key]=val;
        }

        void update(string key, string val){
            if(mpp.find(key)==mpp.end()) cout << "No such Key exist in db" << endl;
            mpp[key]=val;
            cout << "Update Successful: " << key << ":" << val << endl;
        }
        
        void remove(string key, string val){
            if(mpp.find(key)==mpp.end()) cout << "No such Key exist in db" << endl;
            mpp.erase(key);
            cout << "Remove Successful: " << key << ":" << val << endl;
        }

        Memento* createMemento(){
            return new Memento(mpp);
        }

        void restore(Memento* m){
            mpp = m->getState();
        }

        void printValues()
        {
            if (mpp.size() == 0)
                cout << "Nothing in DB" << endl;
            for (auto it : mpp)
            {
                cout << it.first << " : " << it.second << endl;
            }
        }
};

// Caretaker - Manages the memento (transaction manager)
class TransactionManager { 
    private:
        Memento* m;
    public:
        TransactionManager(){
            m = nullptr;
        }

        void beginTransaction(Database* db){
            cout << "----BEGIN------" << endl;
            if(m) {
                delete m;
                m = nullptr;
            }
            m = db->createMemento();
            cout << "New transaction has been created " << endl;
        }

        void commitTransaction(){
            cout << "----COMMIT------" << endl;
            if(m) {
                delete m;
                m = nullptr;
            }
            cout << "Committed transaction successfully" << endl;
        }

        void rollBackTransaction(Database* db){
            cout << "----ROLLBACK------" << endl;
            if(m){
                db->restore(m);
                delete m;
                m = nullptr;
                cout << "Roll Back has been done successfully" << endl;
            }
            else{
                cout << "No backup available" << endl;
            }
        }
};


int main(){

    Database db;
    TransactionManager tm;

    tm.beginTransaction(&db);
    db.create("fruit","orange");
    db.create("toy","horse");

    db.printValues();

    tm.commitTransaction();

    tm.beginTransaction(&db);
    db.create("car", "toyota");
    db.create("bike", "kawasaki");

    db.printValues();

    tm.rollBackTransaction(&db);

    db.printValues();

    return 0;
}