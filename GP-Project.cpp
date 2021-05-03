#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

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

template<typename T>
class Complex {
private:
	T m_real;
	T m_imag;
public:
	Complex<T>(T real = 0.0, T imag = 0.0)
		: m_real(real), m_imag(imag) { };
	Complex<T>(const Complex<T>& c)
		: m_real(c.m_real), m_imag(c.m_imag) { };

	Complex<T> operator -() const;
	Complex<T>& operator +=(const Complex<T>&);
	Complex<T>& operator -=(const Complex<T>&);
	Complex<T>& operator *=(const Complex<T>&);
	Complex<T>& operator /=(const Complex<T>&);
	Complex<T> operator +(const Complex<T>&) const;
	Complex<T> operator -(const Complex<T>&) const;
	Complex<T> operator *(const Complex<T>&) const;
	Complex<T> operator /(const Complex<T>&) const;
	template<typename U>
	friend ostream& operator <<(ostream&, const Complex<U>&);
	T real();
	T imag();
};

template<typename T>
Complex<T> Complex<T>::operator -() const {
	return Complex(-m_real, -m_imag);
}

template<typename T>
Complex<T>& Complex<T>::operator +=(const Complex<T>& c2) {
	m_real += c2.m_real;
	m_imag += c2.m_imag;
	return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator -=(const Complex<T>& c2) {
	return *this += -c2;
}

template<typename T>
Complex<T>& Complex<T>::operator *=(const Complex<T>& c2) {
	T real = m_real * c2.m_real - m_imag * c2.m_imag;
	T imag = m_real * c2.m_imag + m_imag * c2.m_real;
	m_real = real;
	m_imag = imag;
	return *this;
}

template<typename T>
Complex<T>& Complex<T>::operator /=(const Complex<T>& c2) {
	Complex<T> nm = Complex<T>(*this) * Complex<T>(c2.m_real, -c2.m_imag);
	T dn = c2.m_real * c2.m_real + c2.m_imag * c2.m_imag;
	m_real = nm.m_real / dn;
	m_imag = nm.m_imag / dn;
	return *this;
}

template<typename T>
Complex<T> Complex<T>::operator +(const Complex<T>& c2) const {
	return Complex<T>(*this) += c2;
}

template<typename T>
Complex<T> Complex<T>::operator -(const Complex<T>& c2) const {
	return Complex<T>(*this) -= c2;
}

template<typename T>
Complex<T> Complex<T>::operator *(const Complex<T>& c2) const {
	return Complex<T>(*this) *= c2;
}

template<typename T>
Complex<T> Complex<T>::operator /(const Complex<T>& c2) const {
	return Complex<T>(*this) /= c2;
}

template<typename T>
ostream& operator <<(ostream& os, const Complex<T>& c) {
	os << c.m_real;
	if (c.m_imag < 0)
		os << c.m_imag << "i";
	else if (c.m_imag > 0)
		os << "+" << c.m_imag << "i";
	return os;
}

template<typename T>
T Complex<T>::real() {
	return this->m_real;
}
template<typename T>
T Complex<T>::imag() {
	return this->m_imag;
}

using cd = Complex<double>;
const double PI = acos(-1);

template<typename T>
void fft_build(vector<T> & a, bool invert) {
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

template<typename ptr1, typename ptr2, class V>
void init(ptr1 first1, ptr2 last1, ptr1 first2, ptr2 last2, V &a, V &b) {
	while (first1 != last1) {
		a.push_back(*first1);
		++first1;
	}
	while (first2 != last2) {
		b.push_back(*first2);
		++first2;
	}
}

//template<typename T>
//template<typename T, class V>
template<typename T, typename ptr1, typename ptr2>
vector<T> multiply(ptr1 first1, ptr2 last1, ptr1 first2, ptr2 last2) {
	vector<cd> fa, fb;
	//vector<cd> fa(first1, last1), fb(first2, last2);
	init(first1, last1, first2, last2, fa, fb);
	//for (auto it : fb)cout << it << " ";
	int n = 1;
	while (n < fa.size() + fb.size())
		n <<= 1;
	fa.resize(n);
	fb.resize(n);

	fft_build(fa, false);
	fft_build(fb, false);
	for (int i = 0; i < n; i++)
		fa[i] *= fb[i];
	fft_build(fa, true);

	vector<T> result(n);
	for (int i = 0; i < n; i++)
		result[i] = fa[i].real();   //round
	return result;
}

//Binary string
//returns the location of the matches
vector <int> hamming_distance(string str, string pattern) {
	int n = str.size(), m = pattern.size();
	vector<int> P(n);
	vector<int> Q(n);
	for (int i = 0; i < n; i++) P[i] = Q[i] = 0;
	for (int i = 0; i < n; i++) P[i] = str[i] == '1' ? 1 : -1;
	for (int i = 0, j = m - 1; j >= 0; i++, j--) Q[i] = pattern[j] == '1' ? 1 : -1;
	vector <int> res;
	vector <double> res2 = multiply<double>(P.begin(), P.end(), Q.begin(), Q.end());
	for (int i = 0; (i + m) <= n; i++) {
		if (m - (int((round(res2[i + m - 1])) + m) >> 1) == 0)
			res.push_back(i);
		//res.push_back(m - (int((round(res2[i + m - 1])) + m) >> 1));
	}
	return res;
}
}

void solve() {
	int s1, s2;
	cin >> s1 >> s2;
	//vector<int> a, b;
	//list<int> a, b;
	deque<double> a, b;
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
	vector<int> ham = fft::hamming_distance("10100101", "101");
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


/*
//vector<double> res2 = fft::multiply2<double>(a, b);
	//for (auto it : res)cout << it << " ";
	//cout << "\n";
	// fo(i, 0, (s1 + s2) - 1) {
	// 	cout << res[i] << ":" << res2[i] << " ";
	// }
*/
