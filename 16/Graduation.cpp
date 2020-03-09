#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXN = 12;
const int INF = 987654321;

int totalNum;  // 총 과목 수 n 
int gradNum;   // 들어야 하는 과목 수 k
int semesterNum; // 학기 수 m
int semesterMax; // 한 학기 당 최대 과목 수 l 
int prerequire[MAXN];  //선이수 정보를 담을 배열 
int classes[10]; // 학기 별 열리는 과목 정보
int cache[10][1<<MAXN]; // 메모이제이션
int bitCount(int n){
	if(n==0) return 0;
	return n%2 + bitCount(n/2);
}
// 이번 학기 : semester, 지금까지 들은 과목 집합 : taken
// k개 이상의 과목을 수강하기 위해선 몇 학기나 더 있어야 하는가
// 불가능하면 INF return
int graduation(int semester, int taken){
	// 수강한 과목 수가 k 이상이면 끝
	if(bitCount(taken)>=gradNum) return 0;
	// 모든 학기가 끝난 경우
	if(semester==semesterNum) return INF;
	int& ret = cache[semester][taken];
	if(ret != -1) return ret;
	ret = INF;
	// 이번 학기 들을 수 있는 과목 중 아직 수강안한 과목
	int canTake = (classes[semester] & ~taken);
	// 선수 과목 안 들은 과목 거르기
	for(int i=0;i <totalNum;i++){
		// i가 현재 학기에서 들을 수 있는 과목이지만 선이수 과목을 수강하지 않은 경우 canTake 집합에서 i 제외
		if((canTake& (1<<i)) && (taken & prerequire[i]) != prerequire[i]) canTake &= ~(1<<i); 
	}
	// 모든 subset 순회 , 공집합 제외
	for(int take = canTake; take; take = ((take-1)&canTake)) {
		// 한 학기 듣는 과목 수 l 초과 시 continue
		if(bitCount(take)>semesterMax) continue;
		ret = min(ret, graduation(semester+1,taken|take)+1);
	}
	// semester 학기에서 아무것도 안 들을 때
	ret = min(ret, graduation(semester+1,taken));
	return ret;
}
int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin>> test;
	while(test--){
    	memset(prerequire, 0, sizeof(prerequire));
        memset(classes, 0, sizeof(classes));
        memset(cache, -1, sizeof(cache));
		// 
		cin>> totalNum >>gradNum>>semesterNum>>semesterMax;
		// 선이수 정보 입력
		for(int i=0;i<totalNum;i++){
			int required; 
			cin>> required;
			for(int j=0;j<required;j++){
				int temp_input;
				cin>> temp_input;
				prerequire[i] |= (1<<temp_input);
			}
		}
		// 학기 별 정보 입력
		for(int i=0;i<semesterNum;i++){
			int opened;
			cin>>opened;
			for(int j=0;j<opened;j++){
				int temp_input;
				cin>>temp_input;
				classes[i] |= (1<<temp_input);
			}
		}
		int result = graduation(0,0);
		if(result == INF) cout <<"IMPOSSIBLE" <<'\n'; 
		else cout<< result <<'\n';
	}	
	return 0;
	
}