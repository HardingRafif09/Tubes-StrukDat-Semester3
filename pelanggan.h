#ifndef PELANGGAN_H
#define PELANGGAN_H

#include <iostream>
#include <string>
#include "produk.h"
using namespace std;

struct infotypePelanggan {
    string kode;
    string nama;
};

/* CHILD LIST PEMBELIAN */

struct infotypePembelian {
    string kodeProduk;
    int jumlah;
    int hargaBeli;
};

typedef struct elmPembelian *adrPembelian;

struct elmPembelian {
    infotypePembelian info;
    adrPembelian next;
};

struct ListPembelian {
    adrPembelian first;
};

/* PARENT LIST PELANGGAN */

typedef struct elmPelanggan *adrPelanggan;

struct elmPelanggan {
    infotypePelanggan info;
    adrPelanggan next;
    ListPembelian pembelian;
};

struct ListPelanggan {
    adrPelanggan first;
};

/* OPERASI PELANGGAN */

void createList(ListPelanggan &L);
adrPelanggan createElmPelanggan(infotypePelanggan x);
bool isEmptyPelanggan(ListPelanggan L);
adrPelanggan searchPelanggan(ListPelanggan L, string kode);
void insertPelanggan(ListPelanggan &L, infotypePelanggan x, bool &berhasil);
void deletePelanggan(ListPelanggan &L, string kode, bool &berhasil);
void tampilPelanggan(ListPelanggan L);

/* OPERASI PEMBELIAN */

void createListPembelian(ListPembelian &L);
adrPembelian createElmPembelian(infotypePembelian x);
void insertPembelian(ListPembelian &L, infotypePembelian x);
void tampilPembelian(ListPembelian L, BSTProduk T);
void deleteAllPembelian(ListPembelian &L);

#endif