#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std; 
struct point{
	double x, y;
};
vector<point> hull1, hull2;
vector<pair<point,point>> upper, lower;
double minX(const vector<point> hull){
	int n=hull.size();
	double ret=hull[0].x;
	for(int i=1;i<n;i++){
		ret = min(ret, hull[i].x);
	}
	return ret;
}
double maxX(const vector<point> hull){
	int n=hull.size();
	double ret=hull[0].x;
	for(int i=1;i<n;i++){
		ret = max(ret, hull[i].x);
	}
	return ret;
}
bool isInside(const point& a, const point& b, double x){
	return ((a.x<=x&&x<=b.x)||(b.x<=x&&x<=a.x));
}
double at(const point& a, const point& b, double x){
	return a.y+(b.y-a.y)*(x-a.x)/(b.x-a.x);
}

void decompose(const vector<point>& hull){
	int n= hull.size();
	for(int i=0;i<n;i++){
		// hull[i].x == hull[i+1].x 는 수직선과 교차점이 정의되지 않으므로 고려 x
		if(hull[i].x>hull[(i+1)%n].x) upper.push_back(make_pair(hull[i],hull[(i+1)%n]));
	else if(hull[i].x<hull[(i+1)%n].x) lower.push_back(make_pair(hull[i],hull[(i+1)%n]));	
	}
}
double vertical(double x){
	double minUp = 1e20, maxLow= -1e20;
	for(int i=0;i<upper.size();i++){
		if(isInside(upper[i].first,upper[i].second,x))
			minUp= min(minUp,at(upper[i].first,upper[i].second,x));
	}
	for(int i=0;i<lower.size();i++){
		if(isInside(lower[i].first,lower[i].second,x))
			maxLow =max(maxLow, at(lower[i].first,lower[i].second,x));
	}
	return minUp-maxLow;
}
double solve(){
	double lo = max(minX(hull1),minX(hull2));
	double hi = min(maxX(hull1),maxX(hull2));
	if(lo>hi) return 0;
	for(int iter =0;iter<100;iter++){
		double first_third = (lo*2+hi)/3;
		double second_third = (lo+hi*2)/3;
		if(vertical(first_third)>vertical(second_third)) hi = second_third;
		else lo = first_third;
	}
	return max(0.0,vertical(hi));
}

int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin>>test;
	while(test--){
		hull1.clear();
		hull2.clear();
		int input1,input2;
		cin>>input1>>input2;
		for(int i=0;i<input1;i++){
			point temp;
			cin>> temp.x>>temp.y;
			hull1.push_back(temp);
		}
		for(int i=0;i<input2;i++){
			point temp;
			cin>> temp.x>>temp.y;
			hull2.push_back(temp);
		}
		lower.clear();
		upper.clear();
		decompose(hull1);
		decompose(hull2);
		double result = solve();
        if (result <= 0) cout << "0.000000" << endl;
        else{
			cout << fixed << setprecision(10);
			cout << result << endl;
		}             
	}
	return 0;	
}
