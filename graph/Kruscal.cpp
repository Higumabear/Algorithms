#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
#include <cmath>
#include <cstdio>
#include <string>
#include <numeric>
#include <algorithm>

using namespace std;

typedef long long ll;
#define INF 1 << 29
#define LLINF 1LL << 61
#define EPS 1e-6
#define ALL(c) (c).begin(), (c).end()
#define dump(x)  cerr << #x << " = " << (x) << endl;
inline int s2i(string s) {int v; istringstream sin(s);sin>>v;return v;}
template<class T> inline string i2s(T x) {ostringstream sout;sout<<x;return sout.str();}
template<typename A, size_t N, typename T> inline void FILL(A (&array)[N], const T &val){ std::fill( (T*)array, (T*)(array+N), val );}
const double PI  = acos(-1.0);

class UnionFind{
public:
  UnionFind();
  UnionFind(int num){
    for(int i = 0; i < num; i++) parent[i] = i, rank[i] = 0;
  }

  bool same (int x, int y) { return find(x) == find(y); }
  void unite(int x, int y) {
    x = find(x), y = find(y);
    if(x == y) return;
    if(rank[y] > rank[x]){
      parent[x] = y;
    }else{
      parent[y] = x;
      if(rank[x] == rank[y]) rank[x]++;
    }
  }

private:
  int rank[200001], parent[200001];

  int find(int x){
    while(x != parent[x]) x = parent[x];
    return x;
  }
};

struct edge{
  int from, to, cost;
  edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
  bool operator<(const edge &r) const{ return cost < r.cost; }
  bool operator>(const edge &r) const{ return cost > r.cost; }
};

vector<vector<edge> > g;

void add_edge(int from, int to, int cost){//2way
  g[from].push_back(edge(from, to, cost));
  g[to].push_back(edge(to, from, cost));
}

pair<int, vector<edge> > kruscal(vector<vector<edge> > g){
  int V = g.size();
  priority_queue<edge, vector<edge>, greater<edge> > Q;

  for(int i = 0; i < V; i++)
    for(int j = 0; j < g[i].size(); j++)
      if(i < g[i][j].to) Q.push(g[i][j]);

  int sum = 0;
  vector<edge> mst;
  UnionFind uf(V);
  for(int i = 0; i < V - 1; i++){
    edge e = Q.top(); Q.pop();
    if(uf.same(e.from, e.to)) i--;
    else{
      sum += e.cost;
      mst.push_back(e);
      uf.unite(e.from, e.to);
    }
  }
  return make_pair(sum, mst);
}

int main(int argc, char **argv){
  int n, q;
  scanf("%d %d", &n, &q);

  g.resize(n);
  for(int i = 0; i < q; i++){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    add_edge(a, b, c);
  }
  pair<int, vector<edge> > MST = kruscal(g);
  printf("%d\n", MST.first);
}
