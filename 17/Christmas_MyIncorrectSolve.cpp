#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
vector<int> partialSum(const vector<int>& a){
	vector<int> ret(a.size());
	ret[0] = a[0];
	for(int i=1;i<a.size();i++){
		ret[i] += a[i];
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
		vector<int> psum = partialSum(dollNum);
		// Problem 1.
		// 부분합을 childNum으로 나눈 나머지가 같은 개수 저장할 벡터
		vector<int> mod_psum(boxNum);
		mod_psum[0] = 1;
		for(int i=0;i<boxNum;i++){
			mod_psum[psum[i] % childNum]++;
		}
		int ans_1=0;
		for(int i=0;i<childNum;i++){
			ans_1 += (mod_psum[i]*(mod_psum[i]-1))/2;
		}	
		cout<<ans_1<<' ';
		// Problem 2.
		vector<int> dp(boxNum);
		if(psum[0]% childNum == 0) dp[0] = 1;
		for(int i=1;i<boxNum;i++){
	
			// i번째 상자 구매 O => j~i 연속으로 구매할 수 있는 j에 대해 가장 큰 j 구하기
			for(int j=i;j>0;j--){
				if(psum[i] == psum[j-1]) { 
					dp[i] = max(dp[i-1],dp[j-1] +1);
					break;
				}
			}
		}
		cout<< dp[boxNum-1]<<'\n';	
	}
	return 0;
	
}
