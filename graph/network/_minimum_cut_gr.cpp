#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int V;
int g[500][500];

int minimum_cut(){
  //int V = g.size();
  vector<int> v(V);
  for(int i = 0; i < V; i++) v[i] = i;

  int ans = 1 << 29;
  for(int m = V; m > 1; m--){
    vector<int> weight(m, 0);
    int s, t, W;
    for(int k = 0; k < m; k++){
      s = t;
      t = max_element(weight.begin(), weight.end()) - weight.begin();
      W = weight[t];
      weight[t] = -1;
      for(int i = 0; i < m; i++)
	if(weight[i] >= 0) weight[i] += g[v[t]][v[i]];
    }
    for(int i = 0; i < m; i++){
      g[v[s]][v[i]] += g[v[t]][v[i]];
      g[v[i]][v[s]] += g[v[i]][v[t]];
    }
    v.erase(v.begin() + t);
    ans = min(ans, W);
  }
  return ans;
}

int main(){
  int M;
  while(scanf("%d %d", &V, &M) != EOF){
    memset(g, 0, sizeof(g));
    for(int i = 0; i < M; i++){
      int s, t, C;
      scanf("%d %d %d", &s, &t, &C);
      g[s][t] = g[t][s] = C;
    }
    printf("%d\n", minimum_cut());
  }
}
