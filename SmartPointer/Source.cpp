#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Eine kleine Demo-Klasse mit auffälligen Ctor/Dtor-Messages.
class Sensor {
public:
    explicit Sensor(std::string name) : name_{ std::move(name) }
    {
        std::cout << "  + Sensor '" << name_ << "' konstruiert\n";
    }
    ~Sensor()
    {
        std::cout << "  - Sensor '" << name_ << "' zerstört\n";
    }

    virtual double read() const { return 0.0; };

    const std::string& name() const noexcept { return name_; }

private:
    std::string name_;
};


class Temperature : public Sensor {
public:
    using Sensor::Sensor;
    double read() const override { return 21.5; }
};

class Pressure : public Sensor {
public:
    using Sensor::Sensor;
    double read() const override { return 1013.25; }
};

void demo_unique() {

    // Eigenschaften:
    // - genau ein Besitzer, klare Lebensdauer (RAII) 
    // - nicht kopierbar, aber move-bar 
    // genauso schnell wie Raw-Pointer 

    auto t = std::make_unique<Sensor>("temp-1"); 

    // Benutzen 

    std::cout << " name: " << t->name() << "\n";

    // auto p = t; // Compile-Fehler 
    // move erlaubt -> t ist danach nullptr 

    auto p = std::move(t); 

    p.reset(); // manuell Ressourcen freigeben 

    // In Container speichern -> für u.a. dynamischen Dispatch für polymorphe Objekte

    std::vector<std::unique_ptr<Sensor>> sensors;
    sensors.push_back(std::make_unique<Sensor>("temp-1"));
    sensors.push_back(std::make_unique<Sensor>("pressure-1"));

}

// Eigenschaften:
    // - mehrere Besitzer, Refcount-basierte Lebensdauer
    // nicht Universal-Smart-Pointer missbrauchen 
void demo_shared() {
    auto s1 = std::make_shared<Sensor>("shared-1"); // refcount = 1
    std::cout << "count= " << s1.use_count() << "\n";
    
    {
        auto s2 = s1; // keine Kopie! -> std::shared_ptr<Sensor> 
        std::cout << "count= " << s1.use_count() << "\n";
        auto s3 = s1; 
        std::cout << "count= " << s1.use_count() << "\n";

    }
    std::cout << "count= " << s1.use_count() << "\n";
}

struct Node {
    std::string            name;
    std::shared_ptr<Node>  child;
    std::weak_ptr<Node>    parent;   // weak! — bricht den Zyklus

    explicit Node(std::string n) : name{ std::move(n) }
    {
        std::cout << "  + Node '" << name << "'\n";
    }
    ~Node()
    {
        std::cout << "  - Node '" << name << "'\n";
    }
};


void demo_weak() {

    auto parent = std::make_shared<Node>("parent"); 
    auto child = std::make_shared<Node>("child");

    parent->child = child; // parent hält child als shared_ptr 
    child->parent = parent; // child hält parent als weak_ptr 



}

// Task: Dynamischer Dispatch: Vector polymorpher Smartpointer.
// z.b. Temperature "t-1" 21.5
//      Pressure "p-1"  1013.25 
//      Temperature "t-2"  21.5 



int main() {
    std::vector<std::unique_ptr<Sensor>> sensors;

    sensors.push_back(std::make_unique<Temperature>("t-1"));
    sensors.push_back(std::make_unique<Pressure>("p-1"));
    sensors.push_back(std::make_unique<Temperature>("t-2"));

    for (const auto& s : sensors) {

        std::cout << "    "<< s->name() << " = " << s->read() << '\n';

    }
    
    demo_unique();
    demo_shared();
}