// Simple C++ program to multiply two polynomials
#include <bits/stdc++.h>
#include<chrono>
using namespace std;
using namespace std::chrono;
#define ll long long
#define fo(i,k,n) for(ll i=k;i<n;i++)
// A[] represents coefficients of first polynomial
// B[] represents coefficients of second polynomial
// m and n are sizes of A[] and B[] respectively
vector<int> multiply(vector<int> &A, vector<int> &B, int m, int n)
{
   //int *prod = new int[m+n-1];
    vector<int> prod(m+n-1);
   // Initialize the porduct polynomial
 
   // Multiply two polynomials term by term
 
   // Take ever term of first polynomial
   for (int i=0; i<m; i++)
   {
     // Multiply the current term of first polynomial
     // with every term of second polynomial.
     for (int j=0; j<n; j++)
         prod[i+j] += A[i]*B[j];
   }
 
   return prod;
}
 
// A utility function to print a polynomial
void printPoly(vector<int> poly, int n)
{
    for (int i=0; i<n; i++)
    {
       cout << poly[i];
       if (i != 0)
        cout << "x^" << i ;
       if (i != n-1)
       cout << " + ";
    }
}
 
// Driver program to test above functions
int main()
{
	#ifndef ONLINE_JUDGE
 	freopen("input.txt", "r", stdin);

 	freopen("output2.txt", "w", stdout);
	#endif
    // The following array represents polynomial 5 + 10x^2 + 6x^3
	int s1, s2;
	cin >> s1 >> s2;
	//vector<int> a, b;
	//list<int> a, b;
	vector<int> a, b;
	double x;
	vector<int> values(10000);
	fo(i, 0, s1) cin >> x, a.push_back(x);
	fo(i, 0, s2) cin >> x, b.push_back(x);
auto f = []() -> int { return rand() % 10000; };
	generate(values.begin(), values.end(), f);
	auto start = high_resolution_clock::now();
    vector<int> prod = multiply(a,b,s1,s2);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Time taken by function: " << duration.count() << " microseconds" << "\n";
	cout<<"Result of Polynomial Multiplication: ";

    cout << "nProduct polynomial is n";
    printPoly(prod, s1+s2-1);
 
    return 0;
}