#include <iostream>
using namespace std;

int main(){
    int m,n;
    cin>>m>>n;
    if((m*n)%2==0){
        cout<<"[:=[first]\n";
    }else{
        cout<<"[second]=:]\n";
    }
}
