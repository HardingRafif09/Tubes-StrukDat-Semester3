#include "pelanggan.h"

/* ================= PEMBELIAN ================= */

void createListPembelian(ListPembelian &L) {
    L.first = NULL;
}

adrPembelian createElmPembelian(infotypePembelian x) {
    adrPembelian p = new elmPembelian;
    p->info = x;
    p->next = NULL;
    return p;
}

void insertPembelian(ListPembelian &L, infotypePembelian x) {
    adrPembelian baru = createElmPembelian(x);

    baru->next = L.first;
    L.first = baru;
}

void tampilPembelian(ListPembelian L, BSTProduk T) {
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
                 << formatRupiah(
                    p->info.hargaBeli * p->info.jumlah)
                 << endl;

            total += p->info.hargaBeli * p->info.jumlah;

            p = p->next;
            no++;
        }

        cout << "Total pembelian: Rp "
             << formatRupiah(total) << endl;
    }
}

void deleteAllPembelian(ListPembelian &L) {
    adrPembelian p;

    while (L.first != NULL) {
        p = L.first;
        L.first = p->next;
        delete p;
    }
}

/* ================= PELANGGAN ================= */

void createList(ListPelanggan &L) {
    L.first = NULL;
}

adrPelanggan createElmPelanggan(infotypePelanggan x) {
    adrPelanggan p = new elmPelanggan;

    p->info = x;
    p->next = NULL;

    createListPembelian(p->pembelian);

    return p;
}

bool isEmptyPelanggan(ListPelanggan L) {
    return L.first == NULL;
}

adrPelanggan searchPelanggan(ListPelanggan L, string kode) {
    adrPelanggan p = L.first;

    while (p != NULL && p->info.kode != kode) {
        p = p->next;
    }

    return p;
}

void insertPelanggan(ListPelanggan &L,
                     infotypePelanggan x,
                     bool &berhasil) {
    adrPelanggan baru, last;

    if (searchPelanggan(L, x.kode) != NULL) {
        berhasil = false;
    } else {
        baru = createElmPelanggan(x);

        if (L.first == NULL) {
            L.first = baru;
        } else {
            last = L.first;

            while (last->next != NULL) {
                last = last->next;
            }

            last->next = baru;
        }

        berhasil = true;
    }
}

void deletePelanggan(ListPelanggan &L,
                     string kode,
                     bool &berhasil) {
    adrPelanggan p = L.first;
    adrPelanggan prev = NULL;

    while (p != NULL && p->info.kode != kode) {
        prev = p;
        p = p->next;
    }

    if (p == NULL) {
        berhasil = false;
    } else {
        if (prev == NULL) {
            L.first = p->next;
        } else {
            prev->next = p->next;
        }

        deleteAllPembelian(p->pembelian);
        delete p;

        berhasil = true;
    }
}

void tampilPelanggan(ListPelanggan L) {
    adrPelanggan p = L.first;

    if (p == NULL) {
        cout << "Data pelanggan masih kosong.\n";
    } else {
        while (p != NULL) {
            cout << p->info.kode << " | "
                 << p->info.nama << endl;

            p = p->next;
        }
    }
}