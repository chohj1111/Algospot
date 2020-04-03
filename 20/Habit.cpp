#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>

using namespace std;
// 코드 20.9 첫 t글자로 묶인 그룹 정보를 이용해 첫 2t글자를 비교하는 비교자의 구현
// 각 접미사들으리 첫 t글자를 기준으로 한 그룹 번호가 주어질 때,
// 주어진 두 접미사를 첫 2*t글자를 기준으로 비교한다
// group[]은 길이가 0인 접미사도 포함한다
struct Comparator {
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& _group, int _t): group(_group), t(_t) { }
	bool operator () (int a, int b) {
		// 첫 t글자가 다르면 이들을 이용해 비교한다
		if (group[a] != group[b])
			return group[a] < group[b];
		// 아니라면 S[a+t..]와 S[b+b..]의 첫 글자를 비교한다
		return group[a + t] < group[b + t];
	}
};

// 코드 20.10 접미사 배열을 계산하는 맨버와 마이어스의 알고리즘
// s의 접미사 배열을 계산한다
vector<int> getSuffixArray(const string& s) {
	int n = s.size();
	// group[i] = 접미사들을 첫 t글자를 기준으로 정렬했을 때,
	//            S[i..]가 들어가는 그룹 번호
	// t = 1 일때는 정렬할 것 없이 S[i..]의 첫 글자로 그룹 번호를
	// 정해 줘도 같은 효과가 있다
	int t = 1;
	vector<int> group(n + 1);
	for (int i = 0; i < n; ++i)
		group[i] = s[i];
	group[n] = -1;
	// 결과적으로 접미사 배열이 될 반환 값. 이 배열을 lg(n)번 정렬한다
	vector<int> perm(n);
	for (int i = 0; i < n; ++i)
		perm[i] = i;
	while (t < n) {
		// group[]은 첫 t글자를 기준으로 계산해 뒀다
		// 첫 2t글자를 기준으로 perm을 다시 정렬한다
		Comparator compareUsing2T(group, t);
		sort(perm.begin(), perm.end(), compareUsing2T);
		// 2t글자가 n을 넘는다면 이제 접미사 배열 완성!
		t *= 2;
		if (t >= n)
			break;
		// 2t글자를 기준으로 한 그룹 정보를 만든다
		vector<int> newGroup(n + 1);
		newGroup[n] = -1;
		newGroup[perm[0]] = 0;
		for (int i = 1; i < n; ++i)
			if (compareUsing2T(perm[i - 1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
			else
				newGroup[perm[i]] = newGroup[perm[i - 1]];
		group = newGroup;
	}
	return perm;
}
// 코드 20.12 접미사 배열을 이용해 다른 부분 문자열의 수를 세는 알고리즘
// s[i..]와 s[j..]의 공통 접두사의 최대 길이를 계산한다
int commonPrefix(const string& s, int i, int j){
	int ret = 0;
	while(i<s.size() && j<s.size() && s[i] == s[j]){
		i++; j++; ret++;
	}
	return ret;
}
// 코드 20.13 접미사 배열을 이용해 말버릇 문제를 해결하는 알고리즘
// k 번 이상 출현하는 s의 부분 문자열 중 최대 길이를 찾는다
int longestFrequent(int k, const string& s){
	vector<int> a = getSuffixArray(s);
	int ret = 0;
	for(int i=0;i+k<=s.size();i++){
		ret = max(ret, commonPrefix(s, a[i], a[i+k-1]));
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
		int k; string s;
		cin>>k;
		cin>>s;
		cout<<longestFrequent(k,s)<<endl;
	}
	
}
