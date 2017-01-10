/*
  Z algorithm

  Constructs an array that contains the length of 
  the longgest common prefix between S[0..N-1] and S[i..N-1] in linear time.
  Also can be applied to linear time string matching.

  Complexity:
  O(|S|)

  Veriied:
  
 */
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> Z_algorithm(const string &s){
  int l = 0, r = 0;
  vector<int> z(s.size(), 0);
  for(int i = 0; i < s.size(); i++){
    if(r < i){
      int k = 0;
      while(i + k < s.size() && s[i + k] == s[i]) z[i]++;
      if(z[i]) r = i + z[i] - 1, l = i;
    }else{

    }
  }
  return z;
}
