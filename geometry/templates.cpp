// Time-stamp: <Tue Jun 12 20:54:06 Eastern Daylight Time 2018>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

#define EPS 1e-11

using namespace std;

double add(double a, double b){
  if(abs(a + b) < EPS * (abs(a) + abs(b))) return 0;
  return a + b;
}

struct P{
  double x, y;
  P() {}
  P(double x, double y) : x(x), y(y) {}
  P operator + (P p){ return P(add(x, p.x), add(y, p.y)); }
  P operator - (P p){ return P(add(x, -p.x), add(y, -p.y)); }
  P operator * (double d){ return P(x * d, y * d); }
  P operator / (double d){ return P(x / d, y / d); }
  double dot(P p){ return add(x * p.x, y * p.y); }
  double det(P p){ return add(x * p.y, -y * p.x); }
  double norm() { return sqrt(add(x * x, y * y));}
  P rot() { return P(-y, x); }
};

struct line{
  vector<P> pt;
  line() {};
  line(const P &a, const P &b) { pt.push_back(a); pt.push_back(b); }
  inline P& operator[](int i) { return pt[i]; }
};

int ccw(P a, P b, P c){
  b = b - a, c = c - a;
  if(b.det(c) > 0)		return 1;	//CCW
  if(b.det(c) < 0)		return -1;	//CW
  if(b.dot(c) < 0)		return 2;	//BEHIND
  if(b.norm() < c.norm())	return -2;	//FRONT
  return 0; //ON
}

P cross_point(P p1, P p2, P q1, P q2){
  double A = (p2 - p1).det(q2 - q1);
  double B = (p2 - p1).det(p2 - q1);

  //parallel
  if(abs(A) < EPS)
    return P(-1e100, -1e100);

  return q1 + (q2 - q1) * (B / A);
}


struct polygon{
  vector<P> ps;
  polygon() {}
  polygon(vector<P> &ps) : ps(ps) {}
  inline P& operator[](int i) { return ps[i]; }
  int size() const { return ps.size(); }
  inline void push_back(const P& a) { ps.push_back(a); }

  polygon cut(line l){
    polygon Q;
    int N = size();
    for(int i = 0; i < N; i++){
      P a = ps[i], b = ps[(i + 1) % N];
      if(ccw(l[0], l[1], a) != -1) Q.push_back(a);
      if(ccw(l[0], l[1], a) * ccw(l[0], l[1], b) < 0)
	Q.push_back(cross_point(a, b, l[0], l[1]));
    }
    return Q;
  }
};

