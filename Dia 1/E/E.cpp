#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main(){
	int A, B;
	size_t cnt = 0;

	std::vector<int> black;
	std::vector<int> white;

	string str;
	cin >> A >> B;
	cin >> str;

	for (auto &letter : str){
		if (letter == 'B')
			cnt++;
	}

	for (int ix = cnt - 1; ix >= 0; ix--){
		if(str[ix] == 'W')
			white.push_back(ix);
	}

	for (int ix = cnt; ix < str.size(); ix++){
		if(str[ix] == 'B')
			black.push_back(ix);
	}
	int sum=0;
	int C1 = A;
	int C2 = A - B;
	for (int ix=0 ; ix < cnt;ix++){
		sum = sum + min( abs(black[ix]-white[ix]) * C2,C1);
	}
	cout<<sum<<"\n";

	return 0;
}