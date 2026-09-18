
//#include "console_utf8.h"


#include <iostream>
#include <array>
#include <map>

namespace variablen {

    constexpr int square(int x) { // Funktion KANN zur Compile-Zeit laufen 
        return x * x;
    }

    void demo(){
        int    i = 42;
        double d = 3.14;
        char   c = 'x';
        bool   b = true;


        // Brace-Initialisierung 
        int x{ 7 };
        // int y{ 7.0 };

        //auto: Typ-Deduktion = Initialisierer leitet Typ ab
        auto y1 = 0.2; //double 
        auto y2{ 2.5 }; // double
        auto y3 = { 0.2 }; // initializer_list<double>

        // Wert darf zur Laufzeit nicht geändert werden 
        const int N = 10; 
        // constexpr -> Wert MUSS zur Compile-Zeit berechenbar sein 
        constexpr int MAX = 2 * N;
        constexpr int a = square(4); 

        std::cout << "i=" << i << " d=" << d << " c=" << c << " b=" << b << '\n';
    }
    

}

namespace kontrollfluss {

    // lookup simulieren 
    std::pair<bool, int> lookup(int key) {
        if (key == 1) return { true, 999 };
        return { false, 0 };
    }


    void demo() {

        if (auto [found, value] = lookup(1); found) { // [found, value] ... Structural Binding 
            std::cout << "gefunden \n";
        }
        else {
            std::cout << "nicht gefunden";
        }


        int mode = 2;

        switch (mode) {
        case 1:
            std::cout << "Modus 1\n";
            break;
        case 2:
            std::cout << "Modus 2\n";
            [[fallthrough]];
        case 3:
            std::cout << "Modus 3\n";
            break;
        default: 
            std::cout << "Default\n";
            break;

        }


        // äquivalent ohne If-Init & Structural Binding 
        auto result = lookup(1);

        bool found = result.first;
        bool value = result.second;

        if (found) {
            std::cout << "gefunden \n";
        }
        else {
            std::cout << "nicht gefunden";
        }




        std::array<int, 5> data{ 10,20,30,40,50 };
        // Range-based for (C++11). IMMER wenn kein Index gebraucht wird
        // const auto& vermeidet Kopien, erzwingt Read-Only Zugriff 
        int sum = 0;
        for (const auto& x : data) sum += x; 

        // in-place verdoppeln 
        for (auto& n : data) n *= 2; 
        for (const auto& x : data) std::cout << x << " ";

        // Klassische for-Schleife 
        for (std::size_t i = 0; i < data.size(); ++i) {
            std::cout << i << " " << data[i] << '\n';
        }

    }
}


int main()
{

    std::cout << "=== Variablen ===\n";
    variablen::demo();

    std::cout << "=== Kontrollfluss ===\n";
    kontrollfluss::demo();

}