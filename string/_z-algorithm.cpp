/*
  Z algorithm

  Constructs an array that contains the length of 
  the longest common prefix between S[0..N-1] and S[i..N-1] in linear time.
  This algorithm itself is also a linear time string matching algorithm.

  Complexity:
  O(|S|)

  Veriied:
  
 */
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> Z_algorithm(const string &s){
  vector<int> z(s.size(), 0);
  int l = 0, r = 0;
  for(int i = 1; i < s.size(); i++){
    if(i <= r) z[i] = z[i - l];
    else{
      int k = 0;
      while(i + k < s.size() && s[k] == s[i + k]) k++;
      z[i] = k;
      if(i + k - 1 > r) l = i, r = i + k - 1;
    }
  }
  return z;
}
vector<int> snuke_Z(const string &S){
  vector<int> A(S.size(), 0);
  A[0] = S.size();
  int i = 1, j = 0;
  while (i < S.size()) {
    while (i+j < S.size() && S[j] == S[i+j]) ++j;
    A[i] = j;
    if (j == 0) { ++i; continue;}
    int k = 1;
    while (i+k < S.size() && k+A[k] < j) A[i+k] = A[k], ++k;
    i += k; j -= k;
  }
  A[0] = 0;
  return A;
}

int main(){
  string s("ATGATCATAATGATCTGAATGGCCATAATCTGAA");
  cin >> s;
  vector<int> a = Z_algorithm(s);
  vector<int> b = snuke_Z(s);
  for(auto u : s) cout << u << " ";
  cout << endl;
  for(auto u : a) cout << u << " ";
  cout << endl;
  for(auto u : b) cout << u << " ";
  cout << endl;
}
