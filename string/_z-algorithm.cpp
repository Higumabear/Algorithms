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
#include <time.h>

using namespace std;

vector<int> Z_algorithm(const string &s){
  vector<int> z(s.size(), 0);
  int l = 0, r = 0;
  for(int i = 1; i < s.size(); i++){
    if(z[i - l] <= r - i) z[i] = z[i - l];
    else{
      int k = max(0, r - i);
      while(i + k < s.size() && s[k] == s[i + k]) k++;
      z[i] = k;
      l = i, r = i + k - 1;
    }
  }
  return z;
}

int main(){
  string t, p;
  cin >> t >> p;
  int l = p.size();
  p += "$" + t;
  vector<int> z = Z_algorithm(p);
  for(int i = l + 1; i < z.size(); i++) 
    if(z[i] == l) cout << i - l - 1 << endl;
}
