/*
  Boyer-Moore string matching
  不一致規則のみ取り入れたもの
  接尾辞規則は取り入れていない

  Verified : 
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_A
  
  最悪ケースの入力ではTLE
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
 */

#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> boyer_moore(const string &text, const string &pattern){
  int N = text.length(), M = pattern.length();
  vector<int> skip(0x100, M);
  for(int i = 0; i < M - 1; i++) skip[pattern[i]] = M - i - 1;

  vector<int> pos;
  for(int i = M - 1; i < N; ){
    int j = M - 1;
    while(j >= 0 && text[i] == pattern[j]) --i, --j;
    if(j < 0){
      pos.push_back(i + 1);
      i += M + 1;
    }else
      i += (M - j > skip[text[i]]) ? M - j : skip[text[i]];
  }
  return pos;
}

int main(){
  string t = "aaaaaaaaaa";
  string s = "aa";
  cin >> t >> s;
  for(auto u : boyer_moore(t, s)) cout << u << endl;
  return 0;
}
