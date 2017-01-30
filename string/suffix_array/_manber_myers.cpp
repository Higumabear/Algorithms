#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100000;

int k, L;
int rank[MAXN], sa[MAXN], tmp[MAXN];

// compare rank[i], rank[i + k] and rank[j], rank[j + k]
bool comp(int i, int j){
  if(rank[i] != rank[j]) return rank[i] < rank[j];
  int ranki = i + k <= L ? rank[i + k] : -1;
  int rankj = j + k <= L ? rank[j + k] : -1;
  return ranki < rankj;
}

void build_sa(const string &s){
  L = s.size();
  for(int i = 0; i <= L; i++){
    sa[i] = i;
    rank[i] = i < L ? s[i] : -1;
  }

  for(k = 1; k <= L; k *= 2){
    sort(sa, sa + L + 1, comp);

    tmp[sa[0]] = 0;
    for(int i = 1; i <= L; i++)
      tmp[sa[i]] = tmp[sa[i - 1]] + comp(sa[i - 1], s[i]);
    for(int i = 0; i <= L; i++)
      rank[i] = tmp[i];
  }
}

int main(){
  string s("abracadabra");
  
  build_sa(s);

  for(int i = 0; i <= L; i++)
    cout << sa[i] << endl;
}
