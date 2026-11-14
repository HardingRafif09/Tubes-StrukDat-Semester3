#include "produk.h"
#include "pelanggan.h"

/* ================= DATA AWAL ================= */

void isiDataProduk(BSTProduk &T) {
    bool ok;

    infotypeProduk d[5] = {
        {"P003", "RAM 16GB", "Komponen", 0, 650000, 20},
        {"P001", "Keyboard Mechanical", "Aksesoris", 0, 450000, 15},
        {"P005", "Monitor 24 Inch", "Display", 0, 1500000, 8},
        {"P002", "Mouse Gaming", "Aksesoris", 0, 250000, 25},
        {"P004", "SSD 1TB", "Komponen", 0, 1200000, 12}
    };

    for (int i = 0; i < 5; i++) {
        insertProduk(T, d[i], ok);
    }
}

void isiDataPelanggan(ListPelanggan &L) {
    bool ok;

    infotypePelanggan d[3] = {
        {"C001", "Andi"},
        {"C002", "Budi"},
        {"C003", "Caca"}
    };

    for (int i = 0; i < 3; i++) {
        insertPelanggan(L, d[i], ok);
    }
}

/* ================= MENU PRODUK ================= */

void menuTambahProduk(BSTProduk &T) {
    infotypeProduk x;
    bool ok;

    cout << "Kode produk  : ";
    getline(cin, x.kode);

    cout << "Nama produk  : ";
    getline(cin, x.nama);

    cout << "Jenis produk : ";
    getline(cin, x.jenis);

    x.transaksi = 0;

    cout << "Harga        : ";
    cin >> x.harga;

    cout << "Stok         : ";
    cin >> x.stok;
    cin.ignore(1000, '\n');

    if (x.harga < 0 || x.stok < 0) {
        cout << "Harga atau stok tidak valid.\n";
    } else {
        insertProduk(T, x, ok);

        if (ok) {
            cout << "Produk berhasil ditambahkan.\n";
        } else {
            cout << "Kode produk sudah ada.\n";
        }
    }
}

void menuCariProduk(BSTProduk T) {
    string kode;

    cout << "Kode produk : ";
    getline(cin, kode);

    adrProduk p = searchProduk(T, kode);

    if (p != NULL) {
        tampilProduk(p);
    } else {
        cout << "Produk tidak ditemukan.\n";
    }
}

void menuHapusProduk(BSTProduk &T) {
    string kode;
    bool ok;

    cout << "Kode produk : ";
    getline(cin, kode);

    adrProduk p = searchProduk(T, kode);

    if (p == NULL) {
        cout << "Produk tidak ditemukan.\n";
    } else if (p->info.transaksi > 0) {
        cout << "Produk sudah memiliki riwayat pembelian.\n";
    } else {
        deleteProduk(T, kode, ok);
        cout << "Produk berhasil dihapus.\n";
    }
}

void menuTampilProduk(BSTProduk T) {
    int pilih;

    if (isEmpty(T)) {
        cout << "Data produk masih kosong.\n";
    } else {
        cout << "1. InOrder\n";
        cout << "2. PreOrder\n";
        cout << "3. PostOrder\n";
        cout << "Pilih : ";

        cin >> pilih;
        cin.ignore(1000, '\n');

        if (pilih == 1) {
            inOrder(T.root);
        } else if (pilih == 2) {
            preOrder(T.root);
        } else if (pilih == 3) {
            postOrder(T.root);
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
}

void menuProduk(BSTProduk &T) {
    int pilih;

    do {
        cout << "\n=== KELOLA PRODUK ===\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Cari Produk\n";
        cout << "3. Hapus Produk\n";
        cout << "4. Tampilkan Produk\n";
        cout << "0. Kembali\n";
        cout << "Pilih : ";

        cin >> pilih;
        cin.ignore(1000, '\n');

        if (pilih == 1) {
            menuTambahProduk(T);
        } else if (pilih == 2) {
            menuCariProduk(T);
        } else if (pilih == 3) {
            menuHapusProduk(T);
        } else if (pilih == 4) {
            menuTampilProduk(T);
        } else if (pilih != 0) {
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilih != 0);
}

/* ================= MENU PELANGGAN ================= */

void menuTambahPelanggan(ListPelanggan &L, BSTProduk &T) {
    infotypePelanggan x;
    infotypePembelian beli;

    bool ok;
    char lagi;
    string kodeProduk;
    int jumlah;

    cout << "\n=== TAMBAH PELANGGAN ===\n";

    cout << "Kode pelanggan : ";
    getline(cin, x.kode);

    cout << "Nama pelanggan : ";
    getline(cin, x.nama);

    if (searchPelanggan(L, x.kode) != NULL) {
        cout << "Kode pelanggan sudah ada.\n";
    } else {
        insertPelanggan(L, x, ok);

        if (ok) {
            adrPelanggan p = searchPelanggan(L, x.kode);

            cout << "\nPelanggan berhasil ditambahkan.\n";

            if (!isEmpty(T)) {
                do {
                    cout << "\n=== DAFTAR PRODUK ===\n";
                    inOrder(T.root);

                    cout << "\nKode produk yang dibeli : ";
                    getline(cin, kodeProduk);

                    adrProduk produk = searchProduk(T, kodeProduk);

                    if (produk == NULL) {
                        cout << "Produk tidak ditemukan.\n";
                    } else {
                        cout << "Nama produk : "
                             << produk->info.nama << endl;

                        cout << "Jenis produk : "
                             << produk->info.jenis << endl;

                        cout << "Jumlah beli : ";
                        cin >> jumlah;
                        cin.ignore(1000, '\n');

                        if (jumlah <= 0) {
                            cout << "Jumlah pembelian tidak valid.\n";
                        } else if (jumlah > produk->info.stok) {
                            cout << "Stok tidak mencukupi.\n";
                        } else {
                            beli.kodeProduk = produk->info.kode;
                            beli.jumlah = jumlah;
                            beli.hargaBeli = produk->info.harga;

                            // Simpan produk ke pelanggan
                            insertPembelian(p->pembelian, beli);

                            // Kurangi stok produk
                            produk->info.stok -= jumlah;

                            // Tambah jumlah transaksi
                            produk->info.transaksi++;

                            cout << "Pembelian berhasil dicatat.\n";
                        }
                    }

                    cout << "Tambah produk lagi? (y/n) : ";
                    cin >> lagi;
                    cin.ignore(1000, '\n');

                } while (lagi == 'y' || lagi == 'Y');
            } else {
                cout << "Data produk masih kosong.\n";
            }
        }
    }
}

void menuCariPelanggan(ListPelanggan L) {
    string kode;

    cout << "Kode pelanggan : ";
    getline(cin, kode);

    adrPelanggan p = searchPelanggan(L, kode);

    if (p != NULL) {
        cout << "Pelanggan ditemukan: "
             << p->info.kode << " | "
             << p->info.nama << endl;
    } else {
        cout << "Pelanggan tidak ditemukan.\n";
    }
}

void menuHapusPelanggan(ListPelanggan &L) {
    string kode;
    bool ok;

    cout << "Kode pelanggan : ";
    getline(cin, kode);

    deletePelanggan(L, kode, ok);

    if (ok) {
        cout << "Pelanggan berhasil dihapus.\n";
    } else {
        cout << "Pelanggan tidak ditemukan.\n";
    }
}

void rekapPelanggan(ListPelanggan L, BSTProduk T) {
    adrPelanggan p = L.first;

    if (p == NULL) {
        cout << "Data pelanggan masih kosong.\n";
    } else {
        cout << "\n========== REKAP PELANGGAN ==========\n";

        while (p != NULL) {
            cout << "\nKode pelanggan : "
                 << p->info.kode << endl;

            cout << "Nama pelanggan : "
                 << p->info.nama << endl;

            cout << "Produk yang dibeli:\n";

            tampilPembelian(p->pembelian, T);

            cout << "------------------------------------\n";

            p = p->next;
        }
    }
}

void menuPelanggan(ListPelanggan &L, BSTProduk &T) {
    int pilih;

    do {
        cout << "\n=== KELOLA PELANGGAN ===\n";
        cout << "1. Tambah Pelanggan\n";
        cout << "2. Cari Pelanggan\n";
        cout << "3. Hapus Pelanggan\n";
        cout << "4. Rekap Pelanggan\n";
        cout << "0. Kembali\n";
        cout << "Pilih : ";

        cin >> pilih;
        cin.ignore(1000, '\n');

        if (pilih == 1) {
            menuTambahPelanggan(L, T);
        } else if (pilih == 2) {
            menuCariPelanggan(L);
        } else if (pilih == 3) {
            menuHapusPelanggan(L);
        } else if (pilih == 4) {
            rekapPelanggan(L, T);
        } else if (pilih != 0) {
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilih != 0);
}

/* ================= MAIN ================= */

int main() {
    BSTProduk T;
    ListPelanggan L;
    int pilih;

    createTree(T);
    createList(L);

    isiDataProduk(T);
    isiDataPelanggan(L);

    do {
        cout << "\n===== TOKO KOMPUTER COMPZONE =====\n";
        cout << "1. Kelola Produk\n";
        cout << "2. Kelola Pelanggan\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu : ";

        cin >> pilih;
        cin.ignore(1000, '\n');

        if (pilih == 1) {
            menuProduk(T);
        } else if (pilih == 2) {
            menuPelanggan(L, T);
        } else if (pilih != 0) {
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilih != 0);

    cout << "Program selesai.\n";

    return 0;
}
