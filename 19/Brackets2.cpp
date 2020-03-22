#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <stack>
using namespace std;

bool check_stack(const string& str){
	stack<char> stk;
	const string opening("({[");
	const string closing(")}]");
	for(int i=0;i<str.size();i++){
		if(opening.find(str[i]) != -1){
			stk.push(str[i]);
		}
		else{
			if(stk.empty()) 	return false;
			if(opening.find(stk.top())!=closing.find(str[i]))
				return false;
			stk.pop();
		}
	}
	return stk.empty();
}
int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin>>test;
	while(test--){
		string str;
		cin >> str;

		if(check_stack(str)) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
			
	}
	return 0;
	
}
