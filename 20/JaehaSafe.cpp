#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>
using namespace std;
vector<int> getPartialMatch(const string& str){
	int n = str.size();
	vector<int> pi(n,0);
	int begin = 1, match = 0;
	while(begin+match < n){
		if(str[begin+match] == str[match]) {
			match++;
			pi[begin+match-1]= match;
		}
		else {
			if(match==0) begin++;
			else {
				begin +=  match- pi[match-1];
				match =  pi[match-1];
			}
		}
	}
	return pi;
}
vector<int> kmpSearch(const string& str_h, const string& str_n){
	int n= str_h.size(), m = str_n.size();
	vector<int> ret;
	vector<int> pi = getPartialMatch(str_n);
	int begin = 0, matched =0;
	while(begin<= n-m){
		if(matched<m && str_h[begin+matched] == str_n[matched]){
			matched++;
			if(matched ==m) ret.push_back(begin);
		}
		else{
			if(matched==0) begin++;
			else{
				begin+=matched - pi[matched-1];
				matched = pi[matched-1];
			}
		}
	}
	return ret;	
}
int rotateDials(const string& original, const string& target){
	return kmpSearch(original+original, target)[0];
	
}
int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin>>test;
	while(test--){
		int num,ans=0;
		// 시계 = false, 반시계 = true
		bool flag = false;
		cin>>num;
		vector<string> arr(num+1);
		for(int i=0;i<num+1;i++) cin>> arr[i];
		for(int i=0;i<num;i++){
			if(flag) ans+=rotateDials(arr[i],arr[i+1]); // 반시계
			else ans+=rotateDials(arr[i+1], arr[i]);
			flag =flag? false : true ; 
		}
		cout<<ans<<endl;
	}
	
	
	
}
