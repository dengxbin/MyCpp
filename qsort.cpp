#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> ret;
        if(k>input.size())
            return ret;
        sort(input.begin(), input.end());
        for(int i = 0; i < k;i++){
            ret.push_back(input[i]);
        }
        return ret;
    }
};

class Solution_heap {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k)
    {
        vector<int> result;
        int len = input.size();
        if(input.empty() || k<=0 || len < k) return result;
         
        multiset<int, greater<int> > leastNumbers; // 从大到小排序
        multiset<int, greater<int> >::iterator iterGreater; // 定义迭代器
        for( auto&& num:input ){
            if (leastNumbers.size()<k)
            {
                leastNumbers.insert(num);
            }else{
                auto bigNum=leastNumbers.begin();
                if (num<*bigNum)
                {
                    leastNumbers.erase(bigNum);
                    leastNumbers.insert(num);
                }
            }          
        }
        for(auto&& num:leastNumbers){
            result.push_back(num);
        }

    }
};

class Solution_qsort {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k)
    {
        vector<int> ret;
        if(k>input.size())
            return ret;
        qsort(input,0,input.size()-1);
        for(int i = 0; i < k;i++){
            ret.push_back(input[i]);
        }
        return ret;
        
    }
    void qsort(vector<int> &input,int low,int up){
        if(low<up){
            int mid=qsort_helper(input,low,up);
            qsort(input,low,mid-1);
            qsort(input,mid+1,up);
        }
    }
    int qsort_helper(vector<int> &input,int l,int r){
        int pivot=input[r];
        int i=l-1;
        for(int j=l;j<r;j++){
            if(input[j]<=pivot){
                i++;
                swap(input[i],input[j]);
            }
        }
        swap(input[i+1],input[r]);
        return i+1;
    }
};
