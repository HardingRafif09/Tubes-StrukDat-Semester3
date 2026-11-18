#ifndef SERVICE_H
#define SERVICE_H

#include <iostream>
#include <string>
using namespace std;

/* ===== ADT LIST SERVICE (Child List milik pelanggan) =====
   Singly Linked List standar: hanya punya pointer First.
   Penambahan elemen memakai INSERT FIRST.
   Satu pelanggan nanti punya satu ListService sendiri. */

struct infotypeService {
    string kode;        // contoh: S001
    string perangkat;   // contoh: Laptop, PC
    string keluhan;     // contoh: Layar mati
    int biaya;          // biaya service
    string status;      // Diterima / Diproses / Selesai
};

typedef struct elmService *adrService;

struct elmService {
    infotypeService info;
    adrService next;
};

struct ListService {
    adrService first;
};

/* ---------- Pembuatan ---------- */
void createListService(ListService &L);
/* I.S. : L sembarang
   F.S. : L.first = NULL (list kosong) */

adrService createElmService(infotypeService x);
/* I.S. : x terdefinisi
   F.S. : mengembalikan alamat elemen baru berisi x, next = NULL */

bool isEmptyService(ListService L);
/* mengembalikan true jika list kosong */

/* ---------- Operasi utama ---------- */
void insertService(ListService &L, infotypeService x, bool &berhasil);
/* I.S. : L terdefinisi (boleh kosong)
   F.S. : jika kode belum ada di L, x ditambah di AWAL list dan berhasil = true.
          Jika kode sudah ada, L tidak berubah dan berhasil = false */

adrService searchService(ListService L, string kode);
/* I.S. : L terdefinisi
   F.S. : mengembalikan alamat elemen berkode 'kode', atau NULL jika tidak ada */

void updateStatusService(ListService &L, string kode, string statusBaru, bool &berhasil);
/* I.S. : L terdefinisi
   F.S. : jika kode ditemukan, status elemennya diganti statusBaru dan
          berhasil = true. Jika tidak, L tidak berubah dan berhasil = false */

void deleteService(ListService &L, string kode, bool &berhasil);
/* I.S. : L terdefinisi
   F.S. : jika kode ditemukan, elemennya dihapus (awal, tengah, atau akhir)
          dan berhasil = true. Jika tidak, L tidak berubah dan berhasil = false */

void deleteAllService(ListService &L);
/* I.S. : L terdefinisi
   F.S. : semua elemen dihapus, L.first = NULL
          (dipakai saat pelanggan dihapus) */

void tampilService(ListService L);
/* I.S. : L terdefinisi
   F.S. : seluruh service tercetak dari awal sampai akhir,
          atau pesan "kosong" jika list kosong */

#endif
