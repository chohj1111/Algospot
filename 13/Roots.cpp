#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<double> derivative(const vector<double>& poly);
vector<double> solve_low_degree(const vector<double>& poly);
double value(const vector<double>& poly double x_0);
vector<double> solve(const vector<double>& poly);

int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin>>test;
	while(test--){
		int n;
		cin>>n;
		vector<double> poly_input(n);
		for(int i=0;i<n;i++){
			cin>>poly_input[i];			
		}
		vector<double> ans = solve(poly_input);
		for(int i=0;i<ans.size();i++) cout<< ans[i] <<' ';
		cout<<'\n';
	}
	return 0;
}
vector<double> derivative(const vector<double>& poly){
	int n= poly.size();
	vector<double> ret;
	for(int i=0;i<n-1;i++){
		ret.push_back((n-i-1)*poly[i]);
	}
	return ret;
}

vector<double> solve_low_degree(const vector<double>& poly){
	int n = poly.size() - 1;
	vector<double> result;
	switch (n)
	{
		case 0: 
			result.push_back(poly[0]);
			break;
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
	for(int i=0;i<n;i++){
		ret += poly[i]*pow(x_0, n-i);
	}
	return ret;
}
vector<double> solve(const vector<double>& poly){
	int n= poly.size()-1;
	vector<double> ret;
	if(n<=2) ret = solve_low_degree(poly);
	vector<double> 
}
