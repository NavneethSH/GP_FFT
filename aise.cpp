#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int main()
{
vector<int> a{1,2,3,4,5,6,7,8};
int n = a.size();
for (int i = 1, j = 0; i < n; i++) {
	int bit = n >> 1;
	for (; j & bit; bit >>= 1)
		j ^= bit;
	j ^= bit;
	cout<<"i: "<<i<<" j: "<<j<<"\n";
}
return 0;
}