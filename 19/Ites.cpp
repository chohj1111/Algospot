#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
struct RNG{
	unsigned seed;
	RNG(): seed(1983){}
	unsigned next(){
		unsigned ret = seed;
		seed = ((seed*214013u)+2531011u);
		return ret%10000+1;
	}
};
int solve(int k,int n){
	RNG rng;
	int range_sum = 0;
	int ans = 0;
	queue<int> range;
	for(int i=0;i<n;i++){
		int next_num = 	rng.next();
		range_sum+=next_num;
		range.push(next_num);
		while(range_sum>k) {
			range_sum -= range.front();
			range.pop();
		}
		if(range_sum==k) ans++;
	}
	return ans;
}
int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin>>test;
	while(test--){
		int k,n; 
		cin>>k>>n;
		cout<< solve(k,n)<<endl;
	}
	
	
}
