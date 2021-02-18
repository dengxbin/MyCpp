/////////////////////// 快速删除/////////////////////
/*
这个使用最后一个值将需要删除的值 覆盖掉。
在remove 模板函数中，使用move 防止拷贝复制产生。

相对erase的好处是，这样不需要调动每个值得位置（删除值之后得pos),这样做复杂度可以达到O(1)
 - CPP reference 线性：调用 T 析构函数的次数与被擦除的元素数相同，调用 T 赋值运算符的次数与 vector 中被擦除元素后的元素数相等。 
*/
/////////////////////////安全访问/////////////////
#include <iostream>
#include <vector> 
#include <algorithm>
#include <string>
#include <cassert>

using namespace std;
template <typename T>
void quick_remove_at(std::vector<T> &v, std::size_t idx)
{
    if(idx<v.size())
    {
        v[idx]=std::move(v.back());
        v.pop_back();
    }
}
template <typename T>
void quick_remove_at(std::vector<T> &v, typename std::vector<T>::iterator it)//这里有个疑问，typename 是什么作用
{
    if (it!= std::end(v))
    {
    *it=std::move(v.back());
    v.pop_back();        /* code */
    }
}

void test_quick_remove()
{
    std::vector<int> v{123,456, 789,200};
    std::cout<<v.size()<<std::endl;
    quick_remove_at(v, 1);
    for (int i : v){
        std::cout << i << ", ";
    }
    std::cout << '\n';
    std::cout<<v.size()<<std::endl;
    quick_remove_at(v,std::find(v.begin(), v.end(),123));
    for (int i : v){
        std::cout << i << ", ";
    }
    std::cout << '\n';
    std::cout<<v.size()<<std::endl;
}

void test_safe_access() {
    const size_t size{1000};
    vector<int> v(size,123);
    cout<<"1000 is "<< v[size]<<"\n";
    cout<<"1000 is "<< v[size+10]<<"\n";  // 当需要非常快的索引成员时，并能保证索引不越界，我们会使用[]快速访问vector实例，但是会引起crash
    cout<<"1000 is "<< v.at(size+10)<<"\n"; //at函数会检查给定的索引值是否越界，如果越界则返回一个异常
}
auto foo(float val1,float val2)
{
    return [=] (float step) mutable
    {
        return val1+ (val2-val1)*step;
    };
}

void test_lambda() {
    auto x=foo(0.0f,10.0f);
    cout<<x(0.5f)<<endl;
}

void test_sort() {
    vector<string> str{"some", "random", "words", "without", "order", "aaa", "yyy"};
    //auto str_vec=[begin(str), end(str))==false];
    assert(is_sorted(begin(str), end(str))==false);
    sort(begin(str), end(str));
    assert(is_sorted(begin(str), end(str))==true);

}
int main()
{
    test_sort();
    //test_safe_access();
    return 0;
}