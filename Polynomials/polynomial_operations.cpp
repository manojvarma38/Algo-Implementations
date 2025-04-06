#include <bits/stdc++.h>
using namespace std;

// typdef declarations for shorter variables
typedef long long int ll;
typedef long double ld;

// complex class
class Complex
{
private:
    ll real, imaginary;

public:
    // default constructor
    Complex(ll num = 0LL)
    {
        real = num;
        imaginary = 0LL;
    }
    // parameterized constructor
    Complex(const ll real, const ll imaginary)
    {

        this->real = real;
        this->imaginary = imaginary;
    }
    // overloaded + operator for complex class
    Complex operator+(const Complex &c)
    {

        ll realValue = real + c.real;
        ll imaginaryValue = imaginary + c.imaginary;

        return Complex(realValue, imaginaryValue);
    }
    // overloaded - operator for complex class
    Complex operator-(const Complex &c)
    {
        ll realValue = real - c.real;
        ll imaginaryValue = imaginary - c.imaginary;

        return Complex(realValue, imaginaryValue);
    }
    // overloaded * operator for complex class
    Complex operator*(const Complex &c) const
    {
        ll realValue = real * c.real - imaginary * c.imaginary;
        ll imaginaryValue = real * c.imaginary + imaginary * c.real;

        return Complex(realValue, imaginaryValue);
    }

    friend ostream &operator<<(ostream &stream, const Complex &c);
};

// overload cout for printing complex numbers
ostream &operator<<(ostream &stream, const Complex &c)
{
    stream << c.real << ' ' << c.imaginary;
    return stream;
}

// overload multiply operator for string
string operator*(const string &str, ll num)
{
    string result = "";
    for (ll i = 0; i < num; i++)
    {
        result += str;
    }
    return result;
}

// polynomial class with templates
template <typename T>
class Polynomial
{
private:
    vector<T> coefficients;

public:
    // Default constructor
    Polynomial() {}

    Polynomial(const vector<T> &coeff)
    {
        coefficients = coeff;
    }
    vector<T> getCoefficients()
    {
        return coefficients;
    }

    // overload multiply operator
    // use Karatsuba's Algorithm to achieve the operation in O(N * LOG N) Time Complexity
    Polynomial<T> operator*(const Polynomial &c)
    {
        vector<T> multi = karatsubaMultiply(coefficients, c.coefficients);
        Polynomial<T> multiplication(multi);
        return multiplication;
    }

    // Karatsuba Algo
    vector<T> karatsubaMultiply(const vector<T> &a, const vector<T> &b)
    {
        ll n = a.size(), m = b.size();
        ll finalSize = 1;
        // multiply size to power of 2
        while (finalSize < max(n, m))
            finalSize *= 2;
        finalSize *= 2;
        vector<T> A(finalSize, T(0)), B(finalSize, T(0));
        for (int i = 0; i < n; i++)
            A[i] = a[i];
        for (int i = 0; i < m; i++)
            B[i] = b[i];
        vector<T> answer = helperFunction(A, B, finalSize);
        answer.resize(n + m - 1); // cut the extra part
        return answer;
    }

    // helper function for recursion
    vector<T> helperFunction(const vector<T> &A, const vector<T> &B, ll n)
    {
        vector<T> answer(2 * n, T(0));
        if (n == 1) // base case
        {
            answer[0] = A[0] * B[0];
            return answer;
        }

        // divide polynomials into two halves
        ll half = n / 2;
        vector<T> aLow(A.begin(), A.begin() + half);
        vector<T> aHigh(A.begin() + half, A.end());
        vector<T> bLow(B.begin(), B.begin() + half);
        vector<T> bHigh(B.begin() + half, B.end());

        // recurse on both halves
        vector<T> low = helperFunction(aLow, bLow, half);
        vector<T> high = helperFunction(aHigh, bHigh, half);

        vector<T> aSum(half), bSum(half);
        for (ll i = 0; i < half; i++)
        {
            aSum[i] = aLow[i] + aHigh[i];
            bSum[i] = bLow[i] + bHigh[i];
        }
        // third recursion
        vector<T> mid = helperFunction(aSum, bSum, half);

        for (int i = 0; i < 2 * half; i++)
        {
            if (i < (ll)low.size())
                mid[i] = mid[i] - low[i];
            if (i < (ll)high.size())
                mid[i] = mid[i] - high[i];
        }

        for (int i = 0; i < 2 * half; i++)
        {
            answer[i] = answer[i] + low[i];
            answer[i + half] = answer[i + half] + mid[i];
            answer[i + 2 * half] = answer[i + 2 * half] + high[i];
        }
        return answer;
    }
};

// multiplication class
template <typename T>
class Multiplication
{
private:
    Polynomial<T> poly1, poly2;

public:
    Multiplication(const Polynomial<T> &p1, const Polynomial<T> &p2)
    {
        poly1 = p1;
        poly2 = p2;
    }
    void Multiply()
    {
        Polynomial<T> PolynomialMultiplication = poly1 * poly2;
        vector<T> coef = PolynomialMultiplication.getCoefficients();
        for (ll i = 0; i < (ll)coef.size(); i++)
        {
            cout << fixed << setprecision(6) << coef[i] << ' ';
        }
        cout << '\n';
    }
};

// Differentiation class
template <typename T>
class Differentiation
{
private:
    Polynomial<T> poly;

public:
    Differentiation(const Polynomial<T> &p)
    {
        poly = p;
    }
    void Differentiate()
    {
        vector<T> coef = poly.getCoefficients();
        for (ll i = 1; i < (ll)coef.size(); i++)
        {
            cout << fixed << setprecision(6) << i * coef[i] << ' ';
        }
        cout << '\n';
    }
};

// Evaluation class
template <typename T>
class Evaluation
{
private:
    Polynomial<T> poly;

public:
    Evaluation(const Polynomial<T> &p)
    {
        poly = p;
    }
    void Evaluate(ll x)
    {
        vector<T> coef = poly.getCoefficients();
        if (x == 0)
        {
            cout << fixed << setprecision(6) << coef[0] << '\n';
            return;
        }
        ll n = coef.size();
        ll num = (ll)pow(x, n - 1);
        T result = coef[n - 1] * num;
        for (ll i = n - 2; i >= 0; i--)
        {
            num /= x;
            result = result + coef[i] * num;
        }
        cout << fixed << setprecision(6) << result << '\n';
    }
};

int main()
{

    ll q;
    cin >> q;
    while (q--)
    {
        ll type;
        cin >> type;
        if (type == 1)
        {
            string s;
            cin >> s;
            if (s == "integer")
            {
                ll num1;
                cin >> num1;
                vector<ll> coef1(num1);
                for (ll i = 0; i < num1; i++)
                {
                    cin >> coef1[i];
                }

                ll num2;
                cin >> num2;
                vector<ll> coef2(num2);
                for (ll i = 0; i < num2; i++)
                {
                    cin >> coef2[i];
                }

                Multiplication<ll> mult((Polynomial<ll>(coef1)), (Polynomial<ll>(coef2)));
                mult.Multiply();
            }
            else if (s == "float")
            {
                ll num1;
                cin >> num1;
                vector<ld> coef1(num1);
                for (ll i = 0; i < num1; i++)
                {
                    cin >> coef1[i];
                }

                ll num2;
                cin >> num2;
                vector<ld> coef2(num2);
                for (ll i = 0; i < num2; i++)
                {
                    cin >> coef2[i];
                }

                Multiplication<ld> mult((Polynomial<ld>(coef1)), (Polynomial<ld>(coef2)));
                mult.Multiply();
            }
            else if (s == "complex")
            {
                ll num1;
                cin >> num1;
                vector<Complex> coef1(num1);
                for (ll i = 0; i < num1; i++)
                {
                    ll real, imaginary;
                    cin >> real >> imaginary;
                    coef1[i] = Complex(real, imaginary);
                }

                ll num2;
                cin >> num2;
                vector<Complex> coef2(num2);
                for (ll i = 0; i < num2; i++)
                {
                    ll real, imaginary;
                    cin >> real >> imaginary;
                    coef2[i] = Complex(real, imaginary);
                }

                Multiplication<Complex> mult((Polynomial<Complex>(coef1)), (Polynomial<Complex>(coef2)));
                mult.Multiply();
            }
        }
        else if (type == 2)
        {
            string s;
            cin >> s;
            if (s == "integer")
            {
                ll num;
                cin >> num;
                vector<ll> coef(num);
                for (ll i = 0; i < num; i++)
                {
                    cin >> coef[i];
                }
                ll x;
                cin >> x;
                Evaluation<ll> eval((Polynomial<ll>(coef)));
                eval.Evaluate(x);
            }
            else if (s == "float")
            {
                ll num;
                cin >> num;
                vector<ld> coef(num);
                for (ll i = 0; i < num; i++)
                {
                    cin >> coef[i];
                }

                ll x;
                cin >> x;
                Evaluation<ld> eval((Polynomial<ld>(coef)));
                eval.Evaluate(x);
            }
            else if (s == "string")
            {
                ll num;
                cin >> num;
                vector<string> coef(num);
                for (ll i = 0; i < num; i++)
                {
                    cin >> coef[i];
                }

                ll x;
                cin >> x;
                Evaluation<string> eval((Polynomial<string>(coef)));
                eval.Evaluate(x);
            }
        }
        else if (type == 3)
        {
            string s;
            cin >> s;
            if (s == "integer")
            {
                ll num;
                cin >> num;
                vector<ll> coef(num);
                for (ll i = 0; i < num; i++)
                {
                    cin >> coef[i];
                }

                Differentiation<ll> diff((Polynomial<ll>(coef)));
                diff.Differentiate();
            }
            else if (s == "float")
            {
                ll num;
                cin >> num;
                vector<ld> coef(num);
                for (ll i = 0; i < num; i++)
                {
                    cin >> coef[i];
                }

                Differentiation<ld> diff((Polynomial<ld>(coef)));
                diff.Differentiate();
            }
        }
    }

    return 0;
}
