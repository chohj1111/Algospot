#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
using namespace std;
//const int INT_MAX = numeric_limits<int>::max();          vs에선 주석해도 돌아감
struct RMQ {
	int n;
	vector<int> rangeMin;
	RMQ(const vector<int>& arr) {
		n = arr.size();
		rangeMin.resize(n * 4);
		init(arr, 0, n - 1, 1);
	}
	// node노드가 array[left, right] 배열 표현 시 
	// node를 루트로 하는 서브트리 초기화 하고 이 구간의 최소치를 반환
	int init(const vector<int>& arr, int left, int right,int node) {
		if(left == right) return rangeMin[node] = arr[left];
		int mid = (left + right) / 2;
		int leftMin = init(arr, left, mid, node * 2);
		int rightMin = init(arr, mid+1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}
	//node가 가르키는 구간 & 우리가 원하는 구간(left,right) 의 교집합의 최소 원소
	int query(int left, int right, int node, int nodeleft, int noderight) {
		if (right < nodeleft || left> noderight) return INT_MAX;
		if (left <= nodeleft && noderight <= right) return rangeMin[node];
		int mid = (nodeleft + noderight) / 2;
		return min(query(left, right, node * 2, nodeleft, mid), query(left, right, node * 2 + 1, mid+1, noderight));
	}
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}

};
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin >> test;
	while (test--) {
		int N, Q;
		cin >> N >> Q;
		vector<int> positive_heights;
		vector<int> negative_heights;
		for (int i = 0; i < N; i++) {
			int height;
			cin >> height;
			positive_heights.push_back(height);
			negative_heights.push_back(-height);
		}

		RMQ rmq(positive_heights);
		RMQ negative_rmq(negative_heights);

		for (int i = 0; i < Q; i++) {
			int start, end;
			cin >> start >> end;
			int min = rmq.query(start, end);
			int max = abs(negative_rmq.query(start, end));
			int ans = max - min;
			cout << ans << endl;
		}
	}
	return 0;
}
