#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

int main(){
	long long A, B;
	size_t cnt = 0;

	std::vector<long long> black;
	std::vector<long long> white;

	string str;
	cin >> A >> B;
	cin >> str;

	for (auto &letter : str){
		if (letter == 'B')
			cnt++;
	}

	for (long long ix = cnt - 1; ix >= 0; ix--){
		if(str[ix] == 'W')
			white.push_back(ix);
	}

	for (long long ix = cnt; ix < str.size(); ix++){
		if(str[ix] == 'B')
			black.push_back(ix);
	}
	std::cout << "black" << '\n';
	for (auto &pos : black) std::cout << "pos : "<<pos << '\n';
	std::cout << "white" << '\n';
	for (auto &pos : white) std::cout << "pos :" << pos<<'\n';

	long long sum = 0;
	long long C1 = A;
	long long C2 = A - B;
	for (long long ix = 0 ; ix < black.size() ;ix++){
		std::cout <<abs(black[ix]-white[ix])*C2 << '\n';
		std::cout << C1 << '\n';
		sum = sum + min( abs(black[ix]-white[ix])*C2,C1);
	}
	cout<<sum<<"\n";

	return 0;
}
