/*
  Reverse Polish notation

  Verified:
  http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0087
 */

#include <string>
#include <iostream>
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

int main(){
  string s("(234 + 364) * (111 + 4) * (333 + 7) / 544");
  cout << rpn(s) << endl;
  string t("( 1 + 2 ) * ( 3 - 4 ) / ( 5 + 6 )");
  cout << rpn(t) << endl;
}
