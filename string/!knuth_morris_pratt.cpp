#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> KMP(string text, string pattern){
  int T = text.size(), P = pattern.size();
  vector<int> fail(P + 1, -1), ret;
  fail[1] = 0;
  int i = 2, j = 0;
  while(i <= P){
    if(pattern[i - 1] == pattern[j]) fail[i] = j + 1, i++, j++;
    else if(j > 0) j = fail[j];
    else fail[i] = 0, i++;
  }
  for(i = 0, j = 0; i < T; i++){
    while(text[i] != pattern[j] && j != -1) j = fail[j];
    if(++j == P) ret.push_back(i - P + 1);
  }
  for(int i = 0; i < P; i++){
    cout << pattern[i] << '\t';
  }
  cout << endl;
  for(int i = 0; i < P; i++){
    cout << fail[i] << '\t';
  }
  cout << endl;
  return ret;
}

int main(){
  string s, t;
  cin >> s >> t;
  vector<int> a = KMP(s,t);
  for(int i = 0; i < a.size(); i++) 
    cout << a[i] << endl;
  return 0;
}
