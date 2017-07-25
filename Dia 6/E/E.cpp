#include <iostream>
#include <cstddef> // size_t
#include <utility> // pair
#include <vector>  // vector
#include <algorithm>
#include <cstdint>     // SIZE_MAX
#include <climits>      // numeric_limits
#include <queue>       // queue
#include <type_traits> // is_arithmetic
#include <iterator> // back_inserter
#include <stack>

typedef long long ll;
using namespace std;
class Dinic {
    struct edge {
        int to, rev;
        ll f, cap;
    };

    vector<vector<edge>> g;
    vector<ll> dist;
    vector<int> q, work;
    int n, sink;

    bool bfs(int start, int finish) {
        dist.assign(n, -1);
        dist[start] = 0;
        int head = 0, tail = 0;
        q[tail++] = start;
        while (head < tail) {
            int u = q[head++];
            for (const edge &e : g[u]) {
                int v = e.to;
                if (dist[v] == -1 and e.f < e.cap) {
                    dist[v] = dist[u] + 1;
                    q[tail++] = v;
                }
            }
        }
        return dist[finish] != -1;
    }

    ll dfs(int u, ll f) {
        if (u == sink)
            return f;
        for (int &i = work[u]; i < (int)g[u].size(); ++i) {
            edge &e = g[u][i];
            int v = e.to;
            if (e.cap <= e.f or dist[v] != dist[u] + 1)
                continue;
            ll df = dfs(v, min(f, e.cap - e.f));
            if (df > 0) {
                e.f += df;
                g[v][e.rev].f -= df;
                return df;
            }
        }
        return 0;
    }

public:
    Dinic(int n) {
        this->n = n;
        g.resize(n);
        dist.resize(n);
        q.resize(n);
    }

    void add_edge(int u, int v, ll cap) {
        edge a = {v, (int)g[v].size(), 0, cap};
        edge b = {u, (int)g[u].size(), 0, cap}; //Poner cap en vez de 0 si la arista es bidireccional
        g[u].push_back(a);
        g[v].push_back(b);
    }

    ll max_flow(int source, int dest) {
        sink = dest;
        ll ans = 0;
        while (bfs(source, dest)) {
            work.assign(n, 0);
            while (ll delta = dfs(source, LLONG_MAX))
                ans += delta;
        }
        return ans;
    }
};


int main(){
	int n, group=0,group2=0;
	char k;
	while(cin>>n){
		group=0;
		group2=0;
		std::vector<std::vector<int> > lr(n,std::vector<int> (n,-1));
		std::vector<std::vector<int> > ud(n,std::vector<int> (n,-1));
		std::vector<int> cont(10000,0);

		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cin>>k;

				if(k=='X' && j<n-1 && cont[group]!=0){
					group++;
				}else if(k=='.'){
					lr[i][j]=group;
					cont[group]++;
				}
				if(j==n-1){
					group++;
				}
			}
		}
		// group=0;
		cont=std::vector<int> (10000,0);
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(lr[j][i]==-1 && j<n-1 && cont[group2]!=0){
					group2++;
				}else if(lr[j][i]!=-1){
					ud[j][i]=group2;
					cont[group2]++;
				}
				if(j==n-1){
					group2++;
				}
			}
		}

		Dinic d( std::max(group,group2) );
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(lr[i][j]!=-1 && ud[i][j]!=-1 ){
            std::cout << "lr : "<< lr[i][j]<<" ud :"<<ud[i][j] << '\n';
						d.add_edge(lr[i][j], ud[i][j],1);
				}
			}
		}
    // for(int i = 0 ; i < n ; i++){
    //   d.add_edge(i,std::max(group,group2) , 1);
    //   d.add_edge(i,std::max(group,group2) + 1 , 1 );
    // }
		cout<<d.max_flow(0,n)<<"\n";
	}
}
