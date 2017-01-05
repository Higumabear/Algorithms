#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> boyer_moore(string text, string pattern){
  int N = text.length(), M = pattern.length();
  vector<int> skip(0x100, M);
  for(int i = 0; i < M; i++) skip[pattern[i]] = M - i - 1;

  vector<int> pos;
  for(int i = M - 1; i < N; ){
    int j = M - 1;
    while(j >= 0 && text[i] == pattern[j]) i--, j--;
    if(j < 0){
      pos.push_back(i + 1);
      i += M + 1;
      //i += 1;
    }
    else i += skip[text[i]];
  }
  return pos;
}

int main(){
  // string t = "aaaaaaaaaa";
  // string s = "aa";
  string s, t;
  cin >> s;
  cin >> t;
  auto v = boyer_moore(s, t);
  for(int i = 0; i < v.size(); i++) cout << v[i] << endl;
}
