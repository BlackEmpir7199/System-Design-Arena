#include <bits/stdc++.h>
using namespace std;

// when u find a class needs to be open for extension but closed for modification , use open closed principle (abstraction + inheritance + polymorphism)
class DbHandler
{
public:
    virtual void save() = 0;
};

// separate class for mongo <- inherit from dbhandler
class MongoDbHandler : public DbHandler
{
public:
    MongoDbHandler() {}
    void save()
    {
        cout << "saved to mongo db" << endl;
    }
};

// separate class for sql <- inherit from dbhandler
class SqlDbHandler : public DbHandler
{
public:
    SqlDbHandler() {}
    void save()
    {
        cout << "saved to sql db" << endl;
    }
};

int main()
{
    DbHandler *sql = new SqlDbHandler();
    DbHandler *mongo = new MongoDbHandler();

    sql->save();
    mongo->save();

    return 0;
}