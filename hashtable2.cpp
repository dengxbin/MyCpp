#include<iostream>
#include<list>
#include<array>

struct item {
    char* key;
    char* value;
};

class hashTable {
    public:
        hashTable(size_t size):size(size) {
        //std::to_array(size)
        }
    private:
        size_t size=1;//bucket size
        size_t count=0;//real count
        std::array<std::list<item>,1> * buckets=nullptr;
    
};


#include <deque>
#include <list>
#include <vector>
#include <functional>
template <typename C>
static auto consumer(C& container){
        return [&](auto value) {
                container.push_back(value);
        };
}
template <typename T>
static void print(const T& c){
        for (auto i : c){
                std::cout << i << ", ";
        }
        std::cout << "\n";
}
int main()
{
        std::deque<int> d;
        std::list<int> l;
        std::vector<int> v;
        
        const std::vector<std::function<void(int)>> consumers{
                consumer(d),consumer(l),consumer(v)
        };
        for (size_t i{ 0 }; i < 10; ++i)
                for (auto&& consume : consumers)
                        consume(i);
        print(d);
        print(l);
        print(v);
        return 0;          
}
