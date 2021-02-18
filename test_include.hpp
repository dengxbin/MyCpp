#include <iostream>
#include <functional>
#include <vector> 
#include <algorithm>
#include <string>
#include <stdexcept>
#include <cstring>
using namespace std;
int property_get(const char *key, char *value, const char *default_value)
{
    char tmp[100]="12345";
    string str{tmp};
    cout<<"hash::"<<std::hash<string>{}(str)<<endl;
    memcpy(value, &tmp,sizeof(value));
    return 1;
}
auto get_prop=[](string prop){
    try{        
        char propertyValue[100]{};
        int len = property_get(prop.data(), propertyValue, "0");
        if (len<=0) throw std::runtime_error("wrong prop");
        // for(int i=0; i<10;i++)
        //     printf("%d",propertyValue[i]);
        std::string line{};
        line.assign(propertyValue);
        // cout<<"line size is"<<line.size()<<endl;
        // for(auto&& ch:line) {
        //     cout<<ch<<endl;
        // }
        // cout<<line<<endl;
        // cout<<std::stoi(line)<<endl;
        return std::stoi(line);
    }
    catch(const std::exception& e)
    {
        printf("error when getprop:%s \n",e.what());
        return -1;
    }
};
    auto get_prop1=[](string prop){       
        auto len=11;
        return len>0 ?  len : 0;
    };
    auto MemHash=[](const char *s,int size){
    // string tag{"android.vendor.test.hash.size"};
    // int percentage= property_get_int32(tag.data(), 0);
    // if (percentage<=0) return ;
    // int samping_size= percentage<100 ? size/percentage : size;
    return std::hash<std::string_view>()(std::string_view(s, size)); 
    };
    template<typename TYPE>
void typeCheck(TYPE data)
{
    if(std::is_same<TYPE,int>::value)
    {
        std::cout<<"int type"<<std::endl;
    }
    else if(std::is_same<TYPE,std::string>::value)
    {
        std::cout<<"string type"<<std::endl;
    }
    else
    {
        std::cout<<"other type";
    }
}
int main()
{
    char data[100]="12345";
    auto ret=MemHash(data,sizeof(data));

    cout<<typeid(ret).name()<<endl;
    unsigned long long1=100000; 
    cout<<typeid(long1).name()<<endl;
    return 0;
}