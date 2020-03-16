#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <list>
using namespace std;
// o(NK) 
void solve(int n,int k){   
	list<int> l;
	for(int i=1;i<=n;i++){
		l.push_back(i);
	}
	list<int>::iterator iter = l.begin();
	while(n>2){
		iter = l.erase(iter);  // iter 번째 지운 다음 원소 return 
		n--;
		if(iter == l.end()) iter = l.begin();
		for(int i=0;i<k-1;i++){	// k-1 번 pointer 이동
			iter++;
			if(iter == l.end()) iter = l.begin();
		}
	}
	cout<< l.front() <<" "<<l.back()<<'\n';
}
int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin>>test;
	while(test--){
		int n,k;
		cin>>n >>k;
		solve(n,k);
		
	}
	return 0;
	
}
