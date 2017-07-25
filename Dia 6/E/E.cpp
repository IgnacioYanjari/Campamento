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
#include <map> 
using namespace std;

typedef vector<vector<int> > graph;
typedef long long ll;                           

class undirected_graph {
  std::vector<std::vector<size_t>> adj_edges;
  std::vector<std::pair<size_t, size_t>> edge_list;

public:
  explicit undirected_graph(size_t num_vertices) : adj_edges(num_vertices) {}

  size_t add_edge(size_t u, size_t v) {
    edge_list.emplace_back(u, v);
    const size_t edge_id = edge_list.size() - 1;
    adj_edges[u].push_back(edge_id);
    adj_edges[v].push_back(edge_id);
    return edge_id;
  }

  size_t num_vertices() const {
    return adj_edges.size();
  }
  size_t num_edges() const {
    return edge_list.size();
  }

  size_t source(size_t e) const {
    return edge_list[e].first;
  }
  size_t target(size_t e) const {
    return edge_list[e].second;
  }

  const std::vector<size_t>& out_edges(size_t v) const {
    return adj_edges[v];
  }
  const std::vector<size_t>& in_edges(size_t v) const {
    return adj_edges[v];
  }

  size_t degree(size_t v) const {
    return adj_edges[v].size();
  }
  size_t out_degree(size_t v) const {
    return degree(v);
  }
  size_t in_degree(size_t v) const {
    return degree(v);
  }
};

template <typename Graph>
std::size_t hopcroft_karp_maximum_matching(const Graph& g) {
  // Note: pair_of can be used to query the selected pairs.
  const size_t num_vertices = g.num_vertices();
  const size_t nil = num_vertices; // The null vertex
  std::vector<size_t> pair_of(num_vertices, nil);
  std::vector<size_t> dist(num_vertices + 1);
  std::vector<size_t> set_a, set_b;

  auto separate_vertices = [&] {
    std::vector<signed char> color(num_vertices);
    std::function<void(size_t)> dfs_visit;
    dfs_visit = [&](const size_t u) {
      color[u] == 1 ? set_a.push_back(u) : set_b.push_back(u);
      for (const auto e : g.out_edges(u)) {
        const size_t v = (u == g.source(e)) ? g.target(e) : g.source(e);
        if (color[v])
          continue;
        color[v] = -color[u];
        dfs_visit(v);
      }
    };
    for (size_t v = 0; v < num_vertices; ++v) {
      if (color[v] != 0)
        continue;
      color[v] = 1;
      dfs_visit(v);
    }
  };
  auto bfs = [&] {
    std::queue<size_t> q;
    for (const size_t a : set_a) {
      if (pair_of[a] == nil) {
        dist[a] = 0;
        q.push(a);
      } else
        dist[a] = SIZE_MAX;
    }
    dist[nil] = SIZE_MAX;
    while (!q.empty()) {
      const size_t a = q.front();
      q.pop();
      if (dist[a] >= dist[nil])
        continue;
      for (const auto e : g.out_edges(a)) {
        const size_t b = (a == g.source(e)) ? g.target(e) : g.source(e);
        if (dist[pair_of[b]] != SIZE_MAX)
          continue;
        dist[pair_of[b]] = dist[a] + 1;
        q.push(pair_of[b]);
      }
    }
    return dist[nil] != SIZE_MAX;
  };
  std::function<bool(size_t)> dfs = [&](const size_t a) {
    if (a == nil)
      return true;
    for (const auto e : g.out_edges(a)) {
      const auto b = (a == g.source(e)) ? g.target(e) : g.source(e);
      if (dist[pair_of[b]] != dist[a] + 1)
        continue;
      if (!dfs(pair_of[b]))
        continue;
      pair_of[b] = a;
      pair_of[a] = b;
      return true;
    }
    dist[a] = SIZE_MAX;
    return false;
  };

  separate_vertices();
  size_t num_matching = 0;
  while (bfs()) {
    for (const size_t a : set_a)
      if (pair_of[a] == nil && dfs(a))
        ++num_matching;
  }
  return num_matching;
}

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
		
		undirected_graph g(max(group,group2));
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(lr[i][j]!=-1 && ud[i][j]!=-1 ){
					//if(check.find(std::make_pair(j,i)) == check.end()){
						g.add_edge(lr[i][j], ud[i][j]);
					//}

				}
			}
		}
		// cout<<is_bipartite(g)<<endl;
		auto result = hopcroft_karp_maximum_matching(g);
		if( result == 0)
			cout<<"0"<<"\n";
		else
			cout<<result+3<<"\n";
	}
}    