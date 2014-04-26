### DESCRIPTION

This is a simple dependency container for C++, which allows you to use the inversion of control (IoC) pattern in your applications.
The project started as a [blog entry](http://weblambdazero.blogspot.com/2013/08/dependency-injection-in-c.html).

### INSTALLATION

The container requires no installation, just include the "container.hpp" file in your source code.

There is also an example test application container_test.cpp which you can build with "make".

### USAGE

Inversion of control (IoC) is about decoupling the class from its dependencies. Suppose you have a class that does some logging:

```cpp
class Foo {
private:
    Logger *logger;
public:
    Foo() {
        logger = new Logger();
    }
    void doSomethig() {
        /* does something */
        this->logger->log("done");
    }
}
```

This class is strongly tied to concrete logger instance, which means that:
* it will require refactoring in case of using a different logger,
* writng unit tests for this class will be very hard, if not impossible.

Much more sane implementation would look as follows:

```cpp
class ILogger() {
    virtual void log(std::string s) = 0;
};

class Logger : public ILogger() {
    void log(std::string s) {
        /* implementation goes here */
    }
};

class Foo {
private:
    ILogger *logger;
public:
    Foo(ILogger *l) {
        logger = l;
    }
    void doSomethig() {
        /* does something */
        this->logger->log("done");
    }
}
```

Now, you can create an instance of a class inheriting from ILogger (FileLogger, NetworkLogger, etc.) and inject it (hence term "dependency injection") into Foo through a constructor.
Also, writing unit tests is now possible, because you can create another class, like FakeLogger, which has an empty log(std::string) method or does some assertions inside, and use it with Foo without modification.

However, if you have a lot of classes, it is tedious to instantiate all of them with proper dependencies:

```cpp
Foo *foo1 = new Foo(new FileLogger());
...
Foo *foo2 = new Foo(new FileLogger());
```

So you can use a container to keep them for you:

```cpp
/* Bootstrap code */
ioc::Container::Register<ILogger>(new FileLogger());
/* Application code */
Foo *foo1 = new Foo(ioc::Container::Resolve<ILogger>());
...
Foo *foo2 = new Foo(ioc::Container::Resolve<ILogger>());
```

You can also use the container as a service locator, which means that a class uses a container instance to retrieve the dependencies itself:

```cpp
class Foo {
private:
    ILogger *logger;
public:
    Foo() {
        logger = ioc::Container::Resolve<ILogger>();
    }
    void doSomethig() {
        /* does something */
        this->logger->log("done");
    }
}

/* Bootstrap code */
ioc::Container::Register<ILogger>(new FileLogger());
/* Application code */
Foo *foo1 = new Foo();
...
Foo *foo2 = new Foo();
```

Check out the container_test.cpp for a complete example implementation.
