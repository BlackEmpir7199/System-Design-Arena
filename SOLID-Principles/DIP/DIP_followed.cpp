#include <bits/stdc++.h>
using namespace std;

// DIP says that a high lvl class should not depend on low lvl class
// high lvl - application
// low lvl - sqlDB, mongoDB

// code reusability can also be brought

class Database
{
public:
    virtual void save() = 0;
};

class SqlDB : public Database
{
public:
    void save()
    {
        cout << "data saved to SQL db" << endl;
    }
};

class MongoDB : public Database
{
public:
    void save()
    {
        cout << "data saved to Mongo db" << endl;
    }
};

// breaks Open - closed Principle : not extendible
class Application
{
private:
    Database *db;

public:
    Application() {}

    void saveDataToSql(SqlDB *sql)
    {
        db = sql;
        db->save();
    }

    void saveDataToMongo(MongoDB *mongo)
    {
        db = mongo;
        mongo->save();
    }
};

int main()
{

    Application ap;
    // method 1
    SqlDB *sql = new SqlDB();
    MongoDB *mongo = new MongoDB();

    ap.saveDataToSql(sql);
    ap.saveDataToMongo(mongo);

    // method 2
    SqlDB sql1;
    MongoDB mongo1;

    ap.saveDataToSql(&sql1);
    ap.saveDataToMongo(&mongo1);

    return 0;
}