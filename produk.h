#ifndef PRODUK_H
#define PRODUK_H

#include <iostream>
#include <string>
using namespace std;

/* ===== ADT BST PRODUK (Master Data) =====
   Kunci pembanding : kode produk (contoh: P001)
   Satu node memiliki maksimal dua child: left dan right */

struct infotypeProduk {
    string kode;
    string nama;
    string jenis;
    int transaksi;   // jumlah transaksi pembelian produk ini
    int harga;
    int stok;
};

typedef struct nodeProduk *adrProduk;

struct nodeProduk {
    infotypeProduk info;
    adrProduk left;
    adrProduk right;
};

struct BSTProduk {
    adrProduk root;
};

/* ---------- Pembuatan ---------- */
void createTree(BSTProduk &T);
/* I.S. : T sembarang
   F.S. : T.root = NULL (tree kosong) */

adrProduk createNode(infotypeProduk x);
/* I.S. : x terdefinisi
   F.S. : mengembalikan alamat node baru berisi x, left dan right = NULL */

bool isEmpty(BSTProduk T);
/* mengembalikan true jika tree kosong */

/* ---------- Operasi utama ---------- */
void insertProduk(BSTProduk &T, infotypeProduk x, bool &berhasil);
/* I.S. : T terdefinisi (boleh kosong)
   F.S. : jika kode x belum ada, x masuk ke BST dan berhasil = true.
          Jika kode sudah ada, T tidak berubah dan berhasil = false */

adrProduk searchProduk(BSTProduk T, string kode);
/* I.S. : T terdefinisi
   F.S. : mengembalikan alamat node berkode 'kode', atau NULL */

void deleteProduk(BSTProduk &T, string kode, bool &berhasil);
/* I.S. : T terdefinisi
   F.S. : jika kode ditemukan, node dihapus dan berhasil = true.
          Jika tidak, T tidak berubah dan berhasil = false */

/* ---------- Traversal dan tampilan ---------- */
void inOrder(adrProduk root);
/* I.S. : root terdefinisi (boleh NULL)
   F.S. : produk tercetak urut kiri - akar - kanan */

void preOrder(adrProduk root);
/* I.S. : root terdefinisi (boleh NULL)
   F.S. : produk tercetak urut akar - kiri - kanan */

void postOrder(adrProduk root);
/* I.S. : root terdefinisi (boleh NULL)
   F.S. : produk tercetak urut kiri - kanan - akar */

string formatRupiah(int angka);
/* I.S. : angka terdefinisi (tidak negatif)
   F.S. : mengembalikan angka dengan titik pemisah ribuan,
          contoh: 1500000 menjadi "1.500.000" */

void tampilProduk(adrProduk p);
/* I.S. : p tidak NULL
   F.S. : satu baris data produk tercetak di layar */

#endif
