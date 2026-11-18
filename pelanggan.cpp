#include "pelanggan.h"

/* ================= PEMBELIAN (CHILD LIST) ================= */

void createListPembelian(ListPembelian &L) {
    /* I.S. : L sembarang
       F.S. : L.first = NULL */
    L.first = NULL;
}

adrPembelian createElmPembelian(infotypePembelian x) {
    /* I.S. : x terdefinisi
       F.S. : mengembalikan elemen baru berisi x */
    adrPembelian p = new elmPembelian;

    p->info = x;
    p->next = NULL;

    return p;
}

void insertPembelian(ListPembelian &L, infotypePembelian x) {
    /* I.S. : L terdefinisi
       F.S. : x ditambah di awal list (insert first) */
    adrPembelian baru = createElmPembelian(x);

    baru->next = L.first;
    L.first = baru;
}

void tampilPembelian(ListPembelian L, BSTProduk T) {
    /* I.S. : L dan T terdefinisi
       F.S. : pembelian tercetak beserta subtotal dan total */
    adrPembelian p = L.first;
    adrProduk produk;
    int no = 1;
    int total = 0;

    if (p == NULL) {
        cout << "Belum ada produk yang dibeli.\n";
    } else {
        while (p != NULL) {
            produk = searchProduk(T, p->info.kodeProduk);

            cout << no << ". ";

            if (produk != NULL) {
                cout << produk->info.nama
                     << " | Jenis: " << produk->info.jenis;
            } else {
                cout << "Kode produk: " << p->info.kodeProduk;
            }

            cout << endl;
            cout << "   Jumlah: " << p->info.jumlah << endl;
            cout << "   Harga: Rp "
                 << formatRupiah(p->info.hargaBeli) << endl;
            cout << "   Subtotal: Rp "
                 << formatRupiah(p->info.hargaBeli * p->info.jumlah)
                 << endl;

            total += p->info.hargaBeli * p->info.jumlah;

            p = p->next;
            no++;
        }

        cout << "Total pembelian: Rp " << formatRupiah(total) << endl;
    }
}

void deleteAllPembelian(ListPembelian &L) {
    /* I.S. : L terdefinisi
       F.S. : semua elemen dihapus, L kosong */
    adrPembelian p;

    while (L.first != NULL) {
        p = L.first;
        L.first = p->next;
        delete p;
    }
}

/* ================= PELANGGAN (PARENT LIST) ================= */

void createList(ListPelanggan &L) {
    /* I.S. : L sembarang
       F.S. : L.first = NULL */
    L.first = NULL;
}

adrPelanggan createElmPelanggan(infotypePelanggan x) {
    /* I.S. : x terdefinisi
       F.S. : mengembalikan elemen baru dengan daftar pembelian kosong */
    adrPelanggan p = new elmPelanggan;

    p->info = x;
    p->next = NULL;
    createListPembelian(p->pembelian);

    return p;
}

bool isEmptyPelanggan(ListPelanggan L) {
    /* I.S. : L terdefinisi
       F.S. : true jika list kosong */
    return L.first == NULL;
}

adrPelanggan searchPelanggan(ListPelanggan L, string kode) {
    /* I.S. : L terdefinisi
       F.S. : mengembalikan alamat elemen berkode 'kode', atau NULL */
    adrPelanggan p = L.first;

    while (p != NULL && p->info.kode != kode) {
        p = p->next;
    }

    return p;
}

void insertPelanggan(ListPelanggan &L, infotypePelanggan x, bool &berhasil) {
    /* I.S. : L terdefinisi
       F.S. : x ditambah di akhir list jika kodenya belum ada */
    adrPelanggan baru, last;

    if (searchPelanggan(L, x.kode) != NULL) {
        berhasil = false;                 // kode kembar
    } else {
        baru = createElmPelanggan(x);

        if (L.first == NULL) {            // list kosong
            L.first = baru;
        } else {                          // cari elemen terakhir
            last = L.first;

            while (last->next != NULL) {
                last = last->next;
            }

            last->next = baru;
        }

        berhasil = true;
    }
}

void deletePelanggan(ListPelanggan &L, string kode, bool &berhasil) {
    /* I.S. : L terdefinisi
       F.S. : elemen berkode 'kode' beserta pembeliannya dihapus jika ada */
    adrPelanggan p = L.first;
    adrPelanggan prev = NULL;

    while (p != NULL && p->info.kode != kode) {
        prev = p;
        p = p->next;
    }

    if (p == NULL) {
        berhasil = false;                 // tidak ditemukan
    } else {
        if (prev == NULL) {               // hapus elemen pertama
            L.first = p->next;
        } else {                          // hapus tengah atau akhir
            prev->next = p->next;
        }

        deleteAllPembelian(p->pembelian);
        delete p;

        berhasil = true;
    }
}

void tampilPelanggan(ListPelanggan L) {
    /* I.S. : L terdefinisi
       F.S. : semua pelanggan tercetak */
    adrPelanggan p = L.first;

    if (p == NULL) {
        cout << "Data pelanggan masih kosong.\n";
    } else {
        while (p != NULL) {
            cout << p->info.kode << " | " << p->info.nama << endl;
            p = p->next;
        }
    }
}
