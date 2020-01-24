#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
double balance(double loan, int duration,double rates, double monthlyPay){
	double left = loan;
	for(int i=0;i<duration;i++){
		left *= (1.0+(rates/12.0)/100.0);
		left -= monthlyPay;
	}
	return left;
}
double payment(double loan, int duration, double rates){
	double  lo= 0, hi = loan*(1.0+(rates/12.0)/100.0);
	for(int iter =0;iter<100;iter++){
		double mid = (lo+hi) /2;
		if(balance(loan,duration,rates,mid)>0) lo=mid;
		else hi =mid;
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
		double loan_,rates_;
		int months_;
		cin>>loan_>>months_>>rates_;
		cout << fixed << setprecision(10);
		cout<< payment(loan_,months_, rates_)<<'\n';
	}
	return 0;
	
}
