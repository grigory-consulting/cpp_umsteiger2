#include <iostream>
#include <algorithm>
#include <string>


// Rule of 5 an einem eigenen Buffer-Typ
// in Praxis std::vector<char>  

class Buffer {
    char* data_;
    std::size_t size_;

public:
    explicit Buffer(std::size_t n)
        : data_{ new char[n] }, size_{ n }
    {
        std::cout << " Buffer" << n << " konstruiert";
    }

    // Rule Nr.: 1
    // Destructor

    ~Buffer()
    {
        delete[] data_; 
        std::cout << " Buffer" << " zerstoert\n";
    }
    
    // Rule Nr.: 2
    // Copy-Constructor 
    // Buffer a{8}
    // Buffer b{a} <- Copy-Constructor
    Buffer(const Buffer& a)
        : data_{ new char[a.size_] }, size_{ a.size_ }
    {
        std::copy_n(a.data_, size_, data_);

    }
    // Alternativ: Kopieren explizit verbieten
    // Buffer(const Buffer& a) = delete; 

    // Rule Nr.: 3
    // Copy-Assign 
    // Buffer a{8}
    // Buffer b{8}
    // b = a; 

    Buffer& operator=(const Buffer& other)
    { 
        if (this != &other) { // Selbst-Zuweisung abfangen 
            char* new_data = new char[other.size_]; // zuerst allokieren
            std::copy_n(other.data_, other.size_, new_data); // Kopieren
            delete[] data_; // alten freigeben 
            data_ = new_data;
            size_ = other.size_;
        }
        std::cout << "  Buffer copy-assign\n";
        return *this;
    
    }

    // Rule of Three done 

    // Move-Constructor 
    // Buffer a{8}
    // Buffer b = std::move(a);

    Buffer(Buffer&& other) : data_{ other.data_ }, size_{ other.size_ } {
        other.data_ = nullptr; // a gibt es dann nicht 
        other.size_ = 0;
        std::cout << "  Buffer move-ctor\n";
    }


    // Buffer a{8}
    // Buffer b{8}
    // b = std::move(a); 

    Buffer& operator=(Buffer&& other) {
        if (this != &other) {
            delete[] data_; 
            data_ = other.data_;
            size_ = other.size_; 
            other.data_ = nullptr; 
            other.size_ = 0;
        }
        std::cout << "  Buffer move-assign\n";
        return *this;

    }

};

int main() {
    // Rule of 5 
    Buffer a{ 1024 };
    Buffer b{ a };  // Copy-Ctor
    Buffer c{ std::move(a) }; // Move-Ctor - a ist danach "leer"
    b = c;  // Copy-Assign
    b = std::move(c); // Move-Assign 
}