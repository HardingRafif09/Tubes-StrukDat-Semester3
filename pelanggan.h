#ifndef PELANGGAN_H
#define PELANGGAN_H

#include <iostream>
#include <string>
#include "produk.h"
using namespace std;

/* ===== ADT LIST PELANGGAN (Parent) + LIST PEMBELIAN (Child) =====
   Parent : Singly Linked List pelanggan, hanya punya First, INSERT LAST.
   Child  : Singly Linked List pembelian milik tiap pelanggan, INSERT FIRST.
   Child hanya menyimpan kode produk; data produk lengkap ada di BST. */

struct infotypePelanggan {
    string kode;    // contoh: C001
    string nama;    // contoh: Andi
};

/* ---------- CHILD LIST PEMBELIAN ---------- */

struct infotypePembelian {
    string kodeProduk;   // acuan ke produk di BST
    int jumlah;
    int hargaBeli;       // harga produk saat dibeli
};

typedef struct elmPembelian *adrPembelian;

struct elmPembelian {
    infotypePembelian info;
    adrPembelian next;
};

struct ListPembelian {
    adrPembelian first;
};

/* ---------- PARENT LIST PELANGGAN ---------- */

typedef struct elmPelanggan *adrPelanggan;

struct elmPelanggan {
    infotypePelanggan info;
    adrPelanggan next;
    ListPembelian pembelian;   // child list milik pelanggan ini
};

struct ListPelanggan {
    adrPelanggan first;
};

/* ================= OPERASI PELANGGAN ================= */

void createList(ListPelanggan &L);
/* I.S. : L sembarang
   F.S. : L.first = NULL (list kosong) */

adrPelanggan createElmPelanggan(infotypePelanggan x);
/* I.S. : x terdefinisi
   F.S. : mengembalikan elemen baru berisi x, next = NULL,
          dan daftar pembelian kosong */

bool isEmptyPelanggan(ListPelanggan L);
/* mengembalikan true jika list kosong */

adrPelanggan searchPelanggan(ListPelanggan L, string kode);
/* I.S. : L terdefinisi
   F.S. : mengembalikan alamat elemen berkode 'kode', atau NULL */

void insertPelanggan(ListPelanggan &L, infotypePelanggan x, bool &berhasil);
/* I.S. : L terdefinisi (boleh kosong)
   F.S. : jika kode belum ada, x ditambah di AKHIR list dan berhasil = true.
          Jika kode sudah ada, L tidak berubah dan berhasil = false */

void deletePelanggan(ListPelanggan &L, string kode, bool &berhasil);
/* I.S. : L terdefinisi
   F.S. : jika kode ditemukan, elemen dan seluruh daftar pembeliannya dihapus,
          berhasil = true. Jika tidak, L tidak berubah dan berhasil = false */

void tampilPelanggan(ListPelanggan L);
/* I.S. : L terdefinisi
   F.S. : seluruh pelanggan tercetak, atau pesan "kosong" jika list kosong */

/* ================= OPERASI PEMBELIAN ================= */

void createListPembelian(ListPembelian &L);
/* I.S. : L sembarang
   F.S. : L.first = NULL (list kosong) */

adrPembelian createElmPembelian(infotypePembelian x);
/* I.S. : x terdefinisi
   F.S. : mengembalikan elemen baru berisi x, next = NULL */

void insertPembelian(ListPembelian &L, infotypePembelian x);
/* I.S. : L terdefinisi (boleh kosong)
   F.S. : x ditambah di AWAL list (insert first) */

void tampilPembelian(ListPembelian L, BSTProduk T);
/* I.S. : L dan T terdefinisi
   F.S. : seluruh pembelian tercetak beserta subtotal dan total.
          Nama dan jenis produk dicari dari T lewat kode produk */

void deleteAllPembelian(ListPembelian &L);
/* I.S. : L terdefinisi
   F.S. : semua elemen dihapus, L.first = NULL */

#endif
