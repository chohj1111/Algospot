#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

// �ٵ� ���� �Ϸù�ȣ�� ��� ��?
using namespace std;
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
	int init(const vector<int>& arr, int left, int right, int node) {
		if (left == right) return rangeMin[node] = arr[left];
		int mid = (left + right) / 2;
		int leftMin = init(arr, left, mid, node * 2);
		int rightMin = init(arr, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}
	void traversal() {

	}
	//node�� ����Ű�� ���� & �츮�� ���ϴ� ����(left,right) �� �������� �ּ� ����
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
// location_tree : ó�� ��尡 tree �� �����ϴ� ��ġ , index : serial number �� �ƴ� �Է����� �־��� ����(flag) 
int location_tree[MAX_N], depth[MAX_N];
int nextSerial; // ���� serial num

// trip : �� ����� �Ϸù�ȣ�� ������� ������ vector 
// segment tree , �� �Ϸķ� �þ �迭�� ó���ϹǷ� preorder�� ����ϸ� ��带 �� ���� ����ϴ°� �ƴ϶� ��� ��θ� ���
// n���� ��� -> ��� : 2n-1 �� (���۵� ����)
// ���̰� d�� flag ��� ���� preorder traversal
void traversal(int _flag, int _d, vector<int>& trip) {
	no2serial[_flag] = nextSerial;
	serial2no[nextSerial] = _flag;
	nextSerial++;
	depth[_flag] = _d;
	//trip �� �Ϸù�ȣ �߰� 
	location_tree[_flag] = trip.size();
	trip.push_back(no2serial[_flag]);
	for (int i = 0; i < child[_flag].size(); i++) {
		traversal(child[_flag][i], _d + 1, trip);
		trip.push_back(no2serial[_flag]);
	}
}

RMQ* prepareRMQ() {
	nextSerial = 0;
	// ��ȸ ���� �� ������ ����� �Ϸù�ȣ
	vector<int> trip; 
	traversal(0, 0, trip);
	return new RMQ(trip);
}

int distance(RMQ *rmq, int u, int v) {
	int lu = location_tree[u];
	int lv = location_tree[v];
	if (lu > lv) swap(lu, lv);
	int lca = serial2no[rmq->query(lu, lv)]; // tree���� �Ϸù�ȣ�� ���� 
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
		