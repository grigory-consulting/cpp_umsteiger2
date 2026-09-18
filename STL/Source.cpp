#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <set>
#include <unordered_map>
#include <numeric> // accumulate 
#include <functional>

namespace container {

    void demo() {
        // Sequenz-container 

        std::vector<int> vec{ 5,2,8,1,9 }; 
        std::deque<int> deq{1,2,3 };
        std::list<int> lst{ 10, 20, 30 }; 

        vec.push_back(10); // O(1) amortisiert  
        deq.push_back(10); // O(1)
        deq.push_front(10); // O(1)
        lst.push_back(10); // O(1)
        lst.push_front(10); // O(1)


        // std::set: sortierte, eindeutige Werte 
        std::set<int> ids{ 3,1,4,1,1,5,2,9,6 };

        for (const auto& id : ids) std::cout << ' ' << id;
        std::cout << '\n';

        // lookup ist O(1), bei der map ist O(log n) 
        std::unordered_map<int, std::string> id_to_name{
            {1, "A"},
            {2, "B"},
        };


    }

}


namespace algorithmen {

    void demo() {

        std::vector<int> vec{ 5,2,8,1,9 };

        // Liste sortieren 


        //std::sort(vec.begin(), vec.end(), std::greater<int>()); // reverse sortieren 
        //std::sort(vec.rbegin(), vec.rend()); // reverse sortieren 
        std::sort(vec.begin(), vec.begin() + 2);


        for (const auto& x : vec) {
            std::cout << x << " ";
        }

        std::cout << "\n";



        auto it = std::find(vec.begin(), vec.end(), 1); // element 1 suchen
        if (it != vec.end()) {
            std::cout << std::distance(vec.begin(), it) << "\n";
        }

        // Z‰hlen mit Pr‰dikat 
        auto gt3 = std::count_if(vec.begin(), vec.end(), [](int x) { return x > 3; });

        // Summe
        // 
        double sum = std::accumulate(vec.begin(), vec.end(), 0); 



    }
}
    namespace iteratoren {

        void demo() {
            //bidirectional Iterator 
            
            
            std::list<int> lst{ 1,2,3 };
            
            
            auto lit = lst.end();
            --lit;
            std::cout << *lit << "\n";

            std::vector<int> vec{ 5,2,8,1,9 };

            auto vit = vec.begin();
            vit+=2;
            std::cout << *vit;


        }
        
    }
    

    
    namespace task{

        

        void solution() {
            //std::minmax_element gibt ein Paar{ min_it, max_it } in einem Durchgang zur¸ck.
            //std::nth_element -> partielle Sortierung 

            std::vector<double> temps{
        22.1, 23.4, 21.8, 24.5, 25.1, 23.9,
        31.2, 35.6, 28.4, 27.3, 29.1,
        22.5, 23.0, 24.0, 80.0 // Ausreiﬂer 
            };
            
            auto [min_it, max_it] = std::minmax_element(temps.begin(), temps.end());

            double min = *min_it;
            double max = *max_it;

            double mean = std::accumulate(temps.begin(), temps.end(), 0.0) / temps.size(); 

            auto mid = temps.begin() + temps.size() / 2; 
            std::nth_element(temps.begin(), mid, temps.end()); 
            double median = *mid;

            //std::vector<double> hot(temps.size()) ; // zeros
            //auto end = std::copy_if(temps.begin(), temps.end(), hot.begin(), [](double x) {return x > 30.0; });
            // hot -> {31, 80, 0, 0, 0 } 
            //hot.erase(end, hot.end()); 

            // back_inserter ... Wenn du ein Ergebnis hast, push_back an diesen Container 
            std::vector<double> hot;
            std::copy_if(temps.begin(), temps.end(), std::back_inserter(hot), [](double x) {return x > 30.0; });


        }

}



int main()
{
    std::cout << "Container\n";
    container::demo();
    std::cout << "Algorithmen";
    algorithmen::demo();
    iteratoren::demo();

}