



#include <iostream>
#include <concepts>
#include <utility>
#include <vector>



// Ohne Templates 

int maxValue(int a, int b) {
    return a > b ? a : b;
}

double maxValue(double a, double b) {
    return a > b ? a : b;
}


// Template 
template <typename T> // <class T>, Platzhalter für einen Typ 
T maxValue(T a, T b) {
    return a > b ? a : b;
};

// Compiler erzeugt passende Instanzen

// maxValue<int>(10, 20);
// maxValue<double>(3.5, 1.2);
// maxValue<std::string>(a, b);


// Mehrere Typen 
template <typename T, typename U>
void print(T a, U b) {
    std::cout << a << " " << b;
};

// print(42, "Hallo") 

template <typename T>
class Box {
public: 
    Box(T value): value_(value) {}

    T getValue() const {
        return value_; 
    }
private:
    T value_;
};

// Compiler erzeugt passende Instanzen

// Box<int> box1(2);
// Box<double> box1(2.0);


// std::vector ist ebenfalls ein Class Template
//std::vector<int>
//std::vector<double>
//std::vector<std::string>

// Concepts 
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>; // std::integral ... ganzzahlig (int, long, size_t,....) 

template <Number T>
T add(T a, T b) {
    return a + b;
};

// erlaubt add(1,2)
// nicht erlaubt add(std::string("A"), std::string("B"));

template <typename T>
requires std::integral<T>
T square(T value) {
    return value * value;
};

template <typename T>
concept Addable = requires(T a, T b) {
    a + b;
};

// T erfüllt Addable, wenn der Ausdruck a+b gültig ist. 

template <Addable T>
T add(T a, T b) {
    return a + b;
};

template <typename T>
concept Addable2 = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

template <Addable2 T>
T add2(T a, T b) {
    return a + b;
};

// T erfüllt Addable, wenn der Ausdruck a+b gültig ist und das Ergebnis exakt vom Typ T sein muss. 

template <typename T>
concept Arithmetic = requires(T a, T b) {
    a + b;
    a - b;
    a * b;
    a / b;
};


int main(){


struct Person {};



unsigned int a = UINT_MAX;
unsigned int b = 1;

std::cout << add2(a, b);
//maxValue(a, b);



}