#include <iostream>
using namespace std;
int digital_root(int n){
    int root=0;
    if(n/10 == 0) return n;
    while(n>0){
        root+=n%10;
        n/=10;
    }
    return root;
}

int digits(int n){
    int cont=0;
    if(n/10 == 0) return 1;
    while(n>0){
        n/=10;
        cont++;
    }
    return cont;
}

bool is_prime(int n){
    if(n == 1) return 0;
    for(int i=2;i<n;i++){
        if(n%i==0) return 0;
    }
    return 1;
}

void print_spaces(int n){
    for(int i=0;i<n;i++){
        cout<<" ";
    }
}

int main(){
    int n,root,n_digits;
    while(cin>>n){
        if(n==0) return 0;
        root=n;
        while(!is_prime(root) && root/10 != 0){
            root=digital_root(root);
        }
        if(is_prime(root)){
            n_digits=digits(n);
            print_spaces(7-n_digits);
            cout<<n<<" ";
            n_digits=digits(root);
            print_spaces(7-n_digits);
            cout<<root<<"\n";
        }else{
            n_digits=digits(n);
            print_spaces(7-n_digits);
            cout<<n<<"    none\n";
        }
    }
}
