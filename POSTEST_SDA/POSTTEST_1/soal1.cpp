#include <iostream>
using namespace std;
/*
Analisis kompleksitas waktu
1. min = A[0]                : 1 kali
2. inisialisasi i            : 1 kali
3. pengecekan i < n          : n kali
4. A[i] < min                : (n-1) kali
5. min = A[i] (worst case)   : (n-1) kali
6. increment i               : (n-1) kali

Worst case:
jika Semua kondisi true.
T(n) = 1 + 1 + n + (n-1) + (n-1) + (n-1)
T(n) = 2 + n + 3(n-1)
T(n) = 2 + n + 3n - 3
T(n) = 4n - 1

Best case:
jika Tidak pernah masuk ke min = A[i].
T(n) = 1 + 1 + n + (n-1) + (n-1)
T(n) = 2 + n + 2(n-1)
T(n) = 2 + n + 2n - 2
T(n) = 3n

bentuk akhirnya linear terhadap n,maka:
- Best Case  = O(n)
- Worst Case = O(n)
*/
int FindMin(int A[], int n, int &indexMin)
{
    int min = A[0];
    indexMin = 0;

    for (int i = 1; i < n; i++)
    {
        if (A[i] < min)
        {
            min = A[i];
            indexMin = i;
        }
    }
    return min;
}

int main()
{
    int fib[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int indexMin;

    int minimum = FindMin(fib, 8, indexMin);

    cout << "Nilai minimum  : " << minimum << endl;
    cout << "Indeks minimum : " << indexMin << endl;

    return 0;
}