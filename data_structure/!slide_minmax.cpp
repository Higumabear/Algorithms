#include <iostream>
#include <vector>
#include <deque>

using namespace std;

void slide_min(const vector<int> &val, int K){
  deque<int> deq;
  for(int i = 0; i < val.size(); i++){
    while(!deq.empty() && val[deq.back()] >= val[i]) deq.pop_back();
    deq.push_back(i);
    
    if(i - K + 1 >= 0){
      cout << val[deq.front()] << endl;
      if(i - K + 1 == deq.front()) deq.pop_front();
    }
  }
}

int main(){
  vector<int> a{1, 3, 2, 0, 3, 4, 1};
  slide_min(a, 3);
  return 0;
}
