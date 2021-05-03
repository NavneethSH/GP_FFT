#include "fft.h"

void solve() {
	int s1, s2;
	cin >> s1 >> s2;
	vector<int> a;
	//list<int> a, b;
	deque<double> b;
	double x;
	vector<int> values(10000);
	fo(i, 0, s1) cin >> x, a.push_back(x);
	fo(i, 0, s2) cin >> x, b.push_back(x);
auto f = []() -> int { return rand() % 10000; };
	generate(values.begin(), values.end(), f);
	auto start = high_resolution_clock::now();
	vector<double> res = fft::multiply<double>(a.begin(), a.end(), b.begin(), b.end());
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by function: " << duration.count() << " microseconds" << "\n";
	cout<<"Result of Polynomial Multiplication: ";
	fo(i, 0, (s1 + s2) - 1) {
		cout << res[i] << " ";
	}
	cout << "\n";
	//cout << *(b.begin() + 1) << "\n";
	//string
	string text = "10100101";
	string pat = "101";
	cout<<"The pattern "<<pat<<" is found in locations ";
	vector<int> ham = fft::binary_matching("10100101", "101");
	for (auto it : ham) cout << it << " ";
	cout<<"of the text "<<text<<"\n";
}

int main()
{
	speed_up;
	#ifndef ONLINE_JUDGE
 	freopen("input.txt", "r", stdin);

 	freopen("output.txt", "w", stdout);
	#endif

	solve();
	return 0;
}
