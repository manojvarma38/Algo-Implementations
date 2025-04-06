#include <bits/stdc++.h>
using namespace std;

typedef int64_t ll;     // using int_64t as ll to handle larger values
const ll MOD = 1e9 + 7; // Modulo value defined as a constant

class CurrencySorter
{
public:
    int partition(int left, int right, vector<int> &arr)
    {
        // place pivot in correct place by swapping in-place
        // values less than pivot are placed left of pivot
        // values greater than pivot are placed right of pivot
        int Pivot = arr[right];
        int i = left - 1; // position of smaller elements
        for (int j = left; j < right; j++)
        {
            if (arr[j] < Pivot)
            {
                // If current element is smaller than pivot
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[right]); // Place pivot in its correct position
        return i + 1;                 // Return pivot index
    }
    void quickSort(int left, int right, vector<int> &arr)
    {
        if (left < right)
        {
            int finalPivotIndex = partition(left, right, arr); // Place pivot in correct position
            quickSort(left, finalPivotIndex - 1, arr);         // Recursively sort left part
            quickSort(finalPivotIndex + 1, right, arr);        // Recursively sort right part
        }
    }
    void operator()(vector<int> &arr)
    {
        quickSort(0, arr.size() - 1, arr); // call quicksort function with left and right indices
    }
};

class FibonacciGenerator
{
public:
    // Function to multiply 2 matrices
    void multiplyMatrices(ll matrix1[2][2], ll matrix2[2][2])
    {
        ll p = ((matrix1[0][0] % MOD) * (matrix2[0][0] % MOD) + (matrix1[0][1] % MOD) * (matrix2[1][0] % MOD)) % MOD;
        ll q = ((matrix1[0][0] % MOD) * (matrix2[0][1] % MOD) + (matrix1[0][1] % MOD) * (matrix2[1][1] % MOD)) % MOD;
        ll r = ((matrix1[1][0] % MOD) * (matrix2[0][0] % MOD) + (matrix1[1][1] % MOD) * (matrix2[1][0] % MOD)) % MOD;
        ll s = ((matrix1[1][0] % MOD) * (matrix2[0][1] % MOD) + (matrix1[1][1] % MOD) * (matrix2[1][1] % MOD)) % MOD;

        matrix1[0][0] = p;
        matrix1[0][1] = q;
        matrix1[1][0] = r;
        matrix1[1][1] = s;
    }
    // Iterative matrix exponentiation
    void matrixExponentiation(ll matrix[2][2], ll index)
    {
        ll initialMatrix[2][2] = {{1, 0}, {0, 1}}; // Identity matrix

        while (index > 0)
        {
            if (index % 2 == 1)
                multiplyMatrices(initialMatrix, matrix);
            multiplyMatrices(matrix, matrix); // square matrix and divide index by 2
            index /= 2;
        }
        // assign final matrix to matrix
        matrix[0][0] = initialMatrix[0][0];
        matrix[0][1] = initialMatrix[0][1];
        matrix[1][0] = initialMatrix[1][0];
        matrix[1][1] = initialMatrix[1][1];
    }
    ll operator()(const ll &index)
    {
        // base cases
        if (index == 0)
            return 0LL;
        if (index == 1)
            return 1LL;
        ll matrix[2][2] = {{1, 1}, {1, 0}}; // Fibonacci generator matrix
        matrixExponentiation(matrix, index - 1);
        return matrix[0][0] % MOD;
    }
};

class NumberAnalyzer
{
public:
    bool isSquareFree(ll x)
    {
        if (x % 4 == 0)
            return false;
        for (ll i = 3; i * i <= x; i += 2)
        {
            // If any perfect square divides x ,return false
            if (x % i == 0)
            {
                x /= i;
                if (x % i == 0)
                {
                    return false;
                }
            }
        }
        return true; // No perfect square divides x ,return true
    }
    ll countDivisors(ll x)
    {
        ll count = 0; // Stores the number of divisors of x
        for (ll i = 1; i * i <= x; i++)
        {
            if (x % i == 0)
            {
                if (i == x / i) // If i and x/i are the same,then add only 1 to count
                    count++;
                else // i and x/i are different and both are divisors of x ,add 2 to count
                    count += 2;
            }
        }
        return count;
    }
    ll sumOfDivisors(ll x)
    {
        ll sum = 0; // Stores the sum of divisors of x
        for (ll i = 1; i * i <= x; i++)
        {
            if (x % i == 0)
            {
                if (i == x / i) // If i and x/i are the same,then add only one of them to sum
                    sum += i;
                else // i and x/i are different and both are divisors of x ,add both to sum
                    sum += (i + x / i);
            }
        }
        return sum;
    }
};

class PrimeCalculator
{
public:
    // sieve of Eratosthenes to find prime numbers efficiently
    vector<ll> sieve(ll limit)
    {
        vector<bool> isPrime(limit + 1, true);
        vector<ll> primes;

        isPrime[0] = isPrime[1] = false;
        for (ll i = 2; i <= limit; i++)
        {
            if (isPrime[i])
            {
                primes.push_back(i);
                for (ll j = i * i; j <= limit; j += i)
                    isPrime[j] = false;
            }
        }
        return primes;
    }
    void printPrimes(ll left, ll right)
    {
        if (left == 1)
            left++;
        ll sqrtRight = (ll)sqrt(right); // find prime numbers upto square root right
        vector<ll> primes = sieve(sqrtRight);
        vector<bool> isPrime(right - left + 1, true);
        // use the normal sieve method and mark multiples of primes as non prime
        for (auto &p : primes)
        {
            ll start = max(p * p, (left + p - 1) / p * p);
            for (ll j = start; j <= right; j += p)
                isPrime[j - left] = false;
        }
        for (ll i = 0; i <= right - left; i++)
        {
            if (isPrime[i])
            {
                cout << left + i << ' ';
            }
        }
        cout << '\n';
    }
    void printPrimeSum(ll left, ll right)
    {
        ll sum = 0LL;
        if (left == 1)
            left++;
        ll sqrtRight = (ll)sqrt(right);
        vector<ll> primes = sieve(sqrtRight);
        vector<bool> isPrime(right - left + 1, true);
        for (auto &p : primes)
        {
            ll start = max(p * p, (left + p - 1) / p * p);
            for (ll j = start; j <= right; j += p)
                isPrime[j - left] = false;
        }
        for (ll i = 0; i <= right - left; i++)
        {
            if (isPrime[i])
            {
                sum += (left + i);
            }
        }
        cout << sum << '\n';
    }
};
int main()
{
    int type; // Type of the instruction
    cin >> type;
    if (type == 1)
    {

        ll t;
        cin >> t;
        while (t--)
        {
            int n;
            cin >> n;
            vector<int> arr(n);
            for (int i = 0; i < n; i++)
            {
                cin >> arr[i];
            }
            CurrencySorter mySorter;
            mySorter(arr); // Sorting arr in-place using quickSort Algorithm by passing arr by reference to functor
            // Printing the sorted arr
            for (auto &it : arr)
                cout << it << ' ';
            cout << '\n';
        }
    }
    else if (type == 2)
    {
        ll t;
        cin >> t;
        while (t--)
        {
            ll index;
            cin >> index;
            FibonacciGenerator fibonacci;
            cout << fibonacci(index) % MOD << '\n'; // Finding i th Fibonacci number by passing value of index i to functor
        }
    }
    else if (type == 3)
    {
        PrimeCalculator calculator; // object of PrimeCalculator class
        ll t;
        cin >> t;
        while (t--)
        {
            string command;
            cin >> command;
            if (command == "printPrimes")
            {
                ll l, r;
                cin >> l >> r;
                calculator.printPrimes(l, r);
            }
            else if (command == "printPrimeSum")
            {
                ll l, r;
                cin >> l >> r;
                calculator.printPrimeSum(l, r);
            }
        }
    }
    else if (type == 4)
    {
        NumberAnalyzer Analyzer; // Object of analyzer class
        ll t;
        cin >> t;
        while (t--)
        {
            string command;
            cin >> command;
            if (command == "isSquareFree")
            {
                ll x;
                cin >> x;
                if (Analyzer.isSquareFree(x))
                {
                    cout << "yes" << '\n';
                }
                else
                    cout << "no" << '\n';
            }
            else if (command == "countDivisors")
            {
                ll x;
                cin >> x;
                cout << Analyzer.countDivisors(x) << '\n';
            }
            else if (command == "sumOfDivisors")
            {
                ll x;
                cin >> x;
                cout << Analyzer.sumOfDivisors(x) << '\n';
            }
        }
    }
    return 0;
}