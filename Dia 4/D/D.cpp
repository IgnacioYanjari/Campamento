#include <iostream>
#include <vector>
#include <cstddef>    // size_t
#include <functional> // function
#include <queue>      // priority_queue
#include <stdexcept>  // logic_error
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class directed_graph {
  std::vector<std::vector<size_t>> outedges, inedges;
  std::vector<std::pair<size_t, size_t>> edge_list;

public:
  explicit directed_graph(size_t n_verts)
      : outedges(n_verts), inedges(n_verts) {}

  size_t add_edge(size_t src, size_t tgt) {
    edge_list.emplace_back(src, tgt);
    const size_t edge_id = edge_list.size() - 1;
    outedges[src].push_back(edge_id);
    inedges[tgt].push_back(edge_id);
    return edge_id;
  }

  size_t num_vertices() const { return outedges.size(); }
  size_t num_edges() const { return edge_list.size(); }

  size_t source(size_t e) const { return edge_list[e].first; }
  size_t target(size_t e) const { return edge_list[e].second; }

  const std::vector<size_t> &out_edges(size_t v) const { return outedges[v]; }
  const std::vector<size_t> &in_edges(size_t v) const { return inedges[v]; }

  size_t out_degree(size_t v) const { return outedges[v].size(); }
  size_t in_degree(size_t v) const { return inedges[v].size(); }
};

template <typename Graph, typename Comp, typename UnaryFunction>
void prioritized_topological_sort(const Graph& g, Comp comp,
                                  UnaryFunction output_vertex) {
  const size_t num_vertices = g.num_vertices();
  const size_t num_edges = g.num_edges();
  std::priority_queue<size_t, std::vector<size_t>, Comp> queue(comp);
  std::vector<size_t> in_degree(num_vertices);

  for (size_t e = 0; e != num_edges; ++e)
    ++in_degree[g.target(e)];

  for (size_t v = 0; v != num_vertices; ++v)
    if (!in_degree[v])
      queue.push(v);

  while (!queue.empty()) {
    const size_t src = queue.top();
    queue.pop();
    output_vertex(src);

    for (const auto e : g.out_edges(src)) {
      const auto tgt = g.target(e);
      --in_degree[tgt];
      if (!in_degree[tgt])
        queue.push(tgt);
    }
  }
}

template <typename Graph>
std::vector<size_t> topological_sort(const Graph& g) {
  enum class colors { white, gray, black };
  const size_t num_v = g.num_vertices();
  std::vector<size_t> list(num_v);
  std::vector<colors> color(num_v, colors::white);
  size_t cur_pos = num_v;

  std::function<void(size_t)> dfs_visit;
  dfs_visit = [&](const size_t src) {
    color[src] = colors::gray;
    for (const auto e : g.out_edges(src)) {
      const size_t tgt = g.target(e);
      if (color[tgt] == colors::white)
        dfs_visit(tgt);
      else if (color[tgt] == colors::gray)
        throw std::logic_error("Not a DAG");
    }
    color[src] = colors::black;
    list[--cur_pos] = src;
  };

  for (size_t v = 0; v != num_v; ++v)
    if (color[v] == colors::white)
      dfs_visit(v);

  return list;
}

static vector<size_t>
smallest_numbered_first_toposort(const directed_graph& g) {
  vector<size_t> list;
  list.reserve(g.num_vertices());
  prioritized_topological_sort(g, std::greater<size_t>(),
                               [&](size_t v) { list.push_back(v); });
  return list;
}

int main(){
	int n, m, cases=1;
	while(cin>>n){
		std::map<string, int> stoi;
		std::map<int, string> itos;
		string aux,aux2;
		for(int i=0;i<n;i++){
			cin>>aux;
			stoi[aux]=i;
			itos[i]=aux;
		}
		directed_graph graph(n);
		cin>>m;
		for(int i=0;i<m;i++){
			cin>>aux>>aux2;
			graph.add_edge(stoi[aux], stoi[aux2]);
		}
		std::vector<size_t> list;
		list=smallest_numbered_first_toposort(graph);

		cout<<"Case #"<<cases<<": Dilbert should drink beverages in this order: ";
		for(int i=0;i<list.size();i++){
			if(i!=list.size()-1){
				cout<<itos.at(list[i])<<" ";
			}else{
				cout<<itos.at(list[i])<<".\n";
			}
		}
		cout<<"\n";
		cases++;
	}
}
