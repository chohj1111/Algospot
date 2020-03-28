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
// str의 접미사 이자 reversed_str의 접두사인 문자열의 최대 길이
int maxOverlap(const string& str){
	string reversed_str= str;
	reverse(reversed_str.begin(), reversed_str.end());
	int n = str.size();
	vector<int> pi= getPartialMatch(reversed_str);
	int begin = 0, match = 0;
	while(begin+match < n){
		if(str[begin+match] == reversed_str[match]) {
			match++;
			if(begin+ match==n) return match;
		}
		else {
			if(match==0) begin++;
			else {
				begin +=  match- pi[match-1];
				match =  pi[match-1];
			}
		}
	}
	return 0;
}
int getPalindrom(string str){
	return str.size()*2 - maxOverlap(str);
}
int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);	
	int test;
	cin>>test;
	while(test--){
		string str;
		cin>>str;
		cout<<getPalindrom(str)<<endl;
	}
	
	
}
