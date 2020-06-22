#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;
vector<int> arr;
struct RNG {
	int seed, a, b;
	RNG(int _a, int _b) : a(_a), b(_b), seed(1983) {}
	int next() {
		int ret = seed; 
		seed = (seed*(long long)a + b) % 20090711;
		return ret;
	}
};
int runningMedian(int n, RNG rng) {
	priority_queue <int, vector<int>, less<int>> max_heap;
	priority_queue <int, vector<int>, greater<int>> min_heap;
	int ret = 0;
	for (int i = 0; i < n; i++) {
		if (max_heap.size() == min_heap.size()) max_heap.push(rng.next());
		else min_heap.push(rng.next());
		if (!max_heap.empty() && !min_heap.empty() && max_heap.top() > min_heap.top()) {
			int a = max_heap.top();
			int b = min_heap.top();
			max_heap.pop();
			min_heap.pop(); 
			max_heap.push(b); min_heap.push(a);
		}
		ret = (ret + max_heap.top()) % 20090711;
	}
	return ret;	
}

int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin>>test;
	while(test--){
		int num, a, b;
		cin>> num>>a>>b;
		RNG rng(a, b);
		cout<< runningMedian(num, rng)<<endl;
	}
	
	return 0;
}
