#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
vector<int> slice(const vector<int>& v, int a , int b){
	return vector<int> (v.begin()+a,v.begin()+b);
}
void printPostOrder(const vector<int>& preorder, const vector<int>& inorder){
	const int num = preorder.size(); // 트리 노드 수 
	if(preorder.empty()) return; // 기저 사례
	const int root = preorder[0];
	const int L = find(inorder.begin(),inorder.end(),root) - inorder.begin();
	const int R = num - 1 - L;
	printPostOrder(slice(preorder,1,L+1),slice(inorder,0,L));
	printPostOrder(slice(preorder,L+1,num),slice(inorder,L+1,num));
	cout<<root<<' ';
}
int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin>>test;
	while(test--){	
		int num;
		cin>>num;
		vector<int> preorder;
		vector<int> inorder;
		for(int i=0;i<num;i++){
			int temp;
			cin>>temp;
			preorder.push_back(temp);
		}
		for(int i=0;i<num;i++){
			int temp; cin>>temp;
			inorder.push_back(temp);
		}
		printPostOrder(preorder,inorder);
		cout<<'\n';
	}
	return 0;
	
}
