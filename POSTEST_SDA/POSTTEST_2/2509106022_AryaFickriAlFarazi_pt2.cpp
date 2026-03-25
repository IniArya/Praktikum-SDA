#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

struct Kereta
{
    int nomorKereta;
    string namaKereta;
    string asal;
    string tujuan;
    string jamBerangkat;
    string jamTiba;
    double hargaTiket;
};

const int MAX_KERETA = 50;
Kereta dataKereta[MAX_KERETA];
int jumlahKereta = 0;

const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string RED = "\033[31m";

void garisPemisah(char c = '=', int panjang = 75)
{
    cout << string(panjang, c) << endl;
}

void cetakHeader(const string &judul)
{
    cout << endl;
    garisPemisah();
    int pad = (75 - (int)judul.size()) / 2;
    cout << BOLD << string(pad, ' ') << judul << RESET << endl;
    garisPemisah();
}

bool cekKosong(int n)
{
    if (n == 0)
    {
        cout << RED << "  Belum ada data kereta." << RESET << endl;
        return true;
    }
    return false;
}

string toLower(const string &s)
{
    string hasil = s;
    for (char &c : hasil)
        c = tolower(c);
    return hasil;
}

void cetakKereta(const Kereta *k)
{
    cout << left
         << "| " << setw(5) << k->nomorKereta
         << "| " << setw(20) << k->namaKereta
         << "| " << setw(12) << k->asal
         << "| " << setw(12) << k->tujuan
         << "| " << setw(7) << k->jamBerangkat
         << "| " << setw(7) << k->jamTiba
         << "| Rp " << setw(10) << fixed << setprecision(0) << k->hargaTiket << "|"
         << endl;
}

void cetakHeaderTabel()
{
    garisPemisah('-', 88);
    cout << left
         << "| " << setw(5) << "No."
         << "| " << setw(20) << "Nama Kereta"
         << "| " << setw(12) << "Asal"
         << "| " << setw(12) << "Tujuan"
         << "| " << setw(7) << "Brgkt"
         << "| " << setw(7) << "Tiba"
         << "| " << setw(14) << "Harga Tiket" << "|"
         << endl;
    garisPemisah('-', 88);
}

void tampilSemuaKereta(Kereta *arr, int n)
{
    cetakHeader("JADWAL SEMUA KERETA API");
    if (cekKosong(n))
        return;

    cetakHeaderTabel();
    for (int i = 0; i < n; i++)
        cetakKereta(arr + i);
    garisPemisah('-', 88);
    cout << GREEN << "  Total kereta: " << n << RESET << endl;
}

void tambahKereta()
{
    cetakHeader("TAMBAH DATA KERETA BARU");

    if (jumlahKereta >= MAX_KERETA)
    {
        cout << RED << "  Data penuh! Maksimal " << MAX_KERETA << " kereta." << RESET << endl;
        return;
    }

    Kereta *k = &dataKereta[jumlahKereta];

    cout << "  Nomor Kereta     : ";
    cin >> k->nomorKereta;
    cin.ignore(); // buang '\n' sisa cin >> sebelum getline
    cout << "  Nama Kereta      : ";
    getline(cin, k->namaKereta);
    cout << "  Asal             : ";
    getline(cin, k->asal);
    cout << "  Tujuan           : ";
    getline(cin, k->tujuan);
    cout << "  Jam Berangkat    : ";
    getline(cin, k->jamBerangkat);
    cout << "  Jam Tiba         : ";
    getline(cin, k->jamTiba);
    cout << "  Harga Tiket (Rp) : ";
    cin >> k->hargaTiket;

    jumlahKereta++;
    cout << GREEN << "\n  Data kereta berhasil ditambahkan!" << RESET << endl;
}

void swapKereta(Kereta *a, Kereta *b)
{
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void linearSearchRute()
{
    cetakHeader("LINEAR SEARCH - CARI BERDASARKAN RUTE");

    string cariAsal, cariTujuan;
    // PERBAIKAN: hapus cin.ignore() di sini karena main() sudah memanggil
    // cin.ignore() setelah cin >> pilihan, sehingga buffer sudah bersih
    cout << "  Masukkan Kota Asal   : ";
    getline(cin, cariAsal);
    cout << "  Masukkan Kota Tujuan : ";
    getline(cin, cariTujuan);

    cout << endl;
    garisPemisah('-', 75);
    cout << YELLOW << "  [Proses Pencarian Linear Search]" << RESET << endl;
    garisPemisah('-', 75);

    bool ditemukan = false;
    int jumlahHasil = 0;

    for (int i = 0; i < jumlahKereta; i++)
    {
        Kereta *p = dataKereta + i;

        cout << "  Iterasi " << setw(2) << i + 1
             << " -> Cek [" << (p + 0)->namaKereta << "] "
             << p->asal << " -> " << p->tujuan;

        if (toLower(p->asal) == toLower(cariAsal) &&
            toLower(p->tujuan) == toLower(cariTujuan))
        {
            cout << GREEN << "  << COCOK >>" << RESET;
            ditemukan = true;
            jumlahHasil++;
        }
        cout << endl;
    }

    garisPemisah('-', 75);

    if (ditemukan)
    {
        cout << GREEN << "\n  Hasil ditemukan - Rute: " << cariAsal << " -> " << cariTujuan << RESET << endl;
        cetakHeaderTabel();
        for (int i = 0; i < jumlahKereta; i++)
        {
            Kereta *p = dataKereta + i;
            if (toLower(p->asal) == toLower(cariAsal) &&
                toLower(p->tujuan) == toLower(cariTujuan))
                cetakKereta(p);
        }
        garisPemisah('-', 88);
        cout << GREEN << "  Total hasil: " << jumlahHasil << " kereta." << RESET << endl;
    }
    else
    {
        cout << RED << "\n  Rute " << cariAsal << " -> " << cariTujuan
             << " tidak ditemukan." << RESET << endl;
    }
}

void sortByNomor(Kereta *arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        Kereta key = *(arr + i);
        int j = i - 1;
        while (j >= 0 && (arr + j)->nomorKereta > key.nomorKereta)
        {
            *(arr + j + 1) = *(arr + j);
            j--;
        }
        *(arr + j + 1) = key;
    }
}

void jumpSearchNomor()
{
    cetakHeader("JUMP SEARCH - CARI BERDASARKAN NOMOR KERETA");
    if (cekKosong(jumlahKereta))
        return;

    int cariNomor;
    cout << "  Masukkan Nomor Kereta yang dicari: ";
    cin >> cariNomor;

    Kereta salinan[MAX_KERETA];
    copy(dataKereta, dataKereta + jumlahKereta, salinan);
    sortByNomor(salinan, jumlahKereta);

    int n = jumlahKereta;
    int step = (int)sqrt((double)n);
    int prev = 0;

    cout << endl;
    garisPemisah('-', 75);
    cout << YELLOW << "  [Proses Jump Search - step = " << step << "]" << RESET << endl;
    garisPemisah('-', 75);

    int iterasi = 0;

    while (prev < n && salinan[min(step, n) - 1].nomorKereta < cariNomor)
    {
        iterasi++;
        cout << "  Lompat ke indeks " << setw(2) << min(step, n) - 1
             << "  -> Nomor: " << salinan[min(step, n) - 1].nomorKereta
             << "  (lewati)\n";
        prev = step;
        step += (int)sqrt((double)n);
        if (prev >= n)
            break;
    }

    cout << "\n  [Linear dalam blok " << prev << " s/d " << min(step, n) - 1 << "]\n";
    bool ditemukan = false;
    for (int i = prev; i < min(step, n); i++)
    {
        iterasi++;
        cout << "  Cek indeks " << setw(2) << i
             << "  -> Nomor: " << salinan[i].nomorKereta;
        if (salinan[i].nomorKereta == cariNomor)
        {
            cout << GREEN << "  << DITEMUKAN! >>" << RESET;
            ditemukan = true;
        }
        cout << endl;
        if (ditemukan)
        {
            garisPemisah('-', 75);
            cout << GREEN << "\n  Hasil Pencarian (total iterasi: " << iterasi << "):" << RESET << endl;
            cetakHeaderTabel();
            cetakKereta(&salinan[i]);
            garisPemisah('-', 88);
            break;
        }
    }

    if (!ditemukan)
    {
        garisPemisah('-', 75);
        cout << RED << "\n  Nomor kereta " << cariNomor
             << " tidak ditemukan (total iterasi: " << iterasi << ")." << RESET << endl;
    }
}

void merge(Kereta *arr, int kiri, int tengah, int kanan)
{
    int n1 = tengah - kiri + 1;
    int n2 = kanan - tengah;

    Kereta *L = new Kereta[n1];
    Kereta *R = new Kereta[n2];

    for (int i = 0; i < n1; i++)
        *(L + i) = *(arr + kiri + i);
    for (int j = 0; j < n2; j++)
        *(R + j) = *(arr + tengah + 1 + j);

    int i = 0, j = 0, k = kiri;
    while (i < n1 && j < n2)
    {
        if (toLower((L + i)->namaKereta) <= toLower((R + j)->namaKereta))
            *(arr + k) = *(L + i++);
        else
            *(arr + k) = *(R + j++);
        k++;
    }
    while (i < n1)
    {
        *(arr + k) = *(L + i);
        i++;
        k++;
    }
    while (j < n2)
    {
        *(arr + k) = *(R + j);
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(Kereta *arr, int kiri, int kanan)
{
    if (kiri < kanan)
    {
        int tengah = kiri + (kanan - kiri) / 2;
        mergeSort(arr, kiri, tengah);
        mergeSort(arr, tengah + 1, kanan);
        merge(arr, kiri, tengah, kanan);
    }
}

void mergeSortWrapper(Kereta *&arr, int n)
{
    cetakHeader("MERGE SORT - URUTKAN NAMA KERETA (A-Z)");
    if (cekKosong(n))
        return;

    cout << YELLOW << "  Mengurutkan " << n << " kereta berdasarkan nama (A-Z)..." << RESET << endl;
    mergeSort(arr, 0, n - 1);
    cout << GREEN << "  Pengurutan selesai!" << RESET << endl;
    tampilSemuaKereta(arr, n);
}

void selectionSortHarga(Kereta *arr, int n)
{
    cetakHeader("SELECTION SORT - URUTKAN HARGA TIKET (TERMURAH)");
    if (cekKosong(n))
        return;

    cout << YELLOW << "  Proses Selection Sort (" << n << " kereta):" << RESET << endl;
    garisPemisah('-', 75);

    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if ((arr + j)->hargaTiket < (arr + minIdx)->hargaTiket)
                minIdx = j;

        if (minIdx != i)
        {
            cout << "  Tukar: [" << (arr + i)->namaKereta
                 << " Rp" << fixed << setprecision(0) << (arr + i)->hargaTiket
                 << "] <-> [" << (arr + minIdx)->namaKereta
                 << " Rp" << (arr + minIdx)->hargaTiket << "]\n";
            swapKereta(arr + i, arr + minIdx);
        }
    }

    garisPemisah('-', 75);
    cout << GREEN << "  Pengurutan selesai!" << RESET << endl;
    tampilSemuaKereta(arr, n);
}

void inisialisasiData()
{
    Kereta awal[] = {
        {101, "Pak Amba", "Surabaya", "Jakarta", "08:00", "16:30", 350000},
        {205, "Mas Rusdi", "Malang", "Jakarta", "17:00", "06:00", 420000},
        {312, "Mr.ironi", "Surabaya", "Bandung", "16:00", "04:30", 380000},
        {118, "Si Imut", "Yogyakarta", "Jakarta", "09:00", "15:00", 310000},
        {440, "Pria Solo", "Bandung", "Solo", "07:00", "13:00", 195000},
        {225, "Mas Gatot", "Bandung", "Surabaya", "18:00", "06:30", 265000},
        {330, "Ambatron", "Cirebon", "Jakarta", "06:00", "08:30", 120000},
        {511, "Sawitman", "Cilacap", "Surabaya", "10:00", "18:00", 230000},
    };
    int n = sizeof(awal) / sizeof(awal[0]);
    copy(awal, awal + n, dataKereta);
    jumlahKereta = n;
}

void tampilMenu()
{
    cout << endl;
    garisPemisah('=', 50);
    cout << BOLD << "    SISTEM MANAJEMEN KEBERANGKATAN KERETA API" << RESET << endl;
    garisPemisah('=', 50);
    cout << "  [1] Tampil Semua Jadwal Kereta\n"
         << "  [2] Tambah Data Kereta Baru\n"
         << "  [3] Cari Kereta (Linear Search - Rute)\n"
         << "  [4] Cari Kereta (Jump Search - Nomor)\n"
         << "  [5] Urutkan Nama Kereta (Merge Sort)\n"
         << "  [6] Urutkan Harga Tiket (Selection Sort)\n"
         << "  [0] Keluar\n";
    garisPemisah('-', 50);
    cout << "  Pilihan Anda: ";
}

int main()
{
    inisialisasiData();

    cout << BOLD << "\n  ================================================\n"
         << "    Selamat Datang di Sistem Informasi Kereta Api\n"
         << "  ================================================" << RESET << endl;

    int pilihan;
    do
    {
        tampilMenu();
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            tampilSemuaKereta(dataKereta, jumlahKereta);
            break;
        case 2:
            tambahKereta();
            break;
        case 3:
            linearSearchRute();
            break;
        case 4:
            jumpSearchNomor();
            break;
        case 5:
        {
            Kereta *ptrKereta = dataKereta;
            mergeSortWrapper(ptrKereta, jumlahKereta);
            break;
        }
        case 6:
            selectionSortHarga(dataKereta, jumlahKereta);
            break;
        case 0:
            cout << GREEN << "\n  Terima kasih. Sampai jumpa!" << RESET << "\n\n";
            break;
        default:
            cout << RED << "\n  Pilihan tidak valid!" << RESET << endl;
        }

    } while (pilihan != 0);

    return 0;
}