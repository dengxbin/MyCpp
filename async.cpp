#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>
 /*
std::mutex m;
struct X {
    void foo(int i, const std::string& str) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << str << ' ' << i << '\n';
    }
    void bar(const std::string& str) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << str << '\n';
    }
    int operator()(int i) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << i << '\n';
        return i + 10;
    }
};
 
template <typename RandomIt>
int parallel_sum(RandomIt beg, RandomIt end)
{
    auto len = end - beg;
    if (len < 1000)
        return std::accumulate(beg, end, 0);
 
    RandomIt mid = beg + len/2;
    auto handle = std::async(std::launch::async,
                             parallel_sum<RandomIt>, mid, end);
    int sum = parallel_sum(beg, mid);
    return sum + handle.get();
}
 
int main()
{
    std::vector<int> v(10000, 1);
    std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';
 
    X x;
    // 以默认策略调用 x.foo(42, "Hello") ：
    // 可能同时打印 "Hello 42" 或延迟执行
    auto a1 = std::async(&X::foo, &x, 42, "Hello");
    // 以 deferred 策略调用 x.bar("world!")
    // 调用 a2.get() 或 a2.wait() 时打印 "world!"
    auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");
    // 以 async 策略调用 X()(43) ：
    // 同时打印 "43"
    auto a3 = std::async(std::launch::async, X(), 43);
    a2.wait();                     // 打印 "world!"
    std::cout << a3.get() << '\n'; // 打印 "53"
} // 若 a1 在此点未完成，则 a1 的析构函数在此打印 "Hello 42"
*/
#include <chrono>
#include <iostream>
#include <future>
#include <thread>
 
int fib(int n)
{
  if (n < 3) return 1;
  else return fib(n-1) + fib(n-2);
}
 
int main()
{
    std::future<int> f1 = std::async(std::launch::async, [](){
        return fib(40);
    });
    std::future<int> f2 = std::async(std::launch::async, [](){
        return fib(43);
    });
 
    std::cout << "waiting... " << std::flush;
    const auto start = std::chrono::system_clock::now();
 
    f1.wait();
    f2.wait();
 
    const auto diff = std::chrono::system_clock::now() - start;
    std::cout << std::chrono::duration<double>(diff).count() << " seconds\n";
 
    std::cout << "f1: " << f1.get() << '\n';
    std::cout << "f2: " << f2.get() << '\n';
}