vector<int> getPartialMatch(const string& str){
	int n = str.size();
	vector<int> pi(n,0);
	int begin = 1, match = 0;
	while(begin+match < n){
		if(str[begin+match] == str[match]) {
			match++;
			pi[begin+match-1]= match;
		}
		else {
			if(match==0) begin++;
			else {
				begin +=  match- pi[match-1];
				match =  pi[match-1];
			}
		}
	}
	return pi;
}
vector<int> kmpSearch(const string& str_h, const string& str_n){
	int n= str_h.size(), m = str_n.size();
	vector<int> pi = getPartialMatch(str_n);
	int begin = 0, matched =0;
	while(begin<= n-m){
		if(matched<m && str_h[begin+matched] == str_n[matched]){
			matched++;
			if(matched ==m) return ret.push_back(begin);
		}
		else{
			if(matched==0) begin++;
			else{
				begin+=matched - pi[matched-1];
				matched = pi[matched-1];
			}
		}
	}
	return ret;	
}