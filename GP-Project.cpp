#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<ll, ll> PLL;
typedef vector<string> VS;
typedef vector<ll> VL;
typedef vector<vector<ll>> VVL;
typedef vector<int> VI;
typedef map<ll, ll> MPLL;

#define fo(i,k,n) for(ll i=k;i<n;i++)
#define myfo(i,k,n,c) for(ll i=k;i<n;i+=c)
#define rfo(i,n,k) for(ll i=n-1;i>=k;--i)
#define MP make_pair
#define PB push_back
#define all(x) (x).begin(), (x).end()
#define speed_up ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

namespace fft {
using cd = complex<double>;
const double PI = acos(-1);

void fft_build(vector<cd> & a, bool invert) {
	int n = a.size();

	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j & bit; bit >>= 1)
			j ^= bit;
		j ^= bit;

		if (i < j)
			swap(a[i], a[j]);
	}

	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2 * PI / len * (invert ? -1 : 1);
		cd wlen(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len) {
			cd w(1);
			for (int j = 0; j < len / 2; j++) {
				cd u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}

	if (invert) {
		for (cd & x : a)
			x /= n;
	}
}
vector<int> multiply(vector<int> const& a, vector<int> const& b) {
	vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	while (n < a.size() + b.size())
		n <<= 1;
	fa.resize(n);
	fb.resize(n);

	fft_build(fa, false);
	fft_build(fb, false);
	for (int i = 0; i < n; i++)
		fa[i] *= fb[i];
	fft_build(fa, true);

	vector<int> result(n);
	for (int i = 0; i < n; i++)
		result[i] = round(fa[i].real());
	return result;
}
}

void solve() {
	int s1, s2;
	cin >> s1 >> s2;
	vector<int> a(s1);
	vector<int> b(s2);
	fo(i, 0, s1) cin >> a[i];
	fo(i, 0, s2) cin >> b[i];
	vector<int> res = fft::multiply(a, b);
	//for (auto it : res)cout << it << " ";
	cout << "\n";
	fo(i, 0, (s1 + s2) - 1) {
		cout << res[i] << " ";
	}
	cout << "\n";
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