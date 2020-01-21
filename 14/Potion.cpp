#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int gcd(int a, int b) {
	if(b==0) return a;
	return gcd(b,a%b);
}
int maximum_Q(int a,int b) { // a/b보다 큰 최소의 정수 return
	return (a+b-1)/b;
}
vector<int> solve(const vector<int>& recipe,const vector<int>& put){
	int n= recipe.size();
	int b = put[0];
	for(int i=1;i<n;i++) b = gcd(b, put[i]);
	int a = b;
	for(int i=0;i<n;i++){
		a = max(a, maximum_Q(put[i]*b,recipe[i]));
	}
	vector<int> ret(n);
	for(int i=0;i<n;i++){
		ret[i] = a*recipe[i]/b- put[i];
	}
	return ret;
	
}
int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin>> test;
	while(test--){
		int n;
		cin>> n;
		vector<int> recipe(n);
		vector<int> put(n);
		for(int i=0;i<n;i++) cin>>recipe[i];
		for(int i=0;i<n;i++) cin>>put[i];
		vector <int> ans = solve(recipe,put);
		for(int i=0;i<n;i++)	cout<< ans[i]<<' ';
		cout<<'\n';
	}
	return 0;
	
}
