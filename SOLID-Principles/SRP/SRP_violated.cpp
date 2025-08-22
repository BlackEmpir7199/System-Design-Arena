#include <bits/stdc++.h>

using namespace std;

// 1. class to represent the product
class Product
{
private:
    string name;
    int price;

public:
    Product(string name, int price)
    {
        this->name = name;
        this->price = price;
    }

    int getPrice(){
        return price;
    }
};

// 2. SRP violated cart handler , does more than 1 thing
class CartHandler
{
private:
    vector<Product *> items;
    int totalItems;
    int totalValue;

public:
    CartHandler(){
        this->totalItems=0;
        this->totalValue=0;
    }

    void addItems(Product *item){
        items.push_back(item);
        totalItems++;
        totalValue+=item->getPrice();
    }

    void removeItem(Product *item){
        auto idx = find(begin(items),end(items),item);
        items.erase(idx);
        totalValue-=item->getPrice();
        totalItems--;
    }

    vector<Product*> getItems(){
        return items;
    }

    void invoiceGenerate(){
        cout << "Total Items : " << totalItems << endl;
        cout << "Your total Bill is : " << totalValue << endl; 
    }

    void saveToDB(){
        cout << "Cart saved to DB";
    }


};

int main()
{

    CartHandler* cart = new CartHandler();
    cart->addItems(new Product("rice",100));
    cart->addItems(new Product("brinjal",40));
    cart->addItems(new Product("cucumber",20));
    cart->addItems(new Product("facewash",50));

    cart->invoiceGenerate();
    cart->saveToDB();


    return 0;
}