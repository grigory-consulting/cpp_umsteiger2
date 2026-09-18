#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// Eigene Exception Klasse 

class SensorError : public std::runtime_error {
public:
	SensorError(std::string sensor, std::string message)
		: std::runtime_error{std::move(message)}
		, sensor_{std::move(sensor)}
	{}

	const std::string& sensor() const noexcept {
		return sensor_;
	}

private:
	std::string sensor_;
};

void readSensor(){
	throw SensorError{
		"temp-1",
		"Could not read sensor"
};
}

// RAII 

class Widget {
public: 
	//
	// Destruktoren sind implizit noexcept -> wenn doch std::terminate()
	// 
	// Move-Semantik 
	// z.B. std::vector<Widget> kann effizient die Objekte bewegen (statt kopieren) 
	Widget(Widget&&) noexcept = default;
	Widget& operator=(Widget&&) noexcept = default;

	// triviale Getter
	int value() const noexcept { return value_; }
private: 
	int value_ = 0;
};

class LogHandle {
public:
	~LogHandle() {
		try {
			flush();
		}
		catch (...) {
			// Fehler loggen, aber nicht weiterwerfen. 
		}
	}
private:
	void flush() { /* kann werfen */}
};

// Copy-Swap-Idiom 
// Strong Guarantee für Exception-Safety

class Registry {
public:
	
	void replace(const std::vector <std::string>& new_items) {
		// Kopiere new_items. U.a. kann das werfen.
		std::vector<std::string> tmp = new_items;

		// Commit:
		// jetzt items_ verändern
		items_.swap(tmp);
		// tmp am Scope-Ende zerstört weil RAII 
	}

private:
	std::vector<std::string> items_;
};






int main() {
	
	try {
		readSensor();
	}
	catch (const SensorError& e) {
		std::cout << "Sensor: " << e.sensor() << "\n";
		std::cout << "Error: " << e.what() << "\n";
 	}

	// Alles 

	try {
		//readSensor();
		throw "kaputt";
	}
	catch (const SensorError& e) {
		std::cout << "Error: " << e.what() << "\n";
	}
	catch (const std::invalid_argument& e) {
		std::cout << "invalid argument: " << e.what() << "\n";
	}
	catch (const std::exception& e) { // Basisklasse
		std::cout << "Generischer Fehler: " << e.what() << "\n";
	}
	catch (...) {
		std::cout << "Unbekannte Exception"  << "\n";
	}

}