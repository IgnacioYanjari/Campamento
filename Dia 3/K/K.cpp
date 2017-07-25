#include <iostream>
using namespace std;

int main(){
    string s1,s2;
    int t1 = 0, t2 = 0, q = 0;
    cin>>s1>>s2;
    for(int i=0; i<s1.size(); i++){
        if(s1[i]=='+') t1++;
        else t1--;
    }
    for(int i=0; i<s2.size(); i++){
        if(s2[i] == '+') t2++;
        else if(s2[i] == '-') t2--;
        else q++;
    }
}
