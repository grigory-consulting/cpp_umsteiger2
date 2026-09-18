#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <numbers>


class Shape {
public:
	
	virtual ~Shape() = default; // Destructor
	virtual double area() const = 0; // pure virtual, muss überschrieben werden, const -> darf nicht Objektszustand ändern
	virtual std::string name() const { return "Shape"; } // nicht-pure virtual, kann überschrieben werden 

};

class Circle : public Shape { // public weil sonst Klasse private erbt 
	double r_; 
public: 
	explicit Circle(double r) : r_{r} {} // explicit verbietet Circle c = 1.0 
	double area() const override { return std::numbers::pi * r_ * r_; }
	std::string name() const override { return "Circle"; }

};


class Square : public Shape {
	double side_;
public:
	explicit Square(double side) : side_{ side } {}

	double area() const override { return side_ * side_; }
	std::string name() const override { return "Square"; }

};

// final: keine weiteren Ableitung möglich 
class Triangle final : public Shape {
	double base_, height_;
public: 
	Triangle(double b, double h) : base_{b}, height_{h} {}

	double area() const override { return 0.5*base_*height_; }
	std::string name() const override { return "Triangle"; }
};

// Slicing-Falle, Basis nicht abstrakt
class Animal {
public:
	virtual ~Animal() = default;
	virtual std::string sound() const { return "..."; }
};

class Dog : public Animal {
public:
	std::string sound() const override { return "Dog"; }

};

void speak_by_value(Animal a) // slice: IMMER Animal::sound() 
{
	std::cout << a.sound() << "\n";
}

void speak_by_ref(const Animal& a) // polymorph
{
	std::cout << a.sound() << "\n";
}


int main() {

	Circle c{ 2.0 };
	Square q{ 4.0 };
	Triangle t{ 2.0,4.0 };

	Shape& s = c;
	Shape* p = &c; 

	std::cout << c.Shape::name() << "\n";
	std::cout << s.name() << "\n";
	std::cout << p->name() << "\n";


	// Dynamischer Dispatch 
	std::vector<Shape*> shapes{ &c, &q, &t };

	for (Shape* shape : shapes) {
		std::cout << shape->name() << " " << shape->area() << "\n";
	}



	Dog dog;
	speak_by_value(dog);
	speak_by_ref(dog);


}