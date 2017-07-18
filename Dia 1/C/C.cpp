#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main (){
	size_t n;
	cin>>n;
	int matrix[n][n]={0};
	for (int i = 0 ; i < n ;i++){
		for(int j = 0 ; j < n ;j++ ){
			cin>>matrix[i][j];
		}
	}
	int sol[n+1][n+1];
	for(int i=0 ; i <= n ;i++){
		for(int j = 0 ; j <= n ;j++){
			sol[i][j]=0;
		}
	}

	for(int i=1 ; i <= n ;i++){
		for(int j = 1 ; j <= n ;j++){
			sol[i][j] = sol[i-1][j] + sol[i][j-1] - sol[i-1][j-1] + matrix[i-1][j-1];
		}
	}

	for (int i = 1 ; i <= n ;i++){
		for(int j = 1 ; j <= n ;j++ ){
			cout << sol[i][j]<<" ";
		}
		cout<<"\n";
	}

	return 0;
}