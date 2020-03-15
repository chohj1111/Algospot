#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
const int  mod = 20091101;
// Problem 1.
// psum 이 같은 것들 끼리 묶은 집합, psum 첫 원소 전 0이 있다고 가정
int waysToBuy(const vector<int> &psum, int _childNum){
 	int ret=0;
	vector<long long> count(_childNum,0);
	for(int i=0;i<psum.size();i++){
		count[psum[i]]++;
	}
	for(int i=0;i<_childNum;i++){
		if(count[i]>=2)
			ret = (ret+ ((count[i]*(count[i]-1))/2)) % mod;
	}	
	return ret;
}
int maxBuys(const vector<int> &psum, int _childNum){
	vector<int> dp(psum.size(),0);
	// prev[a] = psum[] == a인 위치 
	// 즉 j~i 까지 연속으로 구매한다고 가정할 때(psum[j-1]==psum[i]) 가장 큰 j 
	vector<int> prev(_childNum,-1);
	for(int i=0;i<psum.size();i++){
		if (i>0) dp[i] = dp[i-1];
		else dp[i] = 0;
		int temp = prev[psum[i]];
		if(temp!= -1) dp[i] = max(dp[i], dp[temp]+1);
		//prev[i] 새로 저장
		prev[psum[i]]= i;
	}
	return dp.back();
}
int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin>>test;
	while(test--){
		// boxNum = 인형상자 n, 어린이 k명
		int boxNum,childNum;
		cin>>boxNum>>childNum;
		// 상자 번호 별 인형 수
		vector<int> dollNum(boxNum);
		for(int i=0;i<boxNum;i++) {
			cin>>dollNum[i];
		}
		// 인형들 박스의 부분합
		vector<int> psum(boxNum+1);
		//psum[-1] == 0을 아래처럼 가정 => 첫 상자부터 사는 경우 고려
		psum[0] = 0;
		for(int i=1;i<=boxNum;i++){
			psum[i] = (psum[i-1]+ dollNum[i-1])%childNum; // psum[0] = 0 이므로 dollNum의 index 가 i가 아니라 i-1
 		}
		cout<<waysToBuy(psum, childNum) << " "<< maxBuys(psum,childNum)<<'\n';
	}
	return 0;
}