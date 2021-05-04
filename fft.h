/*
We have created a namespace for Fast Fourier Transform(FFT).
We have a self defined 'Complex' class which helps us with complex numbers and operations related to it.
*/

namespace fft {

/*
Given is the definition for the 'Complex' class.
*/
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
//This is like a __repr__ function in python. Used to print the complex class elements 
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

using cd = Complex<double>;//=typedef,#define
const double PI = acos(-1);

/*
fft_build : Used to apply Fast Fourier Transform and Inverse Fourier Transform on the given vector.
It is a builtin feature(private) of the namespace which cant be accessed by the users directly.
@params: vector a - vector on which FFT or Inverse FFT needs to be applied.
		 bool invert: to determine if inverse FFT needs to be computed (when set to True).
*/
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

/*
@brief: used to copy the elements of the container to a vector(will be used later)
@params: first1, last1 - Starting and ending iterator of the first container
		first2, last2 - Starting and ending iterator of the second container
		a,b - Vectors used to compute FFT
*/

template<typename ptr1, typename ptr2, class V>
void init(ptr1 first1, ptr1 last1, ptr2 first2, ptr2 last2, V &a, V &b) {
	while (first1 != last1) {
		a.push_back(*first1);
		++first1;
	}
	while (first2 != last2) {
		b.push_back(*first2);
		++first2;
	}
}

/*
@brief: Applies FFT to the given containers and does the multiplication in O(nlogn) time.
The parameters can be different types of containers
@params : first1, last1 - Starting and ending iterator of the first container
		  first2, last2 - Starting and ending iterator of the second container
*/

template<typename T, typename ptr1, typename ptr2>
vector<T> multiply(ptr1 first1, ptr1 last1, ptr2 first2, ptr2 last2) {
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

/*
@brief : Additional feature of the namespace to see if a binary pattern occurs in a binary text.
		 Returns the location of the matches.
@params : Takes only strings as the input; str is the text, pattern is the pattern
*/
vector <int> binary_matching(string str, string pattern) {
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