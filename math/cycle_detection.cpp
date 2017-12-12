/*
  Cycle detection for repeating decimal

  Complexity:
  O(n) 
  n : number of repeating digits
  
  Verified:
  http://poj.org/problem?id=3720
*/


#include <iostream>
#include <sstream>

using namespace std;

inline string i2s(int x){
  stringstream ss;
  ss << x;
  return ss.str();
}

string repeating_decimal(const int n){ /* 1 / n */
  int m = 1;
  int p = 1;
  int s = 0, t = 0;
  if(n < 0) return "";

  do{
    m = (m * 10) % n;
    p = (p * 10) % n;
    p = (p * 10) % n;
  }while(m != p);

  if(p != 0){
    p = 1;
    s = 1;
    while(m != p){
      s++;
      m = (m * 10) % n;
      p = (p * 10) % n;
    }
    p = (p * 10) % n;
    t = s + 1;
    while(m != p){
      t++;
      p = (p * 10) % n;
    }
  }

  int tmp = 1;
  string rep_str;
  for(int i = 0; i <= (t == 0 ? 100 : t); i++){
    if(tmp == 0) break;
    rep_str += i2s((tmp * 10) / n);
    tmp = (tmp * 10) % n;
  }

  if(t == 0) return rep_str;
  else return rep_str.substr(0, t - 1);
}

int main(){
  int a;
  while(cin >> a){
    string s = repeating_decimal(a);
    cout << s << endl;
  }
  return 0;
}
