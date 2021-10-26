#include <bits/stdc++.h>
using namespace std;

class Person {
public:
    static std::shared_ptr<Person> create(const std::string& name);
};

class RealPerson: public Person {
private:
    std::string name;
public:
    RealPerson(const std::string& name): name(name) {}
    ~RealPerson() {}
    std::string get_name() const { return this->name; }
};

std::shared_ptr<Person> Person::create(const std::string& name) {
    return std::shared_ptr<Person>(new RealPerson(name));
}
int main() {
    auto it = Person::create("xiao hong");
    cout << std::static_pointer_cast<RealPerson>(it)->get_name() << endl;
	return 0;
}
