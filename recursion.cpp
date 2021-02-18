#include <iostream>
#include <string>
using namespace std;



void printBinaryHelper(int num, string out){
    if(num==0){
        cout<<out<<endl;
    }else{
        printBinaryHelper(num-1,"0"+out);
        printBinaryHelper(num-1,"1"+out);
    }
}

void printAllBinary(int num)
{
    printBinaryHelper(num,"");
}
int main(){
    printAllBinary(4);
    return 0;
}