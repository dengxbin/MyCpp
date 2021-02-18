
#include <iostream>

class string{
    public:
    string():str(nullptr){
        
    };
    string(char * s){
        size_t n=strlen(s)+1;
        str=new char[n];
        std::memcpy(str,s,n);
    };
    //复制构造
    string(const string & other):string(other.str){
 
    }
    //移动构造
    string( string && other):str(std::exchange(other.str,nullptr)){

    }
    //复制赋值
    string & operator=(const string & other){
        return *this=string(other);//这里有疑问，为什么调用构造函数
    }
    //移动赋值
    string&  operator= (string && other)
    {
        std::swap(other.str,str);
    }

    ~string(){
        delete str;
    }
    //注意这里，如果非const，上边会出错
    size_t length() const {
        return strlen(str)+1;
    }
 
    char * str;
};