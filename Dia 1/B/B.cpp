#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main (){
	size_t n, k, x;
	size_t maj = 0;
	int pos_maj = 0;
	size_t n_x = 1;

	cin >> n >> k >> x;

	std::vector<size_t> vec(n);
	std::map<size_t, bool> hist;

	for (int ix = 0; ix < vec.size(); ix++){
		cin >> vec[ix];

		if (vec[ix] >= maj){
			maj = vec[ix];
			pos_maj = ix;
		}
	}

	for (int ix = 0; ix < k; ix++){
		n_x = n_x * x;
	}

	vec[pos_maj] = vec[pos_maj] * n_x;
	size_t sum = 0;

	for (auto &elem : vec){
		if(hist.find(elem) == hist.end()){
			sum += elem;
			hist.insert({elem, true});
		} else {
			continue;
		}
	}
	
	cout << sum << '\n'; 


	return 0;
}