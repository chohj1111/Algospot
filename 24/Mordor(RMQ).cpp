#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
using namespace std;
//const int INT_MAX = numeric_limits<int>::max();          vs���� �ּ��ص� ���ư�
struct RMQ {
	int n;
	vector<int> rangeMin;
	RMQ(const vector<int>& arr) {
		n = arr.size();
		rangeMin.resize(n * 4);
		init(arr, 0, n - 1, 1);
	}
	// node��尡 array[left, right] �迭 ǥ�� �� 
	// node�� ��Ʈ�� �ϴ� ����Ʈ�� �ʱ�ȭ �ϰ� �� ������ �ּ�ġ�� ��ȯ
	int init(const vector<int>& arr, int left, int right,int node) {
		if(left == right) return rangeMin[node] = arr[left];
		int mid = (left + right) / 2;
		int leftMin = init(arr, left, mid, node * 2);
		int rightMin = init(arr, mid+1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}
	//node�� ����Ű�� ���� & �츮�� ���ϴ� ����(left,right) �� �������� �ּ� ����
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
