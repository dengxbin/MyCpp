#include<memory>
#include<mutex>
class singleton {


    public:
    static std::shared_ptr<singleton> getInstance(){
        //std::lock_guard<std::mutex> lock(mut);

    }


private:
   mutable std::mutex mut;

};

#include <iostream>
#include <stack>
#include <iterator>
#include <map>
#include <sstream>
#include <cassert>
#include <vector>
#include <stdexcept>
#include <cmath>
#include<functional>
using namespace std;

template <typename T>
double evaluate_rpn(T itm, T end){
    stack<double> val_stack;
    auto pop_stack([&](){ 
        auto r(val_stack.top());
        val_stack.pop();
        return r;
    });
}

 function<double<double,double>> g=t;

map<string,  function<double<double,double>> > ops {
    {"+", [](double a, double b) { return a + b; }},
    {"-", [](double a, double b) { return a - b; }},
    {"*", [](double a, double b) { return a * b; }},
    {"/", [](double a, double b) { return a / b; }},
    {"^", [](double a, double b) { return pow(a, b); }},
    {"%", [](double a, double b) { return fmod(a, b); }},
};

