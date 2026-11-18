#include "produk.h"

/* ================= PEMBUATAN ================= */

void createTree(BSTProduk &T) {
    /* I.S. : T sembarang
       F.S. : T.root = NULL */
    T.root = NULL;
}

adrProduk createNode(infotypeProduk x) {
    /* I.S. : x terdefinisi
       F.S. : mengembalikan node baru berisi x */
    adrProduk p = new nodeProduk;

    p->info = x;
    p->left = NULL;
    p->right = NULL;

    return p;
}

bool isEmpty(BSTProduk T) {
    /* I.S. : T terdefinisi
       F.S. : true jika tree kosong */
    return T.root == NULL;
}

/* ================= INSERT ================= */

static void insertNode(adrProduk &root, infotypeProduk x, bool &berhasil) {
    /* I.S. : root terdefinisi (boleh NULL)
       F.S. : x masuk ke subtree root jika kodenya belum ada */
    if (root == NULL) {
        root = createNode(x);
        berhasil = true;
    } else if (x.kode < root->info.kode) {
        insertNode(root->left, x, berhasil);
    } else if (x.kode > root->info.kode) {
        insertNode(root->right, x, berhasil);
    } else {
        berhasil = false;   // kode kembar
    }
}

void insertProduk(BSTProduk &T, infotypeProduk x, bool &berhasil) {
    /* I.S. : T terdefinisi
       F.S. : x masuk ke BST jika kode belum ada */
    insertNode(T.root, x, berhasil);
}

/* ================= SEARCH ================= */

adrProduk searchProduk(BSTProduk T, string kode) {
    /* I.S. : T terdefinisi
       F.S. : mengembalikan alamat node berkode 'kode', atau NULL */
    adrProduk p = T.root;

    while (p != NULL && p->info.kode != kode) {
        if (kode < p->info.kode) {
            p = p->left;
        } else {
            p = p->right;
        }
    }

    return p;
}

/* ================= DELETE ================= */

static adrProduk detachMin(adrProduk &root) {
    /* I.S. : root tidak NULL
       F.S. : node paling kiri dilepas dari tree, alamatnya dikembalikan */
    adrProduk m;

    if (root->left == NULL) {
        m = root;
        root = root->right;
    } else {
        m = detachMin(root->left);
    }

    return m;
}

static void deleteNode(adrProduk &root, string kode, bool &berhasil) {
    /* I.S. : root terdefinisi (boleh NULL)
       F.S. : node berkode 'kode' dihapus jika ada */
    if (root == NULL) {
        berhasil = false;
    } else if (kode < root->info.kode) {
        deleteNode(root->left, kode, berhasil);
    } else if (kode > root->info.kode) {
        deleteNode(root->right, kode, berhasil);
    } else {
        adrProduk hapus = root;

        if (root->left == NULL) {            // 0 anak, atau 1 anak (kanan)
            root = root->right;
        } else if (root->right == NULL) {    // 1 anak (kiri)
            root = root->left;
        } else {                             // 2 anak
            adrProduk pengganti = detachMin(root->right);
            pengganti->left = root->left;
            pengganti->right = root->right;
            root = pengganti;
        }

        delete hapus;
        berhasil = true;
    }
}

void deleteProduk(BSTProduk &T, string kode, bool &berhasil) {
    /* I.S. : T terdefinisi
       F.S. : node berkode 'kode' dihapus jika ada */
    deleteNode(T.root, kode, berhasil);
}

/* ================= TAMPILAN ================= */

string formatRupiah(int angka) {
    /* I.S. : angka terdefinisi (tidak negatif)
       F.S. : mengembalikan angka dengan titik pemisah ribuan */
    string s = to_string(angka);
    string hasil = "";
    int n = s.length();

    for (int i = 0; i < n; i++) {
        hasil += s[i];

        if ((n - i - 1) % 3 == 0 && i != n - 1) {
            hasil += ".";
        }
    }

    return hasil;
}

void tampilProduk(adrProduk p) {
    /* I.S. : p tidak NULL
       F.S. : data produk tercetak satu baris */
    cout << p->info.kode << " | "
         << p->info.nama << " | "
         << p->info.jenis << " | Transaksi "
         << p->info.transaksi << " | Rp "
         << formatRupiah(p->info.harga)
         << " | Stok " << p->info.stok << endl;
}

/* ================= TRAVERSAL ================= */

void inOrder(adrProduk root) {
    /* I.S. : root terdefinisi (boleh NULL)
       F.S. : produk tercetak urut kiri - akar - kanan */
    if (root != NULL) {
        inOrder(root->left);
        tampilProduk(root);
        inOrder(root->right);
    }
}

void preOrder(adrProduk root) {
    /* I.S. : root terdefinisi (boleh NULL)
       F.S. : produk tercetak urut akar - kiri - kanan */
    if (root != NULL) {
        tampilProduk(root);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(adrProduk root) {
    /* I.S. : root terdefinisi (boleh NULL)
       F.S. : produk tercetak urut kiri - kanan - akar */
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        tampilProduk(root);
    }
}
