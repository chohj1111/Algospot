//이게 왜 시간복잡도가 o(NlgN) 일까요??

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
using namespace std;
// key :문제수 value : 라면 수
map<int, int> coords;
bool isDominated(int x, int y){
	// x의 오른쪽 점 중 가장 왼쪽
	map<int,int>::iterator it = coords.lower_bound(x);
	//lower_bound가 없을 경우 end 를 return  즉 가장 오른쪽인 경우?
	if(it==coords.end()) return false;
	// it가 가르키는 점은 x보다 오른쪽에 있는 점 중 가장 위에 있으므로 (x,y)가 포함되려면 
	// it보다 작아야함 
	return y< it->second;
}
//지배되는 점 지우기
// (x,y)의 왼쪽으로 가면서 만약 (x,y)가 포함하는 경우 지우고, 포함하지 않으면 종료
void removeDominated(int x,int y){
	map<int,int>::iterator it = coords.lower_bound(x);
	// it가 가장 왼쪽일 때 지울 것이 없음
	if(it == coords.begin())  return;
	// (x,y) 바로 오른쪽 -> 바로 왼쪽
	it--; 
	while(true){
		if(it->second > y) break;
		if(it == coords.begin()){
			coords.erase(it);
			break;
		}
		else{
			map<int,int>::iterator jt = it;
			jt--;
			coords.erase(it);
			it = jt;
		}
	}
}
int registered(int x,int y){
	if(isDominated(x,y)) return coords.size();
	removeDominated(x,y);
	coords[x]=y;
	return coords.size();
}
int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin>> test;
	while(test--){
		int ans =0;
		int num;
		cin>>num;
		coords.clear();
		for(int i=0;i<num;i++){
			int p, q;
			cin>> p>> q;
			ans+= registered(p,q);
		}
		cout<<ans<<'\n';
	}
	
	return 0;
}
