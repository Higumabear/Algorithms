bool check(vector<int> &a, long long x){
  long long y = 0;
  for(long long i = 0; i < (int)a.size() - 1; i++){
    if((y - a[i]) % x != 0) return false;
    y = (y - a[i]) / x;
  }
  return y == a.back();
}
vector <int> integer_roots(vector <int> a) {
  vector <int> ans;

  int idx = 0; while(a[idx] == 0) idx++;
  if(idx != 0) ans.push_back(0);
  for(int i = 1; i * i <= ABS(a[idx]); i++){
    if(a[idx] % i != 0) continue;

    if(check(i)) ans.push_back(i);
    if(check(-i)) ans.push_back(-i);
    if(check(a[idx] / i)) ans.push_back(a[idx] / i);
    if(check(-a[idx] / i)) ans.push_back(-a[idx] / i);
  }
  sort(ans.begin(), ans.end());
  ans.erase(unique(ans.begin(), ans.end()), ans.end());
  return ans;
}

