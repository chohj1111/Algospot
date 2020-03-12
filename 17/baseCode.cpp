//부분합
vector<int> partialSum(const vector<int>& a){ 
	vector<int> ret(a.size());
	ret[0] = a[0]
	for(int i=1;i<a.size();i++){
		ret[i] += a[i];
	}
	return ret;
}
//구간합
int rangeSum(const vector<int>& psum, int start, int end){
	if(start==0) return psum[end];
	return psum[end]-psum[start-1];
}
