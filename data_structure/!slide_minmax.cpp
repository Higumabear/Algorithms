#include <iostream>
#include <vector>
#include <deque>

using namespace std;

void slide_min(const vector<int> &val, int K){
  deque<int> deq;
  
  for(int i = 0; i < val.size(); i++){
    if(deq.empty()) deq.push_back(val[i]);
    else{
      while(!deq.empty() && deq.back() < val[i]) deq.pop_back();
      deq.push_back(val[i]);
    }
    if(i >= val.size() - 1){
      cout << deq.front() << endl;
      deq.pop_front();
    }
  }
}

int main(){
  vector<int> a{1, 3, 2, 0, 3, 4, 1};
  slide_min(a, 3);
  return 0;
}
