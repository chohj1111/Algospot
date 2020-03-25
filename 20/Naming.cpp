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
vector<int> getAnswer(const string& str){
	vector<int> pi = getPartialMatch(str);
	vector<int> ret;
	for(int ans = str.size(); ans!=0 ;ans = pi[ans-1]){
		ret.push_back(ans);
	}
	return ret;
}
int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	string pa, ma;
	getline(cin,pa);
	getline(cin,ma);
	string str = pa+ma;
	
	vector<int> ans = getAnswer(str);
	for(int i=ans.size()-1;i>=0;i--){
		cout<< ans[i]<<' ';
	}
	cout<<endl;
	return 0;	
	
}
