#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
long long MAX = 2000000000;
int win_ratio(long long games, long long win){
	return (win*100)/games;
}
int solve(long long games, long long win){
	if(win_ratio(games,win) == win_ratio(games+MAX, win+MAX)) return -1;
	long long lo = 0, hi =MAX;
	while(lo+1<hi){
		long long mid = (lo+hi)/2;
		if(win_ratio(games,win)==win_ratio(games+mid,win+mid)) lo = mid;
		else hi = mid;
	}
	return hi;
}

int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin>>test;
	while(test--){
		int game_played, win_games;
		cin>> game_played>>win_games;
		cout<< solve(game_played, win_games)<<'\n';
	}
	return 0;
	
}
