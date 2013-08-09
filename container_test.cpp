#include <cassert>
#include "container.hpp"
#include <iostream>
#include <string>

using namespace ioc;
using namespace std;

class IFooBar {
public:
    virtual string getName() = 0;
};

class Foo : public IFooBar {
public:
    string getName() {
        return "Foo";
    }
};

class Bar : public IFooBar {
public:
    string getName() {
        return "Bar";
    }
};

class Test {
private:
    IFooBar *foobar;
public:
    Test() {
        Init(Container::Resolve<IFooBar>());
    }
    Test(IFooBar *fb) {
        Init(fb);
    }
    ~Test() {
        delete foobar;
    }
    void Init(IFooBar *fb) {
        foobar = fb;
    }
    string getName() {
        return foobar->getName();
    }
};

int main() {
    Test *t;

    t = new Test(new Foo());
    assert(t->getName().compare("Foo") == 0);
    delete t;

    t = new Test(new Bar());
    assert(t->getName().compare("Bar") == 0);
    delete t;

    Container::Register<IFooBar>(new Foo());
    t = new Test();
    assert(t->getName().compare("Foo") == 0);
    delete t;

    Container::Register<IFooBar>(new Bar());
    t = new Test();
    assert(t->getName().compare("Bar") == 0);
    delete t;

    cout << "All tests passed" << endl;

    return 0;
}
