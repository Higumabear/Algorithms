/*
  Rabin-Karp string matching

  Complexity:
  worst : O(NM)
  (but in my code, checking exact match is omitted.
  thus runs in O(N + M) time also in the worst cases)

  Verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
 */

#include <string>
#include <iostream>
#include <vector>

using namespace std;

vector<int> rabin_karp(const string &text, const string &pattern){
  int N = text.size(), M = pattern.size();
  const long long u = 0xff;
  const long long MOD[2] = {999999937LL, 1000000007LL};
  
  vector<int> ret;
  long long t[2] = {0, 0}, p[2] = {0, 0}, h[2] = {1, 1};
  for(int k = 0; k < 2; k++){
    for(int i = 0; i < M - 1; i++) h[k] = (h[k] * u) % MOD[k];
    for(int i = 0; i < M; i++){
      p[k] = (u * p[k] + pattern[i]) % MOD[k];
      t[k] = (u * t[k] + text[i]) % MOD[k];
    }
  }
  for(int i = 0; i <= N - M; i++){
    if(p[0] == t[0] && p[1] == p[1]){
      // int j = 0;
      // while(j < M && text[i + j] == pattern[j]) j++;
      // if(j == M) ret.push_back(i);
      
      ret.push_back(i); //nondeterministic
    }
    if(i < N - M){
      for(int k = 0; k < 2; k++){
	t[k] = (u * (t[k] - text[i] * h[k]) + text[i + M]) % MOD[k];
	if(t[k] < 0) t[k] += MOD[k];
      }
    }
  }
  return ret;
}

int main(){
  string s, t;
  cin >> s >> t;
  vector<int> match = rabbin_karp(s, t);
  for(auto u : match) cout << u << endl;
}
