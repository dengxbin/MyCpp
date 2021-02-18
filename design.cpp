#include<iostream>
#include<list>
#include<string>
#include<string_view>
#include <memory>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
class Isubscriber{
    public:
    virtual void update(std::string_view message) const=0;
    virtual void setPub();
};
using pSubscriber= std::shared_ptr<Isubscriber> ;
class Ipublisher{
    public:
    virtual void subscribe(pSubscriber)=0;
    virtual void unsubscribe(pSubscriber)=0;
    virtual void notifyAll(std::string_view message) const=0;
};
using pPublisher= std::shared_ptr<Ipublisher> ;
class publisher:public Ipublisher
{
    public:
    publisher(){
        std::cout << "construct publisher "<<std::endl;
    };
    void subscribe(pSubscriber sub) override{
        list.emplace_back(sub);
        std::cout << " subscribe! "<<std::endl;

    };

    void unsubscribe(pSubscriber sub) override{
        list.remove(sub);
    };
    void notifyAll(std::string_view message) const override{
        for(auto&& sub:list){
            sub->update(message);
        }
    };
    virtual ~publisher(){
        list.clear();
    };
    private:
    std::list<pSubscriber> list;
};
class subscriber:public Isubscriber,public std::enable_shared_from_this<Isubscriber>{
    public:
    subscriber()=default;
    subscriber(std::shared_ptr<Ipublisher> newPub):pub(newPub){
        std::cout <<"subscriber construct"<<std::endl;
        std::cout <<"pub ref is "<<pub.use_count()<<std::endl;

        pub.lock()->subscribe(shared_from_this());
        std::cout <<"subscriber construct end"<<std::endl;
    };
    void update(std::string_view message) const{
        std::cout <<message<<std::endl;
    };
    void setPub(std::shared_ptr<Ipublisher> newPub){
        pub=newPub;
        std::cout <<"setting"<<std::endl;
    };

    virtual ~subscriber(){
    };
    private:
    std::weak_ptr<Ipublisher> pub;
};

class bufferQ
{
private:
    /* data */
    std::list<int> data;
    std::mutex m;
public:
    bufferQ(/* args */){
        data={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    }; 
    ~bufferQ()=default;
    int size() const{
        return data.size();
    }
    void push(int num){
        std::lock_guard<std::mutex> lock(m);
        data.push_back(num);
    }
    int pop(){
        std::lock_guard<std::mutex> lock(m);
        if(!data.empty()){
            int ret= data.front();
            std::cout<<"buffer:"<<ret<<std::endl;
            data.pop_front();
            return ret;
        }
        return -1;
    }
};


bufferQ Q;
void producer(){
    for (size_t i = 0; i < 100; i++)
    { 
        using namespace std::chrono_literals ;
        std::cout<<"producer:"<<i<<std::endl;
        /* code */
        Q.push(i);
        std::this_thread::sleep_for(10ms);
    }
    
}
void consumer(){
    std::thread::id thread_id = std::this_thread::get_id();
    using namespace std::chrono_literals ;
        /* code */
    std::this_thread::sleep_for(10ms);
    int ret=Q.pop();
    std::cout<<"consumer::"<<thread_id<<"::"<<ret<<std::endl;
}






int main(){
    // pPublisher pub1=std::make_shared<publisher>();
    // // pSubscriber sub1=std::make_shared<subscriber>(pub1);
    
    // // pSubscriber sub2=std::make_shared<subscriber>(pub1);
    // // pSubscriber sub3=std::make_shared<subscriber>(pub1);
    // // subscriber sub1;
    // // sub1.setPub(pub1);
    // // pSubscriber sub2(new subscriber());
    // // pSubscriber sub3(new subscriber());
    // pub1->notifyAll("hello there!");

    std::vector<std::thread> t;
    t.emplace_back(std::thread(&producer));
    t.emplace_back(std::thread([]{
        for (int i = 0; i <10;i++)
        consumer();
    }));
    t.emplace_back(std::thread([]{
        for (int i = 0; i <10;i++)
        consumer();
    }));
     t.emplace_back(std::thread([]{
        for (int i = 0; i <10;i++)
        consumer();
    }));   
    //t.emplace_back(std::thread(&producer));
    // t.emplace_back(std::thread(&consumer));
    // t.emplace_back(std::thread(&consumer));
    for(auto&& thread:t){
        thread.join();
    }
    std::cout<<"Q size is "<<Q.size()<<std::endl;
    return 0;
}