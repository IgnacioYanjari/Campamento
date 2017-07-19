#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main(){
	int N,M,A,B;
    int P;
	while(cin>>N){
		if(N == 0) return 0;
		cin>>M;
		double adj[N][N];
        // inicializar en 0 la matriz ADJ
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                adj[i][j]=0.0;
            }
        }

		for (int i = 0 ; i < M ; i++){
			cin>>A>>B>>P;
			adj[A-1][B-1]=P*0.01;
			adj[B-1][A-1]=P*0.01;
		}

        // for(int i=0;i<N;i++){
        // 	for(int j=0;j<N;j++){
        // 		cout<<adj[i][j]<<" ";
        // 	}
        //     cout<<"\n";
        // }
        //
        // cout<<"\n";
        double dist[N][N];
        // for(int i=0;i<N;i++){
        //     for(int j=0;j<N;j++){
        //         dist[i][j]=0;
        //     }
        // }
        for(int i=0;i<N;i++){
                dist[i][i]=0.0;
        }

        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                dist[i][j]=adj[i][j];
            }
        }

        // for(int i=0;i<N;i++){
        //     for(int j=0;j<N;j++){
        //         cout<<dist[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
        // cout<<"\n";

	    for(int k=0; k < N; k++){
            for(int i=0; i < N; i++){
                for(int j=0; j < N; j++){
                    if(i==j||i==k||j==k) continue;
                    dist[i][j]=max(dist[i][j], dist[i][k]*dist[k][j]);
                    // if(i!=j&&j!=k&&i!=k&&dist[i][k]*dist[k][j] > dist[i][j])
                    //     dist[i][j]=dist[i][k]*dist[k][j];
                }
            }
        }
        // for(int i=0;i<N;i++){
        // 	for(int j=0;j<N;j++){
        // 		cout<<dist[i][j]<<" ";
        // 	}
        //     cout<<"\n";
        // }
        cout<<std::fixed;
        cout<<setprecision(6)<<dist[0][N-1]*100<<" percent\n";
    }
}
