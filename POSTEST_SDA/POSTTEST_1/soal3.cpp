#include <iostream>
using namespace std;

void reverseArray(int *arr, int n)
{
    int *start = arr;
    int *end = arr + n - 1;
    while (start < end)
    {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int main()
{
    int bilprima[7] = {2, 3, 5, 7, 11, 13, 17};

    cout << "Array sebelum dibalik:\n";
    for (int i = 0; i < 7; i++)
    {
        cout << bilprima[i] << " ";
    }

    cout << "\n\nAlamat memori dari setiap elemen:\n";
    int *ptr = bilprima;
    for (int i = 0; i < 7; i++)
    {
        cout << "Alamat elemen ke " << i << ": " << (ptr + i) << endl;
    }

    reverseArray(bilprima, 7);

    cout << "\nArray setelah dibalik:\n";
    for (int i = 0; i < 7; i++)
    {
        cout << bilprima[i] << " ";
    }

    return 0;
}