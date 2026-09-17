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
