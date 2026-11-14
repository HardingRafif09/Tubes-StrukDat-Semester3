
#include "produk.h"

void createTree(BSTProduk &T) {
    T.root = NULL;
}

adrProduk createNode(infotypeProduk x) {
    adrProduk p = new nodeProduk;
    p->info = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}

bool isEmpty(BSTProduk T) {
    return T.root == NULL;
}

static void insertNode(adrProduk &root, infotypeProduk x,
                       bool &berhasil) {
    if (root == NULL) {
        root = createNode(x);
        berhasil = true;
    } else if (x.kode < root->info.kode) {
        insertNode(root->left, x, berhasil);
    } else if (x.kode > root->info.kode) {
        insertNode(root->right, x, berhasil);
    } else {
        berhasil = false;
    }
}

void insertProduk(BSTProduk &T, infotypeProduk x,
                  bool &berhasil) {
    insertNode(T.root, x, berhasil);
}

adrProduk searchProduk(BSTProduk T, string kode) {
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

static adrProduk detachMin(adrProduk &root) {
    adrProduk m;

    if (root->left == NULL) {
        m = root;
        root = root->right;
    } else {
        m = detachMin(root->left);
    }

    return m;
}

static void deleteNode(adrProduk &root, string kode,
                       bool &berhasil) {
    if (root == NULL) {
        berhasil = false;
    } else if (kode < root->info.kode) {
        deleteNode(root->left, kode, berhasil);
    } else if (kode > root->info.kode) {
        deleteNode(root->right, kode, berhasil);
    } else {
        adrProduk hapus = root;

        if (root->left == NULL) {
            root = root->right;
        } else if (root->right == NULL) {
            root = root->left;
        } else {
            adrProduk pengganti = detachMin(root->right);
            pengganti->left = root->left;
            pengganti->right = root->right;
            root = pengganti;
        }

        delete hapus;
        berhasil = true;
    }
}

void deleteProduk(BSTProduk &T, string kode,
                  bool &berhasil) {
    deleteNode(T.root, kode, berhasil);
}

string formatRupiah(int angka) {
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
    cout << p->info.kode << " | "
         << p->info.nama << " | "
         << p->info.jenis << " | Transaksi "
         << p->info.transaksi << " | Rp "
         << formatRupiah(p->info.harga)
         << " | Stok " << p->info.stok << endl;
}

void inOrder(adrProduk root) {
    if (root != NULL) {
        inOrder(root->left);
        tampilProduk(root);
        inOrder(root->right);
    }
}

void preOrder(adrProduk root) {
    if (root != NULL) {
        tampilProduk(root);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(adrProduk root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        tampilProduk(root);
    }
}
