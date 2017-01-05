/*
  Boyer-Moore string matching
  オリジナル・バージョン

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
<<<<<<< HEAD
  for(int i = 0; i < M; i++) skip[pattern[i]] = M - i - 1;
=======
  for(int i = 0; i < M - 1; i++) skip[pattern[i]] = M - i - 1;
>>>>>>> ed4d28677342817d83621f6afa2ed00b1fdcbed3

  vector<int> pos;
  for(int i = M - 1; i < N; ){
    int j = M - 1;
    while(j >= 0 && text[i] == pattern[j]) --i, --j;
    if(j < 0){
      pos.push_back(i + 1);
      i += M + 1;
<<<<<<< HEAD
      //i += 1;
    }
    else i += skip[text[i]];
=======
    }else
      i += (M - j > skip[text[i]]) ? M - j : skip[text[i]];
    if(i % 10 == 0)cerr << i << " ";
>>>>>>> ed4d28677342817d83621f6afa2ed00b1fdcbed3
  }
  return pos;
}

int main(){
<<<<<<< HEAD
  // string t = "aaaaaaaaaa";
  // string s = "aa";
  string s, t;
  cin >> s;
  cin >> t;
  auto v = boyer_moore(s, t);
  for(int i = 0; i < v.size(); i++) cout << v[i] << endl;
=======
  string t = "aaaaaaaaaa";
  string s = "aa";
  cin >> t >> s;
  for(auto u : boyer_moore(t, s)) cout << u << endl;
  return 0;
>>>>>>> ed4d28677342817d83621f6afa2ed00b1fdcbed3
}
