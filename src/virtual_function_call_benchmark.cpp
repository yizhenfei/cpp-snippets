#include <sys/time.h>
#include <cstdint>
#include <iostream>

class Base {
public:
    Base() : counter(0) {}
    virtual void foo() = 0;

    int64_t counter;
};

class Derived : public Base {
public:
    virtual void foo();
};

void Derived::foo()
{
    counter += 1;
}

class Concrete {
public:
    void foo();

    int64_t counter;
};

void Concrete::foo()
{
    counter += 1;
}

int main(int argc, char *argv[])
{
    const int64_t LOOP = 10 * 1024 * 1024 * 1024LL;

    struct timeval dbegin;
    struct timeval dend;
    struct timeval cbegin;
    struct timeval cend;
    struct timeval bbegin;
    struct timeval bend;
    
    Base *base = new Derived();
    Concrete concrete;

    gettimeofday(&dbegin, nullptr);
    int64_t tmp = 0;
    for (int64_t i = 0; i < LOOP; ++i) {
        tmp += 1;
    }
    gettimeofday(&dend, nullptr);

    gettimeofday(&cbegin, nullptr);
    for (int64_t i = 0; i < LOOP; ++i) {
        concrete.foo();
    }
    gettimeofday(&cend, nullptr);

    gettimeofday(&bbegin, nullptr);
    for (int64_t i = 0; i < LOOP; ++i) {
        base->foo();
    }
    gettimeofday(&bend, nullptr);

    std::cout << "dbegin: " << dbegin.tv_sec << "." << dbegin.tv_usec << std::endl;
    std::cout << "dend: " << dend.tv_sec << "." << dend.tv_usec << std::endl;
    std::cout << "cbegin: " << cbegin.tv_sec << "." << cbegin.tv_usec << std::endl;
    std::cout << "cend: " << cend.tv_sec << "." << cend.tv_usec << std::endl;
    std::cout << "bbegin: " << bbegin.tv_sec << "." << bbegin.tv_usec << std::endl;
    std::cout << "bend: " << bend.tv_sec << "." << bend.tv_usec << std::endl;
    
    return 0;
}
