#include <bits/stdc++.h>
using namespace std;

// DIP says that a high lvl class should not depend on low lvl class
// high lvl - application
// low lvl - sqlDB, mongoDB

// code reusability can also be brought
class SqlDB
{
public:
    void save()
    {
        cout << "data saved to SQL db" << endl;
    }
};

class MongoDB
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
    SqlDB sql;
    MongoDB mongo;

public:
    Application() {}

    void saveDataToSql()
    {
        sql.save();
    }

    void saveDataToMongo()
    {
        mongo.save();
    }
};

int main()
{

    Application ap;
    ap.saveDataToMongo();
    ap.saveDataToSql();

    return 0;
}