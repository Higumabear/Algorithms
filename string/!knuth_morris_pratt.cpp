#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> KMP(string text, string pattern){
  int T = text.size(), P = pattern.size();
  vector<int> skip(P, 1);
  skip[0] = 1;
  for(int j = 1; j < P; j++){
    int k;
    for(k = 1; k < j; k++){
      int m = k;
      while(m < j && pattern[m] == pattern[m - k]) m++;
      if(m == j) break;
    }
    skip[j] = k;
  }
  for(int i = 0; i < P; i++) cout << skip[i] << " ";
  cout << endl;
  vector<int> ans;
  int i = 0, j;
  while(i < T){
    int tmpi = i, j = 0;
    while(text[tmpi] == pattern[j]) tmpi++, j++;
    if(j == P){
      ans.push_back(i);
      i++;
    }else i += skip[j];
  }
  return ans;
}

int main(){
  string s, t;
  cin >> s >> t;
  vector<int> a = KMP(s,t);
  for(auto u : a) cout << u << endl;
  return 0;
}
