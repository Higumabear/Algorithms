/*
  Reverse Polish notation

  Verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0087
 */

#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <cstring>
#include <cmath>

using namespace std;

string rpn(string s){
  stack<char> op;
  string ret;
  bool cons = true;
  for(int i = 0; i < s.size(); i++){
    if(s[i] == ' ') continue;
    if(isdigit(s[i])){
      if(!cons && ret.size()) ret += ' ';
      ret += s[i]; 
      cons = true;
    }else{ //operand or parenthes
      cons = false;
      if(s[i] == ')'){
	while(1){
	  char c = op.top(); op.pop();
	  if(c == '(') break;
	  else ret += ' ', ret += c;
	}
      }else if(s[i] == '('){
      	op.push(s[i]);
      }else{
	while(!op.empty() && 
	      abs(op.top() - ',') < abs(s[i] - ',')){
	  ret += ' ', ret += op.top();
	  op.pop();
	}
	op.push(s[i]);
      }
    }
  }
  while(!op.empty()){
    ret += ' ', ret += op.top();
    op.pop();
  }
  return ret;
}

template<class T> 
T calc_rpn(string s){
  stack<T> sta;
  stringstream ss(s);
  string t;
  while(ss >> t){
    if(isdigit(t[0])){
      stringstream sss(t);
      T val; sss >> val;
      sta.push(val);
    }else{
      char op = t[0];
      T val1 = sta.top(); sta.pop();
      T val2 = sta.top(); sta.pop();
      cout << val1 << " " << op << " " << val2 << " -> ";
      if(op == '+') val2 += val1;
      if(op == '-') val2 -= val1;
      if(op == '*') val2 *= val1;
      if(op == '/') val2 /= val1;
      cout << val2 << endl;
      sta.push(val2);
    }
  }
  return sta.top();
}

int main(){
  string s("(234 + 364) * (111 + 4) * (333 + 7) / 544");
  cout << rpn(s) << endl;
  string t("( 1 + 2 ) * ( 3 - 4 ) / ( 5 + 6 )");
  cout << rpn(t) << endl;
  cout << calc_rpn<int>("1 5 + 2 3 + *") << endl;
  cout << calc_rpn<double>("1 2 + 3 4 - * 5 6 + /") << endl;
}
