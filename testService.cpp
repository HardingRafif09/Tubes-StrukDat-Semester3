#include "service.h"

int main() {
    ListService L;
    bool ok;
    infotypeService a = {"S001", "Laptop", "Layar mati",        350000, "Diterima"};
    infotypeService b = {"S002", "PC",     "Tidak bisa menyala", 200000, "Diterima"};
    infotypeService c = {"S003", "Laptop", "Baterai drop",       450000, "Diterima"};

    createListService(L);
    cout << "--- list kosong ---\n";
    tampilService(L);                 // Belum ada data service.

    insertService(L, a, ok);  cout << "Insert S001 : " << ok << endl;   // 1
    insertService(L, b, ok);  cout << "Insert S002 : " << ok << endl;   // 1
    insertService(L, c, ok);  cout << "Insert S003 : " << ok << endl;   // 1
    insertService(L, b, ok);  cout << "Insert S002 lagi : " << ok << endl;  // 0

    cout << "--- tampil (insert first: S003, S002, S001) ---\n";
    tampilService(L);

    cout << "Cari S002 : " << (searchService(L, "S002") != NULL) << endl;  // 1
    cout << "Cari S999 : " << (searchService(L, "S999") != NULL) << endl;  // 0

    updateStatusService(L, "S002", "Diproses", ok);
    cout << "Ubah status S002 : " << ok << endl;                          // 1
    updateStatusService(L, "S999", "Selesai", ok);
    cout << "Ubah status S999 : " << ok << endl;                          // 0
    tampilService(L);

    deleteService(L, "S002", ok);  cout << "Hapus S002 (tengah) : " << ok << endl;  // 1
    deleteService(L, "S003", ok);  cout << "Hapus S003 (awal)   : " << ok << endl;  // 1
    deleteService(L, "S001", ok);  cout << "Hapus S001 (akhir)  : " << ok << endl;  // 1
    deleteService(L, "S001", ok);  cout << "Hapus S001 lagi     : " << ok << endl;  // 0

    insertService(L, a, ok);
    insertService(L, b, ok);
    deleteAllService(L);
    cout << "--- setelah deleteAll ---\n";
    tampilService(L);                 // Belum ada data service.
    return 0;
}