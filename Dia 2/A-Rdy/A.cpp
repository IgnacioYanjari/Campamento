#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <utility>
using namespace std;

int main(){
  // Avoids iostream and stdio synchronization
std::ios_base::sync_with_stdio(false);

// Avoids flushing std::cout before reading from std::cin
std::cin.tie(nullptr);
	int N,M,K;
	cin>>N>>M>>K;
	char matrix[N+2][M+2];
	for (int i =0 ; i <= N+1 ; i++){
		for (int j=0 ; j <= M+1 ; j++){
			matrix[i][j]='#';
		}
	}

	for (int i =1 ; i <= N ; i++){

		for (int j=1 ; j <= M ; j++){
			cin>>matrix[i][j];
		}

	}

	// for (int i =0 ; i <= N+1 ; i++){
	// 	for (int j=0 ; j <= M+1 ; j++){
	// 		cout<<matrix[i][j]<<" ";
	// 	}
	// 	cout<<"\n";
	// }

	int marked[N+2][M+2];
	for (int i =0 ; i <= N+1 ; i++){
		for (int j=0 ; j <= M+1 ; j++){
			marked[i][j]=-1;
		}
	}


	int solution[N+2][M+2];
	for (int i =0 ; i <= N+1 ; i++){
		for (int j=0 ; j <= M+1 ; j++){
			solution[i][j]=0;
		}
	}
  int grupo=0;
  std::vector<int> tableofsum;
	for (int i=1 ; i <= N ;i++){
		for (int j=1 ; j <= M ; j++){
			int suma=0;
			if(matrix[i][j]=='.' && marked[i][j]==-1){
				suma=0;
				//std::vector< pair<int,int> > pos();
				stack<pair<int,int>> a;
				a.push(make_pair(i,j));
				marked[i][j] = grupo;
				//cout << a.top().first << " " << a.top().second << endl;
				while(!a.empty()){
					auto x = a.top().first;
					auto y = a.top().second;	
					a.pop();
					if (marked[x+1][y] == -1){
						if(matrix[x+1][y] == '.'){
							//cout<<"x :"<<x+1<<" y :"<<y<<"\n";
							a.push(make_pair(x+1,y));
							marked[x+1][y]=grupo;
						}
						if(matrix[x+1][y] == '*'){
							suma++;
						}
					}
					if (marked[x][y+1] == -1){
						if(matrix[x][y+1] == '.'){
							//cout<<"x :"<<x<<"y :"<<y+1<<"\n";
							a.push(make_pair(x,y+1));
							marked[x][y+1]=grupo;
						}
						if(matrix[x][y+1] == '*'){
							suma++;
						}
					}
					if (marked[x-1][y] == -1){
						if(matrix[x-1][y] == '.'){
							//cout<<"x :"<<x-1<<"y :"<<y<<"\n";
							a.push(make_pair(x-1,y));
							marked[x-1][y]=grupo;
						}
						if(matrix[x-1][y] == '*'){
							suma++;
						}
					}
					if (marked[x][y-1] == -1){
						if(matrix[x][y-1] == '.'){
							a.push(make_pair(x,y-1));
							marked[x][y-1]=grupo;
						}
						if(matrix[x][y-1] == '*'){
							suma++;
						}
					}
				}

				tableofsum.push_back(suma);
				grupo++;
			}
		}
	}

  for (size_t i = 1; i <= N ; i++) {
    for (size_t j = 1; j <= M; j++) {
        if( marked[i][j] < tableofsum.size() ){
          solution[i][j] = tableofsum[marked[i][j]];
        }
    }
  }

  // for (size_t i = 1; i <= N ; i++) {
  //   for (size_t j = 1; j <= M; j++) {
  //     std::cout <<"\t"<< marked[i][j];
  //   }
  //   std::cout << '\n';
  // }
  // for (size_t i = 1; i <= N ; i++) {
  //   for (size_t j = 1; j <= M; j++) {
  //     std::cout <<"\t"<< solution[i][j];
  //   }
  //   std::cout << '\n';
  // }

  for(int i = 0 ; i<K ;i++){
		int l,r;
		cin>>l>>r;
		cout<<solution[l][r]<<"\n";
	}

}
