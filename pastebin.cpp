#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Eine kleine Demo-Klasse mit auffälligen Ctor/Dtor-Messages.
class Sensor {
public:
    explicit Sensor(std::string name) : name_{std::move(name)}
    {
        std::cout << "  + Sensor '" << name_ << "' konstruiert\n";
    }
    ~Sensor()
    {
        std::cout << "  - Sensor '" << name_ << "' zerstört\n";
    }

    const std::string& name() const noexcept { return name_; }

private:
    std::string name_;
};


struct Node {
    std::string            name;
    std::shared_ptr<Node>  child;
    std::weak_ptr<Node>    parent;   // weak! — bricht den Zyklus

    explicit Node(std::string n) : name{std::move(n)}
    {
        std::cout << "  + Node '" << name << "'\n";
    }
    ~Node()
    {
        std::cout << "  - Node '" << name << "'\n";
    }
};


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

    virtual double read() const = 0;

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




















