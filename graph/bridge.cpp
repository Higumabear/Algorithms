/*
	Enumerate bridges in graph
	
	Complexity:
	O(V + E)
	
	verified:
	http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B
	
*/
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

typedef long long ll;
#define INF 1 << 29
#define LLINF 1LL << 60
#define EPS 1e-6
#define ALL(c) (c).begin(), (c).end()
#define CNT(c,x) count(ALL(c),x)
#define dump(x)  cerr << #x << " = " << (x) << endl;
template<typename A, size_t N, typename T>
void FILL(A (&array)[N], const T &val){
    std::fill( (T*)array, (T*)(array+N), val );
}

using namespace std;

class Bridge{
  int V;
  const vector<vector<int> > &g;
  vector<pair<int, int> > bridge;
  vector<int> ord, low;
  vector<bool> vis;
  int k;
  
public:
  Bridge(const vector<vector<int> > &g) :
    g(g), V(g.size()), k(0), ord(V, -1), low(V), vis(V, false) {}

  vector<pair<int, int> > decomp(){
    for(int i = 0; i < V; i++)
      if(!vis[i]) dfs(i, -1);
    return bridge;
  }
  
private:
  
  void dfs(int idx, int prv){
    ord[idx] = k++;
    low[idx] = ord[idx];
    vis[idx] = true;
    for(int i = 0; i < g[idx].size(); i++){
      int nxt = g[idx][i];
      if(!vis[nxt]){
	dfs(nxt, idx);
	low[idx] = min(low[idx], low[nxt]);
	if(ord[idx] < low[nxt])
	  bridge.push_back(make_pair(min(idx, nxt),
				     max(idx, nxt)));
      }else if(nxt != prv){
	low[idx] = min(low[idx], ord[nxt]);
      }
    }
  }
};

int main(){
  int V, E;
  vector<vector<int> > g;
  scanf("%d %d", &V, &E);
  g.resize(V);

  for(int i = 0; i < E; i++){
    int u, v;
    scanf("%d %d", &u, &v);
    
    g[u].push_back(v);
    g[v].push_back(u);
  }

  Bridge br(g);
  vector<pair<int, int> > ed = br.decomp();
  sort(ALL(ed));
  for(int i = 0; i < ed.size(); i++)
    cout << ed[i].first << " " << ed[i].second << endl;
  return 0;
}
