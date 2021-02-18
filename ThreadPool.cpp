#include<iostream>
#include<thread>
#include<vector>
#include<functional>
#include<queue>
#include<memory>
#include<mutex>
#include<condition_variable>
class threadPool{
    public:
        threadPool(size_t);
        ~threadPool()=default;
        void addTask(std::function<void()>&);
        template<class F, class... Args> decltype(auto) enqueue(F&& f, Args&&... args);
       
    private:
        std::queue<std::function<void()>> m_tasks;
        std::vector<std::thread> m_works;
        std::mutex m_mutex;
        std::condition_variable cv;
};

threadPool::threadPool(size_t size){
    for (size_t i = 0; i < size; i++){
       m_works.emplace_back(
           [this]{
               while(1){
                   std::function<void()> task;
                   {
                       std::cout << "construct" << '\n';
                        std::unique_lock<std::mutex> lk(m_mutex);
                        //wait until task queue not empty
                        cv.wait(lk,[this]{!this->m_tasks.empty();});

                       task=std::move(this->m_tasks.front());
                       this->m_tasks.pop();

                   }
                   task();
                }
           }
       );
    }

}

threadPool::~threadPool(){ 
    {
        std::unique_lock<std::mutex> lock(m_mutex);

    }
    cv.notify_all();
    //for()
}
template<class F, class... Args>
decltype(auto) threadPool::enqueue(F&& f, Args&&... args){
    
}
void threadPool::addTask(std::function<void()>& task){
    std::lock_guard<std::mutex> lock(m_mutex);
    m_tasks.emplace(std::move(task));
}
struct Foo {
    Foo(int num) : num_(num) {}
    void print_add(int i) const { std::cout << num_+i << '\n'; }
    int num_;
};
 
void print_num(int i)
{
    std::cout << i << '\n';
}
 
struct PrintNum {
    void operator()(int i) const
    {
        std::cout << i << '\n';
    }
};
int main(){
    threadPool t(4);
    // std::function<void()> f_display = [](){ print_num(42);};
    // t.addTask(f_display);
    return 0;
}