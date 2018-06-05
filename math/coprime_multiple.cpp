// Time-stamp: <Tue Jun 05 19:53:02 Eastern Daylight Time 2018>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <utility>
#include <set>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <numeric>

typedef long long ll;

using namespace std;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

ll multiple_number(ll r, vector<ll> nums){
  int N = nums.size();
  ll ret = 0;
  for(int S = 1; S < 1 << N; S++){
    int bits = 0;
    ll lcm = 1;
    for(int i = 0; i < N; i++){
      if(S >> i & 1){
	bits++;
	lcm = lcm  / gcd(lcm, nums[i]) * nums[i];
	if(lcm > r) break;
      }
    }
    if(bits % 2) ret += (r / lcm);
    else ret -= (r / lcm);
  }
  return ret;
}

int main(int argc, char **argv){
  int r, m;
  cin >> r >> m;
  vector<ll> nums;
  for(int i = 0; i < m; i++){
    ll x;
    cin >> x;
    nums.push_back(x);
  }
  cout << multiple_number(r, nums) << endl;
  return 0;
}
