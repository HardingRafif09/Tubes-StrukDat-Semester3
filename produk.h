
#ifndef PRODUK_H
#define PRODUK_H

#include <iostream>
#include <string>
using namespace std;

struct infotypeProduk {
    string kode;
    string nama;
    string jenis;
    int transaksi;
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

void createTree(BSTProduk &T);
adrProduk createNode(infotypeProduk x);
bool isEmpty(BSTProduk T);
void insertProduk(BSTProduk &T, infotypeProduk x, bool &berhasil);
adrProduk searchProduk(BSTProduk T, string kode);
void deleteProduk(BSTProduk &T, string kode, bool &berhasil);
void inOrder(adrProduk root);
void preOrder(adrProduk root);
void postOrder(adrProduk root);
string formatRupiah(int angka);
void tampilProduk(adrProduk p);

#endif
