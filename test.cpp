
#include "LifetimeList.h"
#include <iostream>
#include <memory>

class MyClass
{
    public:
        MyClass() : node(instances.appendStatic(*this))
        {
        }

        static Collections::LifetimeList<MyClass&> instances;


    private:
        Collections::LifetimeList<MyClass&>::Node node;
};

Collections::LifetimeList<MyClass&> MyClass::instances{};

template <class T>
void print(Collections::LifetimeList<T>& lst)
{
    std::cout << "[" << lst.size() << "-tupel] = {";
    for (auto element : lst) {
        std::cout << element << ",";
    }
    std::cout << "}" << std::endl;
}

template <class T>
void testStatic(Collections::LifetimeList<T> &list)
{
    for (size_t i = 0; i < 100; i++)
    {
        auto node1 = list.appendStatic(i*2);
        auto node2 = list.pushStatic(i*2 + 1);
    }    
}

template <class T>
void testDynamic(Collections::LifetimeList<T> &list)
{
    auto n1 = list.appendDynamic(10);
    auto n2 = list.appendDynamic(11);

    n1.reset();
    n2.reset();

    n1 = list.appendDynamic(12);
    // forget to reset this on porpuse
}

int main(int argc, char* argv[])
{
    std::cout << "---------- Test started --------------" << std::endl;

    Collections::LifetimeList<int> lst{};

    // define array in function scope
    auto x = {
        lst.appendStatic(-2),
        lst.appendStatic(-1),
        lst.appendStatic(0),
        lst.appendStatic(1),
        lst.appendStatic(2)
    };

    testStatic(lst);
    testDynamic(lst);
    print(lst);

    MyClass instances[10];
    std::cout << "MyClass instances: " << MyClass::instances.size() << std::endl;

    return 0;
}