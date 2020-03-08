#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin>> test;
	while(test--){
		int total_num;  // 총 과목 수 n 
		int grad_num;   // 들어야 하는 과목 수 k
		int minister_num; // 학기 수 m
 		int max_sub_minister; // 한 학기 당 최대 과목 수 l 
		int prerequire[12];  //선이수 정보를 담을 배열 
		int minister_bit[10]; // 학기 별 열리는 과목 정보
		// 
		cin>> total_num >>grad_num>>minister_num>>max_sub_minister;
		// 선이수 정보 입력
		for(int i=0;i<total_num;i++){
			int required; 
			cin>> required;
			for(int j=0;j<required;j++){
				int temp_input;
				cin>> temp_input;
				prerequire[i] |= (1<<temp_input);
			}
		}
		// 학기 별 정보 입력
		for(int i=0;i<minister_num;i++){
			int opened;
			cin>>opened;
			for(int j=0;j<opened;j++){
				int temp_input;
				cin>>temp_input;
				minister_bit[i] |= (1<<temp_input);
			}
		}
	
	}	
	return 0;
	
}