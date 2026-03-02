#include <iostream>
using namespace std;

void pertukaran(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int x, y;

    cout << "Masukkan nilai dari x: ";
    cin >> x;
    cout << "Masukkan nilai dari y: ";
    cin >> y;

    cout << "\nSebelum pertukaran:\n";
    cout << "x = " << x << ", y = " << y << endl;

    pertukaran(&x, &y);

    cout << "\nSetelah pertukaran:\n";
    cout << "x = " << x << ", y = " << y << endl;

    return 0;
}