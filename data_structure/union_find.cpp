#include <cstdio>
#include <iostream>

using namespace std;

class union_find{
public:
  union_find();
  union_find(int num){
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

int main(int argc, char **argv){
  int n, q;
  scanf("%d %d", &n, &q);

  union_find uf(n);
  for(int i = 0; i < q; i++){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    if(a == 0)
      uf.unite(b, c);
    else
      cout << uf.same(b, c) << endl;
  }
}
