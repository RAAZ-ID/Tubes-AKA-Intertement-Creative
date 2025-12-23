// service.cpp
#include "service.h"

// ============================================
// IMPLEMENTASI FUNGSI BST
// ============================================

void createBST(BST &T) {
    T.root = Nil;
}

adrService alokasiService(infoService data) {
    adrService P = new NodeService;
    P->info = data;
    P->left = Nil;
    P->right = Nil;
    return P;
}

void insertBST(BST &T, adrService P) {
    if (T.root == Nil) {
        T.root = P;
    } else {
        adrService current = T.root;
        adrService parent = Nil;
        
        while (current != Nil) {
            parent = current;
            if (P->info.idService < current->info.idService) {
                current = current->left;
            } else if (P->info.idService > current->info.idService) {
                current = current->right;
            } else {
                cout << "ID Service sudah ada!" << endl;
                delete P;
                return;
            }
        }
        
        if (P->info.idService < parent->info.idService) {
            parent->left = P;
        } else {
            parent->right = P;
        }
    }
}

adrService findService(adrService root, int idService) {
    if (root == Nil) {
        return Nil;
    }
    if (root->info.idService == idService) {
        return root;
    } else if (idService < root->info.idService) {
        return findService(root->left, idService);
    } else {
        return findService(root->right, idService);
    }
}

void showInOrder(adrService root) {
    if (root != Nil) {
        showInOrder(root->left);
        tampilkanService(root->info);
        showInOrder(root->right);
    }
}

void showPreOrder(adrService root) {
    if (root != Nil) {
        tampilkanService(root->info);
        showPreOrder(root->left);
        showPreOrder(root->right);
    }
}

void showPostOrder(adrService root) {
    if (root != Nil) {
        showPostOrder(root->left);
        showPostOrder(root->right);
        tampilkanService(root->info);
    }
}

int countTotalService(adrService root) {
    if (root == Nil) {
        return 0;
    }
    return 1 + countTotalService(root->left) + countTotalService(root->right);
}

adrService findMaxKomponen(adrService root, adrService &maxNode) {
    if (root == Nil) {
        return maxNode;
    }
    
    if (maxNode == Nil || root->info.komponenRusak.jumlahKomponen > maxNode->info.komponenRusak.jumlahKomponen) {
        maxNode = root;
    }
    
    findMaxKomponen(root->left, maxNode);
    findMaxKomponen(root->right, maxNode);
    
    return maxNode;
}

adrService findMinNode(adrService root) {
    adrService current = root;
    while (current != Nil && current->left != Nil) {
        current = current->left;
    }
    return current;
}

void deleteService(BST &T, int idService) {
    adrService parent = Nil;
    adrService current = T.root;
    
    // Cari node yang akan dihapus
    while (current != Nil && current->info.idService != idService) {
        parent = current;
        if (idService < current->info.idService) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    if (current == Nil) {
        cout << "Service tidak ditemukan!" << endl;
        return;
    }
    
    // Case 1: Node adalah leaf
    if (current->left == Nil && current->right == Nil) {
        if (parent == Nil) {
            T.root = Nil;
        } else if (parent->left == current) {
            parent->left = Nil;
        } else {
            parent->right = Nil;
        }
        delete current;
    }
    // Case 2: Node punya 1 child
    else if (current->left == Nil || current->right == Nil) {
        adrService child = (current->left != Nil) ? current->left : current->right;
        if (parent == Nil) {
            T.root = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete current;
    }
    // Case 3: Node punya 2 children
    else {
        adrService successor = findMinNode(current->right);
        int tempId = successor->info.idService;
        deleteService(T, successor->info.idService);
        current->info.idService = tempId;
    }
}

// ============================================
// IMPLEMENTASI FUNGSI MLL
// ============================================

void createListTeknisi(ListTeknisi &L) {
    L.first = Nil;
}

adrTeknisi alokasiTeknisi(infoTeknisi data) {
    adrTeknisi P = new ElmTeknisi;
    P->info = data;
    P->firstAntrian = Nil;
    P->next = Nil;
    return P;
}

adrAntrian alokasiAntrian(int idService) {
    adrAntrian P = new ElmAntrian;
    P->idService = idService;
    P->next = Nil;
    return P;
}

void insertTeknisi(ListTeknisi &L, adrTeknisi P) {
    if (L.first == Nil) {
        L.first = P;
    } else {
        adrTeknisi Q = L.first;
        while (Q->next != Nil) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void insertAntrian(adrTeknisi T, adrAntrian P) {
    if (T->firstAntrian == Nil) {
        T->firstAntrian = P;
    } else {
        adrAntrian Q = T->firstAntrian;
        while (Q->next != Nil) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

adrTeknisi findTeknisi(ListTeknisi L, int idTeknisi) {
    adrTeknisi P = L.first;
    while (P != Nil) {
        if (P->info.idTeknisi == idTeknisi) {
            return P;
        }
        P = P->next;
    }
    return Nil;
}

void showAllTeknisi(ListTeknisi L) {
    if (L.first == Nil) {
        cout << "Belum ada teknisi terdaftar!" << endl;
        return;
    }
    
    adrTeknisi P = L.first;
    int no = 1;
    cout << "\n========================================" << endl;
    cout << "        DAFTAR TEKNISI" << endl;
    cout << "========================================" << endl;
    
    while (P != Nil) {
        cout << no << ". ID Teknisi     : " << P->info.idTeknisi << endl;
        cout << "   Nama           : " << P->info.namaTeknisi << endl;
        cout << "   Spesialisasi   : " << P->info.spesialisasi << endl;
        cout << "   Jumlah Antrian : " << countAntrianTeknisi(P) << endl;
        cout << "----------------------------------------" << endl;
        P = P->next;
        no++;
    }
}

void showAntrianTeknisi(adrTeknisi T) {
    if (T->firstAntrian == Nil) {
        cout << "Tidak ada antrian." << endl;
        return;
    }
    
    adrAntrian P = T->firstAntrian;
    int no = 1;
    cout << "\nAntrian Service:" << endl;
    while (P != Nil) {
        cout << no << ". ID Service: " << P->idService << endl;
        P = P->next;
        no++;
    }
}

int countAntrianTeknisi(adrTeknisi T) {
    int count = 0;
    adrAntrian P = T->firstAntrian;
    while (P != Nil) {
        count++;
        P = P->next;
    }
    return count;
}

adrTeknisi findTeknisiPalingSedikit(ListTeknisi L) {
    if (L.first == Nil) {
        return Nil;
    }
    
    adrTeknisi minTeknisi = L.first;
    int minAntrian = countAntrianTeknisi(minTeknisi);
    
    adrTeknisi P = L.first->next;
    while (P != Nil) {
        int jumlah = countAntrianTeknisi(P);
        if (jumlah < minAntrian) {
            minAntrian = jumlah;
            minTeknisi = P;
        }
        P = P->next;
    }
    
    return minTeknisi;
}

void deleteFirstAntrian(adrTeknisi T, adrAntrian &P) {
    if (T->firstAntrian != Nil) {
        P = T->firstAntrian;
        T->firstAntrian = P->next;
        P->next = Nil;
    }
}

int countTotalAntrian(ListTeknisi L) {
    int total = 0;
    adrTeknisi P = L.first;
    while (P != Nil) {
        total += countAntrianTeknisi(P);
        P = P->next;
    }
    return total;
}

// ============================================
// IMPLEMENTASI FUNGSI HELPER
// ============================================

void tampilkanService(infoService data) {
    cout << "\n========================================" << endl;
    cout << "ID Service      : " << data.idService << endl;
    cout << "Nama Customer   : " << data.namaCustomer << endl;
    cout << "Jenis Device    : " << data.jenisDevice << endl;
    cout << "Keluhan         : " << data.keluhan << endl;
    cout << "Estimasi        : " << data.estimasiHari << " hari" << endl;
    cout << "Komponen Rusak  : ";
    if (data.komponenRusak.jumlahKomponen == 0) {
        cout << "Belum ada";
    } else {
        cout << endl;
        for (int i = 0; i < data.komponenRusak.jumlahKomponen; i++) {
            cout << "  - " << data.komponenRusak.namaKomponen[i] << endl;
        }
    }
    cout << "========================================" << endl;
}

void clearScreen() {
    system("cls");
}

void pause() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}