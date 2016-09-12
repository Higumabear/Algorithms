#include <iostream>
#include <string>
#include <vector>

using namespace std;
 
void multikey_qsort(vector<string> &val, vector<string> &tmp, 
		    int idx, int l, int r){
  if(r - l <= 1) return;
  char pivot = val[(l + r) / 2][idx]; /* ピボットの選び方 */

  int le = 0, eq = 0;
  for(int i = l; i < r; i++) /* かっこわるい */
    if(val[i][idx] < pivot) le++; 
    else if(val[l][idx] == pivot) eq++;

  int i = 0, j = le, k = le + eq;
  for(int p = l; p < r; p++){
    if(val[p][idx] < pivot)       tmp[l + i++] = val[p];
    else if(val[p][idx]	== pivot) tmp[l + j++] = val[p];
    else                          tmp[l + k++] = val[p];
  }
  multikey_qsort(tmp, val, idx, l, l + i);
  multikey_qsort(tmp, val, idx + 1, l + 1, l + j);
  multikey_qsort(tmp, val, idx, l + j, r);
}

void mqsort(vector<string> &s){
  vector<string> tmp = s;
  multikey_qsort(s, tmp, 0, 0, s.size());
}

int main(){
  vector<string> s(5);

  // s[0] = "afkege";
  // s[1] = "srsrthkege";
  // s[2] = "mvaoner";
  // s[3] = "egmp;ergm";
  // s[4] = "pagnel";
  s[4] = "a";
  s[3] = "aa";
  s[2] = "aaa";
  s[1] = "aaaa";
  s[0] = "aaaaa";
  mqsort(s);
  for(int i = 0; i < s.size(); i++)
    cout << s[i] << endl;
}
