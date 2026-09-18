#include <iostream>
#include <string>
#include <vector>


void by_value(int x) { x += 1; }

void by_const_ref(const std::string& s) {
	std::cout << s << "\n";
}

void by_ref(std::string& s) {
	s += " modifiziert";
}

void by_pointer(std::string* s) {
	if (s) *s += " modifiziert via Pointer";
}

void by_rvalue_ref(std::string&& s) {
	std::string own = std::move(s); // s = "Hallo" -> own = "Hallo" -> s = gültiger std::string
	// s = "Neuer Wert"; 
	// aber Inhalt nicht garantiert / vorausgesetzt 
	// valid but unspecified state 
}