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

pair<int, vector<edge> > prim(vector<vector<edge> > g){
  int V = g.size();
  priority_queue<edge, vector<edge>, greater<edge> > Q;
  vector<bool> use(V, false);
  Q.push(edge(-1, 0, 0));

  int sum = 0;
  vector<edge> mst;
  while(!Q.empty()){
    edge e = Q.top(); Q.pop();
    if(use[e.to]) continue;
    use[e.to] = true;
    sum += e.cost;
    mst.push_back(e);
    for(int i = 0; i < g[e.to].size(); i++)
      if(!use[g[e.to][i].to])Q.push(g[e.to][i]); 
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
  pair<int, vector<edge> > MST = prim(g);
  printf("%d\n", MST.first);
}
