#include <iostream>

class Toy
{
public:
    Toy(std::string _name) : name(_name) {};
    Toy() : name("SomeToy") {};

    Toy(Toy &oth)
    {
        this->name=oth.name;
    }
private:
    std::string name;
};

class shared_ptr_toy
{
private:
    Toy* obj;
    unsigned int* owners;
public:
    shared_ptr_toy()
    {
        obj = nullptr;
    }

    shared_ptr_toy(const shared_ptr_toy &oth)
    {
        obj=oth.obj;
        owners=oth.owners;
        (*owners)++;
    }

    shared_ptr_toy& operator=(const shared_ptr_toy& oth)
    {
        if ( this->obj == oth.obj)
            return *this;
        else if ( obj == nullptr)
        {
            obj=oth.obj;
            owners=oth.owners;
            (*owners)++;
        }
        else
        {
            (*owners)--;
            if(*owners<1)
            {
               delete obj;
               delete owners;
            }
            obj=oth.obj;
            owners=oth.owners;
            (*owners)++;
        }
        return *this;
    }

    friend shared_ptr_toy make_shared_toy(std::string name);
    friend shared_ptr_toy make_shared_toy(Toy& oth);

    ~shared_ptr_toy()
    {
        *owners--;
        if(*owners<1)
        {
            delete obj;
            delete owners;
        }
    };
};

shared_ptr_toy make_shared_toy(std::string name)
{
    shared_ptr_toy ptrToy;
    ptrToy.obj=new Toy(name);
    ptrToy.owners=new unsigned int(1);
    return ptrToy;
}

shared_ptr_toy make_shared_toy(Toy& oth)
{
    shared_ptr_toy ptrToy;
    ptrToy.obj=new Toy(oth);
    ptrToy.owners=new unsigned int(1);
    return ptrToy;
}

int main()
{
    Toy actToy1("leg");
    Toy actToy2("some toy");
    shared_ptr_toy toy1 = make_shared_toy("bone");
    shared_ptr_toy toy2 = make_shared_toy("something");
    shared_ptr_toy toy3 = make_shared_toy("anything");
    shared_ptr_toy toy4 = make_shared_toy("head");
    shared_ptr_toy toy5 = make_shared_toy("arm");
    shared_ptr_toy toy6 = make_shared_toy(actToy1);
    shared_ptr_toy toy7 = toy3;
    toy4=toy1;

    return 0;
}
