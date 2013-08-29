/**
 * Copyright (c) 2013, Krzysztof Kli¿ <krzysztof.klis@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cassert>
#include "container.hpp"
#include <iostream>
#include <string>

using namespace ioc;
using namespace std;

class IFooBar {
public:
    virtual ~IFooBar() {};
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
