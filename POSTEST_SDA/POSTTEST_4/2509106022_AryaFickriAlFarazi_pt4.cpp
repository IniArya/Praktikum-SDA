#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

const int MAX_KERETA = 50;

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

struct Pemesanan
{
    int idPemesanan;
    int nomorKereta;
    string namaPenumpang;
    string namaKereta;
    string asal;
    string tujuan;
    string status;
    double hargaTiket;
    Pemesanan *next;
};

struct Queue
{
    Pemesanan *front;
    Pemesanan *rear;
    int ukuran;
};

struct Stack
{
    Pemesanan *top;
    int ukuran;
};

Kereta dataKereta[MAX_KERETA];
int jumlahKereta = 0;
Queue antrianTiket;
Stack riwayatTransaksi;
int idCounter = 1000;

string toLower(const string &s)
{
    string h = s;
    for (int i = 0; i < (int)h.size(); i++)
        h[i] = tolower(h[i]);
    return h;
}

void garis() { cout << string(70, '-') << "\n"; }
void header(const string &judul) { cout << "\n=== " << judul << " ===\n"; }

void cetakKereta(const Kereta *k)
{
    cout << left
         << setw(6) << k->nomorKereta
         << setw(18) << k->namaKereta
         << setw(13) << k->asal
         << setw(13) << k->tujuan
         << setw(8) << k->jamBerangkat
         << setw(8) << k->jamTiba
         << "Rp " << fixed << setprecision(0) << k->hargaTiket << "\n";
}

void cetakHeaderKereta()
{
    garis();
    cout << left
         << setw(6) << "No."
         << setw(18) << "Nama Kereta"
         << setw(13) << "Asal"
         << setw(13) << "Tujuan"
         << setw(8) << "Brgkt"
         << setw(8) << "Tiba"
         << "Harga\n";
    garis();
}

void tampilSemuaKereta(Kereta *arr, int n)
{
    header("JADWAL KERETA API");
    if (n == 0)
    {
        cout << "Belum ada data kereta.\n";
        return;
    }
    cetakHeaderKereta();
    for (int i = 0; i < n; i++)
        cetakKereta(arr + i);
    garis();
    cout << "Total: " << n << " kereta\n";
}

void tambahKereta()
{
    header("TAMBAH KERETA");
    if (jumlahKereta >= MAX_KERETA)
    {
        cout << "Data penuh! Maksimal " << MAX_KERETA << " kereta.\n";
        return;
    }
    Kereta *k = &dataKereta[jumlahKereta];
    cout << "Nomor Kereta     : ";
    cin >> k->nomorKereta;
    cin.ignore();
    cout << "Nama Kereta      : ";
    getline(cin, k->namaKereta);
    cout << "Asal             : ";
    getline(cin, k->asal);
    cout << "Tujuan           : ";
    getline(cin, k->tujuan);
    cout << "Jam Berangkat    : ";
    getline(cin, k->jamBerangkat);
    cout << "Jam Tiba         : ";
    getline(cin, k->jamTiba);
    cout << "Harga Tiket (Rp) : ";
    cin >> k->hargaTiket;
    jumlahKereta++;
    cout << "Kereta berhasil ditambahkan.\n";
}

void swapKereta(Kereta *a, Kereta *b)
{
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void linearSearchRute()
{
    header("RUTE");
    string cariAsal, cariTujuan;
    cout << "Kota Asal   : ";
    getline(cin, cariAsal);
    cout << "Kota Tujuan : ";
    getline(cin, cariTujuan);

    cout << "\nProses pencarian:\n";
    bool ditemukan = false;
    int jumlahHasil = 0;

    for (int i = 0; i < jumlahKereta; i++)
    {
        Kereta *p = dataKereta + i;
        cout << "  [" << i + 1 << "] " << p->namaKereta
             << " (" << p->asal << "->" << p->tujuan << ")";
        if (toLower(p->asal) == toLower(cariAsal) &&
            toLower(p->tujuan) == toLower(cariTujuan))
        {
            cout << " << COCOK >>";
            ditemukan = true;
            jumlahHasil++;
        }
        cout << "\n";
    }

    if (ditemukan)
    {
        cout << "\nHasil (" << jumlahHasil << " kereta):\n";
        cetakHeaderKereta();
        for (int i = 0; i < jumlahKereta; i++)
        {
            Kereta *p = dataKereta + i;
            if (toLower(p->asal) == toLower(cariAsal) &&
                toLower(p->tujuan) == toLower(cariTujuan))
                cetakKereta(p);
        }
        garis();
    }
    else
    {
        cout << "Rute tidak ditemukan.\n";
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
    header("NOMOR KERETA");
    if (jumlahKereta == 0)
    {
        cout << "Belum ada data kereta.\n";
        return;
    }

    int cariNomor;
    cout << "Nomor Kereta : ";
    cin >> cariNomor;
    cin.ignore();

    Kereta salinan[MAX_KERETA];
    for (int i = 0; i < jumlahKereta; i++)
        *(salinan + i) = *(dataKereta + i);
    sortByNomor(salinan, jumlahKereta);

    int n = jumlahKereta;
    int step = (int)sqrt((double)n);
    int prev = 0;
    int iterasi = 0;

    cout << "\nProses jump (step=" << step << "):\n";
    while (prev < n && salinan[min(step, n) - 1].nomorKereta < cariNomor)
    {
        iterasi++;
        cout << "  Lompat ke [" << min(step, n) - 1 << "] nomor="
             << salinan[min(step, n) - 1].nomorKereta << "\n";
        prev = step;
        step += (int)sqrt((double)n);
        if (prev >= n)
            break;
    }

    cout << "Linear dalam blok [" << prev << ".." << min(step, n) - 1 << "]:\n";
    bool ditemukan = false;
    for (int i = prev; i < min(step, n); i++)
    {
        iterasi++;
        cout << "  Cek [" << i << "] nomor=" << salinan[i].nomorKereta;
        if (salinan[i].nomorKereta == cariNomor)
        {
            cout << " << DITEMUKAN >>";
            ditemukan = true;
        }
        cout << "\n";
        if (ditemukan)
        {
            cout << "\nHasil (iterasi=" << iterasi << "):\n";
            cetakHeaderKereta();
            cetakKereta(&salinan[i]);
            garis();
            break;
        }
    }
    if (!ditemukan)
        cout << "Nomor " << cariNomor << " tidak ditemukan (iterasi=" << iterasi << ").\n";
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

void jalankanMergeSort()
{
    header("MERGE SORT - NAMA KERETA (A-Z)");
    if (jumlahKereta == 0)
    {
        cout << "Belum ada data kereta.\n";
        return;
    }
    mergeSort(dataKereta, 0, jumlahKereta - 1);
    cout << "Pengurutan selesai.\n";
    tampilSemuaKereta(dataKereta, jumlahKereta);
}

void selectionSortHarga(Kereta *arr, int n)
{
    header("SELECTION SORT - HARGA TIKET");
    if (n == 0)
    {
        cout << "Belum ada data kereta.\n";
        return;
    }
    cout << "Proses swap:\n";
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if ((arr + j)->hargaTiket < (arr + minIdx)->hargaTiket)
                minIdx = j;
        if (minIdx != i)
        {
            cout << "  Tukar: " << (arr + i)->namaKereta
                 << " <-> " << (arr + minIdx)->namaKereta << "\n";
            swapKereta(arr + i, arr + minIdx);
        }
    }
    cout << "Pengurutan selesai.\n";
    tampilSemuaKereta(arr, n);
}

void initQueue(Queue *q)
{
    q->front = NULL;
    q->rear = NULL;
    q->ukuran = 0;
}

bool isQueueEmpty(const Queue *q) { return q->front == NULL; }

bool enqueue(Queue *q, const Pemesanan &p)
{
    Pemesanan *node = new Pemesanan;
    *node = p;
    node->next = NULL;

    if (isQueueEmpty(q))
    {
        q->front = node;
        q->rear = node;
    }
    else
    {
        q->rear->next = node;
        q->rear = node;
    }
    q->ukuran++;
    return true;
}

bool dequeue(Queue *q, Pemesanan *hasil)
{
    if (isQueueEmpty(q))
        return false;

    Pemesanan *hapus = q->front;
    *hasil = *hapus;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    delete hapus;
    q->ukuran--;
    return true;
}

bool peekQueue(const Queue *q, Pemesanan *hasil)
{
    if (isQueueEmpty(q))
        return false;
    *hasil = *(q->front);
    return true;
}

void cetakBarisPemesanan(const Pemesanan *p, int no)
{
    cout << left
         << setw(4) << no
         << setw(8) << p->idPemesanan
         << setw(20) << p->namaPenumpang
         << setw(6) << p->nomorKereta
         << setw(15) << p->namaKereta
         << p->asal << "->" << p->tujuan
         << "  Rp" << fixed << setprecision(0) << p->hargaTiket << "\n";
}

void tampilSemuaAntrian(const Queue *q)
{
    header("ANTRIAN TIKET");
    if (isQueueEmpty(q))
    {
        cout << "Antrian kosong.\n";
        return;
    }
    cout << "Isi antrian (" << q->ukuran << ") - front ke rear:\n";
    garis();
    cout << left << setw(4) << "No." << setw(8) << "ID" << setw(20) << "Penumpang"
         << setw(6) << "No.KA" << setw(15) << "Kereta" << "Rute & Harga\n";
    garis();

    Pemesanan *curr = q->front;
    int no = 1;
    while (curr != NULL)
    {
        cetakBarisPemesanan(curr, no++);
        curr = curr->next;
    }
    garis();
}

void beliTiket(Queue *q)
{
    header("BELI TIKET");
    tampilSemuaKereta(dataKereta, jumlahKereta);
    if (jumlahKereta == 0)
        return;

    Pemesanan p;
    p.next = NULL;
    cout << "\nNama Penumpang           : ";
    getline(cin, p.namaPenumpang);
    cout << "Nomor Kereta yang dipilih: ";
    cin >> p.nomorKereta;
    cin.ignore();

    bool ketemu = false;
    for (int i = 0; i < jumlahKereta; i++)
    {
        Kereta *k = dataKereta + i;
        if (k->nomorKereta == p.nomorKereta)
        {
            p.namaKereta = k->namaKereta;
            p.asal = k->asal;
            p.tujuan = k->tujuan;
            p.hargaTiket = k->hargaTiket;
            p.status = "ANTRIAN";
            ketemu = true;
            break;
        }
    }
    if (!ketemu)
    {
        cout << "Nomor kereta tidak ditemukan.\n";
        return;
    }

    p.idPemesanan = idCounter++;
    enqueue(q, p);
    cout << "Berhasil masuk antrian!\n";
    cout << "  ID=" << p.idPemesanan << "  " << p.namaPenumpang
         << "  [" << p.nomorKereta << "] " << p.namaKereta
         << "  " << p.asal << "->" << p.tujuan
         << "  Rp" << fixed << setprecision(0) << p.hargaTiket << "\n";
    cout << "  Posisi antrian ke-" << q->ukuran << "\n";
}

void initStack(Stack *s)
{
    s->top = NULL;
    s->ukuran = 0;
}

bool isStackEmpty(const Stack *s) { return s->top == NULL; }

bool push(Stack *s, const Pemesanan &p)
{
    Pemesanan *node = new Pemesanan;
    *node = p;
    node->next = s->top;
    s->top = node;
    s->ukuran++;
    return true;
}

bool pop(Stack *s, Pemesanan *hasil)
{
    if (isStackEmpty(s))
        return false;

    Pemesanan *hapus = s->top;
    *hasil = *hapus;
    s->top = s->top->next;

    delete hapus;
    s->ukuran--;
    return true;
}

bool peekStack(const Stack *s, Pemesanan *hasil)
{
    if (isStackEmpty(s))
        return false;
    *hasil = *(s->top);
    return true;
}

void tampilSemuaRiwayat(const Stack *s)
{
    header("RIWAYAT TRANSAKSI");
    if (isStackEmpty(s))
    {
        cout << "Riwayat kosong.\n";
        return;
    }
    cout << "Total: " << s->ukuran << " transaksi (terbaru di atas):\n";
    garis();
    cout << left << setw(4) << "No." << setw(8) << "ID" << setw(20) << "Penumpang"
         << setw(18) << "Kereta" << setw(22) << "Rute" << "Status\n";
    garis();

    Pemesanan *curr = s->top;
    int urutan = 1;
    while (curr != NULL)
    {
        cout << left
             << setw(4) << urutan++
             << setw(8) << curr->idPemesanan
             << setw(20) << curr->namaPenumpang
             << setw(18) << curr->namaKereta
             << setw(22) << (curr->asal + "->" + curr->tujuan)
             << curr->status << "\n";
        curr = curr->next;
    }
    garis();
}

void prosesTiket(Queue *q, Stack *s)
{
    header("PROSES TIKET");
    if (isQueueEmpty(q))
    {
        cout << "UNDERFLOW! Antrian kosong.\n";
        return;
    }

    Pemesanan diproses;
    dequeue(q, &diproses);
    diproses.status = "SELESAI";

    cout << "Tiket diproses:\n";
    cout << "  ID        : " << diproses.idPemesanan << "\n";
    cout << "  Penumpang : " << diproses.namaPenumpang << "\n";
    cout << "  Kereta    : [" << diproses.nomorKereta << "] " << diproses.namaKereta << "\n";
    cout << "  Rute      : " << diproses.asal << " -> " << diproses.tujuan << "\n";
    cout << "  Harga     : Rp" << fixed << setprecision(0) << diproses.hargaTiket << "\n";

    push(s, diproses);
    cout << "Dicatat ke riwayat. Sisa antrian: " << q->ukuran << "\n";
}

void batalkanTransaksiTerakhir(Stack *s)
{
    header("BATALKAN TRANSAKSI");
    if (isStackEmpty(s))
    {
        cout << "UNDERFLOW! Riwayat kosong.\n";
        return;
    }

    Pemesanan batal;
    pop(s, &batal);
    batal.status = "DIBATALKAN";

    cout << "Transaksi dibatalkan:\n";
    cout << "  ID        : " << batal.idPemesanan << "\n";
    cout << "  Penumpang : " << batal.namaPenumpang << "\n";
    cout << "  Kereta    : " << batal.namaKereta << "\n";
    cout << "  Rute      : " << batal.asal << " -> " << batal.tujuan << "\n";
    cout << "  Status    : DIBATALKAN\n";
    cout << "Sisa riwayat: " << s->ukuran << " transaksi\n";
}

void peekSemuaData(const Queue *q, const Stack *s)
{
    header("PEEK ANTRIAN & RIWAYAT");

    cout << "[Queue - Penumpang Terdepan]\n";
    if (isQueueEmpty(q))
    {
        cout << "  Antrian kosong.\n";
    }
    else
    {
        Pemesanan f;
        peekQueue(q, &f);
        cout << "  ID=" << f.idPemesanan << "  " << f.namaPenumpang
             << "  [" << f.nomorKereta << "] " << f.namaKereta
             << "  " << f.asal << "->" << f.tujuan
             << "  (total antrian: " << q->ukuran << ")\n";
    }

    cout << "\n[Stack - Transaksi Terakhir]\n";
    if (isStackEmpty(s))
    {
        cout << "  Riwayat kosong.\n";
    }
    else
    {
        Pemesanan t;
        peekStack(s, &t);
        cout << "  ID=" << t.idPemesanan << "  " << t.namaPenumpang
             << "  " << t.namaKereta
             << "  " << t.asal << "->" << t.tujuan
             << "  Status=" << t.status
             << "  (total riwayat: " << s->ukuran << ")\n";
    }
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
    for (int i = 0; i < n; i++)
        *(dataKereta + i) = *(awal + i);
    jumlahKereta = n;
}

void tampilMenu()
{
    cout << "\n=== SISTEM KERETA API ===\n"
         << "-- Data Kereta --\n"
         << "  1. Tampil Semua Kereta\n"
         << "  2. Tambah Kereta\n"
         << "  3. Cari Rute\n"
         << "  4. Cari Nomor\n"
         << "  5. Urutkan Nama\n"
         << "  6. Urutkan Harga\n"
         << "-- Antrian Tiket (Queue) --\n"
         << "  7. Beli Tiket\n"
         << "  8. Proses Tiket\n"
         << "  9. Tampil Antrian\n"
         << "-- Riwayat Transaksi (Stack) --\n"
         << "  10. Tampil Riwayat\n"
         << "  11. Batalkan Transaksi Terakhir\n"
         << "  12. Peek Antrian & Riwayat\n"
         << "  0. Keluar\n"
         << "Pilihan: ";
}

int main()
{
    inisialisasiData();
    initQueue(&antrianTiket);
    initStack(&riwayatTransaksi);
    cout << "Selamat Datang - Sistem Informasi Kereta Api\n";

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
            jalankanMergeSort();
            break;
        case 6:
            selectionSortHarga(dataKereta, jumlahKereta);
            break;
        case 7:
            beliTiket(&antrianTiket);
            break;
        case 8:
            prosesTiket(&antrianTiket, &riwayatTransaksi);
            break;
        case 9:
            tampilSemuaAntrian(&antrianTiket);
            break;
        case 10:
            tampilSemuaRiwayat(&riwayatTransaksi);
            break;
        case 11:
            batalkanTransaksiTerakhir(&riwayatTransaksi);
            break;
        case 12:
            peekSemuaData(&antrianTiket, &riwayatTransaksi);
            break;
        case 0:
            cout << "Sampai jumpa!\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    return 0;
}