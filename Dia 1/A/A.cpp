#include <iostream>
using namespace std;
int main(){
	int n,k,q;
	cin>>n>>k>>q;
	int aux[200000+3]={0};
	int l,r;
	for (int i = 1 ; i <= n ; i++){
		cin>>l>>r;
		aux[l+1] = aux[l+1] + 1;
		aux[r+2] = aux[r+2] -1;
	}
	int temp[200000+3]={0};
	int cont = 0;
	for (int i=1 ; i<=200000+1  ; i++){
		cont = cont + aux[i];
		temp[i] = cont;
	}
	int ans[200000+3]={0};
	for (int i = 1 ; i <= 200000+1 ; i++){
		if(temp[i] >= k) ans[i] = ans[i-1] +1;
		else ans[i] = ans[i-1];
	}
	int in,fin;
	for (int i =0 ; i<q ;i++){
		cin>>in>>fin;
		if (in == fin){
			if(temp[fin+1] >= k ) cout<<"1\n";
			else cout <<"0\n";
		}
		else cout<<ans[fin+1]-ans[in]<<"\n";
	}
}