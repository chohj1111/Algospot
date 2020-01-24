#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
vector<double> derivative(const vector<double>& poly);
vector<double> solve_low_degree(const vector<double>& poly);
double value(const vector<double>& poly, double x_0);
vector<double> solve(const vector<double>& poly);
const double L= 10;
int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin>>test;
	while(test--){
		vector<double> poly_input;
		int n;
		cin>>n;
		for(int i=0;i<n+1;i++){
			double input; 
			cin>> input;
			poly_input.push_back(input);
		}
		vector<double> ans = solve(poly_input);
		cout << fixed << setprecision(12);
		for(int i=0;i<ans.size();i++) cout<< ans[i] <<' ';
		cout<<'\n';
	}
	return 0;
}
vector<double> derivative(const vector<double>& poly){
	int n= poly.size() -1;
	vector<double> ret;
	for(int i=0;i<n;i++){
		ret.push_back((n-i)*poly[i]);
	}
	return ret;
}

vector<double> solve_low_degree(const vector<double>& poly){
	int n = poly.size() - 1;
	vector<double> result;
	switch (n)
	{
	case 1:
		result.push_back(-poly[1] / poly[0]);
        break;
    case 2:
      	double a = poly[0], b = poly[1], c = poly[2];
		result.push_back((-b + sqrt(pow(b, 2) - 4 * a*c)) / (2 * a));
        result.push_back((-b - sqrt(pow(b, 2) - 4 * a*c)) / (2 * a));
        break;
    }
    sort(result.begin(), result.end());
	return result;
}
double value(const vector<double>& poly, double x_0){
	int n= poly.size()-1;
	double ret = 0;
	for(int i=0;i<=n;i++){
		 ret += pow(x_0, n - i)*poly[i];
	}
	return ret;
}
vector<double> solve(const vector<double>& poly){
	int n= poly.size()-1;
	if(n<=2) return solve_low_degree(poly);
	vector<double> differ = derivative(poly);
	vector<double> sols = solve(differ);  // roots of f'(x)
	sols.insert(sols.begin(),-L-1);
	sols.insert(sols.end(),L+1);
	vector<double> ret;
	for(int i=0;i+1<sols.size();i++){
		// initialize 
		double x_1 = sols[i];    double x_2 = sols[i+1];
		double y_1 = value(poly, x_1); double y_2 = value(poly, x_2);
		// no root between same signed value
		if(y_1*y_2 >0) continue;
		// fix f(x_1) <= 0 < f(x_2)
		if(y_1>y_2) {
			swap(x_1,x_2); swap(y_1,y_2);
		}
		for(int iter =0;iter<100;iter++){
			double x_mid = (x_1+x_2)/2;
			double y_mid = value(poly, x_mid);
			if(y_mid > 0) {
				x_2= x_mid; y_2 =y_mid;
			}else{
				x_1 = x_mid; y_1 = y_mid;
			}
		}
		ret.push_back((x_1+x_2)/2);
	}
	sort(ret.begin(),ret.end());
	return ret;	
}
