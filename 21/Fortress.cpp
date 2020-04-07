#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#define MAX 100
using namespace std;

struct Treenode{
	vector<Treenode*> children;
};

int longest; // 가장 긴 leap - leap 경로 길이
int num;
int x[MAX], y[MAX], radius[MAX];
int height(Treenode* root){
	vector<int> heights;
	for(int i=0;i<root->children.size();i++){
		heights.push_back(height(root->children[i]));
	}
	if(heights.empty()) return 0;
	sort(heights.begin(),heights.end());
	if(heights.size()>=2) {
		longest = max(longest, 2+heights[heights.size()-2]+heights[heights.size()-1]);
	}
	return heights.back() + 1;
}
int solve(Treenode* root){
	longest =0;
	int h= height(root);
	return max(h,longest);
}

int sqr(int x){
	return x*x;
}
// 두 점 간 거리
int sqrdist(int a,int b){
	return sqr(x[a]-x[b]) + sqr(y[a]-y[b]);
}
// a가 b를 포함하는지 여부
bool enclosed(int a, int b){
	return radius[a]>radius[b] && sqrdist(a,b)< sqr(radius[a]-radius[b]);
}
bool isChild(int parent,int child){
	if(!enclosed(parent,child)) return false;
	for(int i=0;i<num;i++){
		if(i!=parent&& i!=child && enclosed(parent,i) && enclosed(i,child)) return false;
	}
	return true;
}
// 주어진 번호의 성벽을 루트로 하는 트리를 생성
Treenode* getTree(int root){
	Treenode* ret = new Treenode();
	for(int i=0;i<num;i++){
		if(isChild(root, i)){
			ret->children.push_back(getTree(i));
		}
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
		cin>>num;
		for(int i=0;i<num;i++){
			cin>>x[i]>>y[i]>>radius[i];
		}
		Treenode* T = getTree(0);
		cout<<solve(T)<<endl;
		
	}
	
	
}
