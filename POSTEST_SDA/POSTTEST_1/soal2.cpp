#include <iostream>
using namespace std;

struct DataMahasiswa
{
    string nama;
    string nim;
    float ipk;
};

int main()
{
    DataMahasiswa mhs[5];
    for (int i = 0; i < 5; i++)
    {
        cout << "Mahasiswa ke-" << i + 1 << endl;
        cout << "Nama: ";
        cin >> mhs[i].nama;
        cout << "NIM: ";
        cin >> mhs[i].nim;
        cout << "IPK: ";
        cin >> mhs[i].ipk;
        cout << endl;
    }
    int indexMax = 0;
    for (int i = 1; i < 5; i++)
    {
        if (mhs[i].ipk > mhs[indexMax].ipk)
        {
            indexMax = i;
        }
    }
    cout << "\nMahasiswa dengan IPK tertinggi adalah:\n";
    cout << "Nama: " << mhs[indexMax].nama << endl;
    cout << "NIM : " << mhs[indexMax].nim << endl;
    cout << "IPK : " << mhs[indexMax].ipk << endl;

    return 0;
}