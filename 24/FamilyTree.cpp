#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

// 근데 굳이 일련번호를 써야 돼?
using namespace std;
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
	int init(const vector<int>& arr, int left, int right, int node) {
		if (left == right) return rangeMin[node] = arr[left];
		int mid = (left + right) / 2;
		int leftMin = init(arr, left, mid, node * 2);
		int rightMin = init(arr, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}
	void traversal() {

	}
	//node가 가르키는 구간 & 우리가 원하는 구간(left,right) 의 교집합의 최소 원소
	int query(int left, int right, int node, int nodeleft, int noderight) {
		if (right < nodeleft || left> noderight) return INT_MAX;
		if (left <= nodeleft && noderight <= right) return rangeMin[node];
		int mid = (nodeleft + noderight) / 2;
		return min(query(left, right, node * 2, nodeleft, mid), query(left, right, node * 2 + 1, mid + 1, noderight));
	}
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}
};
const int MAX_N = 100000;
vector<int> child[MAX_N];
int no2serial[MAX_N], serial2no[MAX_N];
// location_tree : 처음 노드가 tree 에 출현하는 위치 , index : serial number 가 아닌 입력으로 주어진 순서(flag) 
int location_tree[MAX_N], depth[MAX_N];
int nextSerial; // 다음 serial num

// trip : 각 노드의 일련번호를 순서대로 저장한 vector 
// segment tree , 즉 일렬로 늘어선 배열을 처리하므로 preorder를 사용하며 노드를 한 번씩 출력하는게 아니라 모든 경로를 출력
// n개의 노드 -> 경로 : 2n-1 개 (시작도 포함)
// 깊이가 d인 flag 노드 이하 preorder traversal
void traversal(int _flag, int _d, vector<int>& trip) {
	no2serial[_flag] = nextSerial;
	serial2no[nextSerial] = _flag;
	nextSerial++;
	depth[_flag] = _d;
	//trip 에 일련번호 추가 
	location_tree[_flag] = trip.size();
	trip.push_back(no2serial[_flag]);
	for (int i = 0; i < child[_flag].size(); i++) {
		traversal(child[_flag][i], _d + 1, trip);
		trip.push_back(no2serial[_flag]);
	}
}

RMQ* prepareRMQ() {
	nextSerial = 0;
	// 순회 과정 중 만나는 노드의 일련번호
	vector<int> trip; 
	traversal(0, 0, trip);
	return new RMQ(trip);
}

int distance(RMQ *rmq, int u, int v) {
	int lu = location_tree[u];
	int lv = location_tree[v];
	if (lu > lv) swap(lu, lv);
	int lca = serial2no[rmq->query(lu, lv)]; // tree에는 일련번호가 저장 
	return depth[u] + depth[v] - 2 * depth[lca];
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int test;
	cin >> test;
	while (test--) {
		for (int j = 0; j < MAX_N; j++)
			child[j].clear();
		int N, Q;
		cin >> N >> Q;
		// father
		for (int i = 1; i < N; i++) {
			int father;
			cin >> father;
			child[father].push_back(i);
		}
		nextSerial = 0;
		RMQ *pRmq = prepareRMQ();
		// calculate
		for (int i = 0; i < Q; i++) {
			int a, b;
			cin >> a >> b;
			cout << distance(pRmq, a, b) << endl;
		}
	}

	return 0;
}
		