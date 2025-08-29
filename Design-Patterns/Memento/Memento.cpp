#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

class Memento;

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
};


class Memento{
    private:
        unordered_map<string,string> state;
    public:
        Memento(unordered_map<string,string> dump){
            state=dump;
        }   
        
        unordered_map<string,string> getState(){
            return state;
        }
        
        void setState(unordered_map<string,string> dump){
            state=dump;
        }
};


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

    tm.

    return 0;
}