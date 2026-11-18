#include "service.h"
#include "produk.h"   // dipakai untuk formatRupiah (titik ribuan)

void createListService(ListService &L) {
    /* I.S. : L sembarang
       F.S. : L.first = NULL */
    L.first = NULL;
}

adrService createElmService(infotypeService x) {
    /* I.S. : x terdefinisi
       F.S. : mengembalikan elemen baru berisi x */
    adrService p = new elmService;
    p->info = x;
    p->next = NULL;
    return p;
}

bool isEmptyService(ListService L) {
    return L.first == NULL;
}

adrService searchService(ListService L, string kode) {
    /* I.S. : L terdefinisi
       F.S. : mengembalikan alamat elemen berkode 'kode', atau NULL */
    adrService p = L.first;
    while (p != NULL && p->info.kode != kode) {
        p = p->next;
    }
    return p;
}

void insertService(ListService &L, infotypeService x, bool &berhasil) {
    /* I.S. : L terdefinisi
       F.S. : x ditambah di awal list jika kodenya belum ada */
    adrService baru;
    if (searchService(L, x.kode) != NULL) {
        berhasil = false;            // kode kembar
    } else {
        baru = createElmService(x);
        baru->next = L.first;        // insert first
        L.first = baru;
        berhasil = true;
    }
}

void updateStatusService(ListService &L, string kode, string statusBaru, bool &berhasil) {
    /* I.S. : L terdefinisi
       F.S. : status service berkode 'kode' diganti jika ada */
    adrService p = searchService(L, kode);
    if (p == NULL) {
        berhasil = false;
    } else {
        p->info.status = statusBaru;
        berhasil = true;
    }
}

void deleteService(ListService &L, string kode, bool &berhasil) {
    /* I.S. : L terdefinisi
       F.S. : elemen berkode 'kode' dihapus jika ada */
    adrService p = L.first;
    adrService prev = NULL;
    while (p != NULL && p->info.kode != kode) {
        prev = p;
        p = p->next;
    }
    if (p == NULL) {
        berhasil = false;            // tidak ditemukan
    } else {
        if (prev == NULL) {          // hapus elemen pertama
            L.first = p->next;
        } else {                     // hapus tengah atau akhir
            prev->next = p->next;
        }
        delete p;
        berhasil = true;
    }
}

void deleteAllService(ListService &L) {
    /* I.S. : L terdefinisi
       F.S. : semua elemen dihapus, L kosong */
    adrService p;
    while (L.first != NULL) {
        p = L.first;
        L.first = p->next;
        delete p;
    }
}

void tampilService(ListService L) {
    /* I.S. : L terdefinisi
       F.S. : semua service tercetak */
    adrService p = L.first;
    if (p == NULL) {
        cout << "Belum ada data service.\n";
    } else {
        while (p != NULL) {
            cout << p->info.kode << " | " << p->info.perangkat << " | "
                 << p->info.keluhan << " | Rp " << formatRupiah(p->info.biaya)
                 << " | " << p->info.status << endl;
            p = p->next;
        }
    }
}
