#include <iostream>
using namespace std;

class Person
{
    private:
        string name;
        int age;
    public:
        Person(string name, int age): name(name), age(age) {}
        string getName() const {return this->name;}
        int getAge() const {return this->age;}
};