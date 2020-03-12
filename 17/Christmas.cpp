#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
const int  mod = 20091101;
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
			dollNum[i] = 0;
			cin>>dollNum[i];
		}
		// 인형들 박스의 부분합
		vector<int> psum(boxNum+1);
		//psum[-1] == 0을 아래처럼 가정 => 첫 상자부터 사는 경우 고려
		psum[0] = 0;
		for(int i=1;i<=boxNum;i++){
			psum[i] = (psum[i-1]+ dollNum[i])%mod;
		}
		// Problem 1.
		// psum 이 같은 것들 끼리 묶은 집합, psum 첫 원소 전 0이 있다고 가정
		vector<long long> count(childNum);
		for(int i=0;i<psum.size();i++){
			count[psum[i]]++;
		}
		int ans_1=0;
		for(int i=0;i<childNum;i++){
			if(count[i]>=2)
				ans_1 += ((count[i]*(count[i]-1))/2)%mod;
		}
		cout<<ans_1<<' ';
		// Problem 2.
		vector<int> dp(boxNum+1,0);
		// prev[a] = psum[] == a인 위치 
		// 즉 j~i 까지 연속으로 구매한다고 가정할 때(psum[j-1]==psum[i]) 가장 큰 j 
		vector<int> prev(childNum,-1);
		dp[0] = 0;
		for(int i=1;i<boxNum+1;i++){
			dp[i] = dp[i-1];
			int temp = prev[dp[i]];
			if(temp!= -1) dp[i] = max(dp[i], dp[temp]+1);
			//prev[i] 새로 저장
			prev[i] = i;
		}
		cout<< dp[boxNum]<<'\n';	
		
		
	}		

}