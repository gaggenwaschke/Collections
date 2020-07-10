## LifetimeList

LifetimeList is a generic collection that can be used without dynamic memory.
New elements are added through one of the factory functions. In the case of the
dynamically generated nodes, smart pointers take care of that.
Dynamic and static operations can be mixed in the same list.
Elements get deleted when they go out of scope with the help of their destructor.
LifetimeList is std::iterable<...>.

### Example

The first example shows how to use LifetimeList to make a list of all objects of a class:
```cpp
#include "LifetimeList.h"

/**
 * class that has a registry of all instances
 */
class MyClass
{
    public:
        MyClass() : node(instances.appendStatic(*this))
        {
        }

        static Collections::LifetimeList<MyClass&> instances;   /** hold a reference to every instance of this */

    private:
        Collections::LifetimeList<MyClass&>::Node node;         /**< the node belongs to the object */
};

Collections::LifetimeList<MyClass&> MyClass::instances{};

// instantiate as many as you want, they will all be registered in instances.
static MyClass myObjects[100];
```

The second example shows how to use it as a stand alone list
```cpp
#include "LifetimeList.h"

Collections::LifetimeList<int> iList{};     /**< generic list of integers */

void main()
{
    for (int i = 0; i < 10; ++i) {
        // static gets created in this scope
        auto nodeStatic = list.appendStatic(1);
        // dynamic gets created to a smart pointer
        auto nodeDynamic = list.pushDynamic(2);
        // scope ends here, object and smart pointer get destroyed
    }
}
```