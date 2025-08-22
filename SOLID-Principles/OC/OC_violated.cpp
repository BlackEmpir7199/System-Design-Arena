#include <bits/stdc++.h>
using namespace std;

// the problem is, lets say in future i want to add saveToFirebase , then again i come here and rewrite this code , which means the code is not flexible to extension and open to modification
class DbHandler
{
public:
    DbHandler() {}

    void saveToSQL()
    {
        cout << "saved to sql" << endl;
    }

    void saveToMongoDb()
    {
        cout << "saved to mongo db" << endl;
    }
};

int main()
{
    DbHandler *db = new DbHandler();
    db->saveToMongoDb();
    db->saveToSQL();
    return 0;
}