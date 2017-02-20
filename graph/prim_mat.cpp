#include <vector>
#include <iostream>
#include <queue>

using namespace std;

const int INF = 1 << 29;

// int prim(const vector<vector<int> > &g){
//   int V = g.size(), res = 0;
//   vector<bool> used(V, false);
//   vector<int> mincost(V, INF);
//   mincost[0] = 0;
  
//   while(true){
//     int v = -1;
//     for(int u = 0; u < V; u++)
//       if(!used[u] && (v == -1 || mincost[u] < mincost[v])) v = u;
    
//     if(v == -1) break;
//     used[v] = true;
//     res += mincost[v];
//     for(int u = 0; u < V; u++)
//       mincost[u] = min(mincost[u], g[v][u]);
//   }
//   return res;
// }

typedef pair<int, int> PII;

pair<int, vector<PII> >
prim(const vector<vector<int> > &g){
  int V = g.size();
  //priority_queue<pair<int, PII> > Q;
  priority_queue<pair<int, PII> ,
  		 vector<pair<int, PII> >,
  		 greater<pair<int, PII> > > Q;

  vector<bool> used(V, false);
  int res = 0;
  vector<PII> edges;

  Q.push(make_pair(0, make_pair(-1, 0)));
  while(!Q.empty()){
    int cost = Q.top().first;
    PII e = Q.top().second; Q.pop();

    int cur = e.second, prev = e.first;
    if(used[cur]) continue;
    used[cur] = true;
    if(prev != -1){
      res += cost;
      edges.push_back(e);
    }
    for(int next = 0; next < V; next++)
      if(!used[next] && g[cur][next] != INF)
  	Q.push(make_pair(g[cur][next], make_pair(cur, next)));
  }
  return make_pair(res, edges);
}

int main(){
  int n;
  cin >> n;
  
  vector<vector<int> > g(n, vector<int>(n));
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cin >> g[i][j];
      if(g[i][j] == -1) g[i][j] = INF;
    }
  }
  pair<int, vector<PII> > mst = prim(g);
  cout << mst.first << endl;
}
