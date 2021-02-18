#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include<chrono>
std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
 
void worker_thread()
{
    // 等待直至 main() 发送数据
    std::unique_lock<std::mutex> lk(m);
    cv.wait(lk, []{return ready;});
 
    // 等待后，我们占有锁。
    std::cout << "Worker thread is processing data\n";
    data += " after processing";
 
    // 发送数据回 main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";
 
    // 通知前完成手动解锁，以避免等待线程才被唤醒就阻塞（细节见 notify_one ）
    lk.unlock();
    cv.notify_one();
}
 void foo()
{
    // 模拟昂贵操作
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "foo running first helper...\n";
}
 
void bar()
{
    // 模拟昂贵操作
    std::this_thread::sleep_for(std::chrono::seconds(1));
       std::cout << "bar running first helper...\n";
}
int main()
{
    // std::cout << "starting first helper...\n";
    // std::thread helper1(foo);
 
    // std::cout << "starting second helper...\n";
    // std::thread helper2(bar);
 
    // std::cout << "waiting for helpers to finish..." << std::endl;
    // helper1.join();
    // helper2.join();
 
    // std::cout << "done!\n";
    std::thread worker(worker_thread);
 
    data = "Example data";
    // 发送数据到 worker 线程
    {
        std::lock_guard<std::mutex> lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();
 
    // 等候 worker
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return processed;});
    }
    std::cout << "Back in main(), data = " << data << '\n';
 
    worker.join();
}