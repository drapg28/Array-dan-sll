#include "NSLL.h"

int jumlahKota = 0; 

// Membuat node baru
void Create_Node(address *p, infotype data) {
    *p = (address)malloc(sizeof(ElmtList));
    if (*p != NULL) {
        strcpy((*p)->info, data);  
        (*p)->next = NULL;
    }
}

// Menghapus node
void DeAlokasi(address *p) {
    free(*p);
    *p = NULL;
}

// Mengecek apakah list kosong
bool isEmpty(List L) {
    return L == NULL;
}


// *** OPERASI PENYISIPAN ***
void InsVFirst(List *L, infotype X) {
    address P;
    Create_Node(&P, X);
    if (P != NULL) {
        P->next = *L;
        *L = P;
    }
}

void InsVLast(List *L, infotype X) {
    address P, Last;
    Create_Node(&P, X);
    if (P != NULL) {
        if (isEmpty(*L)) {
            *L = P;
        } else {
            Last = *L;
            while (Last->next != NULL) {
                Last = Last->next;
            }
            Last->next = P;
        }
    }
}

void InsertFirst(List *L, address P) {
    P->next = *L;
    *L = P;
}

void InsertAfter(List *L, address P, address Prec) {
    if (Prec != NULL) {
        P->next = Prec->next;
        Prec->next = P;
    }
    (void)L; // Prevent unused parameter warning
        (void)P;
        (void)Prec;
}

void InsertLast(List *L, address P) {
    address Last;
    if (isEmpty(*L)) {
        *L = P;
    } else {
        Last = *L;
        while (Last->next != NULL) {
            Last = Last->next;
        }
        Last->next = P;
    }
}

// *** OPERASI PENGHAPUSAN ***
void DelVFirst(List *L, infotype *X) {
    address P;
    if (!isEmpty(*L)) {
        P = *L;
        strcpy(*X, P->info);
        *L = P->next;
        DeAlokasi(&P);
    }
}

void DelVLast(List *L, infotype *X) {
    address P, Prec = NULL;
    if (!isEmpty(*L)) {
        P = *L;
        while (P->next != NULL) {
            Prec = P;
            P = P->next;
        }
        strcpy(*X, P->info); 
        if (Prec == NULL) {
            *L = NULL;
        } else {
            Prec->next = NULL;
        }
        DeAlokasi(&P);
    }
}

void DelFirst(List *L, address *P) {
    if (!isEmpty(*L)) {
        *P = *L;
        *L = (*P)->next;
        DeAlokasi(P);
    }
}

void DelLast(List *L, address *P) {
    address Prec = NULL;
    if (!isEmpty(*L)) {
        *P = *L;
        while ((*P)->next != NULL) {
            Prec = *P;
            *P = (*P)->next;
        }
        if (Prec == NULL) {
            *L = NULL;
        } else {
            Prec->next = NULL;
        }
        DeAlokasi(P);
    }
}

void DelP(List *L, infotype X) {
    address P = *L, Prec = NULL;
    while (P != NULL && P->info != X) {
        Prec = P;
        P = P->next;
    }
    if (P != NULL) {
        if (Prec == NULL) {
            *L = P->next;
        } else {
            Prec->next = P->next;
        }
        DeAlokasi(&P);
    }
}

// *** OPERASI PENCARIAN ***
address Search(List L, infotype X) {
    address P = L;
    while (P != NULL && P->info != X) {
        P = P->next;
    }
    return P;
}

// Menghapus seluruh list
void DeleteList(List *L) {
    address P;
    while (!isEmpty(*L)) {
        P = *L;
        *L = P->next;
        DeAlokasi(&P);
    }
}

void PrintList(List L) {
    address P = L;
    if (P == NULL) {
        printf("  (Tidak ada nama)\n");
    }
    while (P != NULL) {
        printf("  - %s\n", P->info);
        P = P->next;
    }
}

int cariKota(char nama[]) {
    for (int i = 0; i < jumlahKota; i++) {
        if (strcmp(JmlKota[i].namaKota, nama) == 0)
            return i;
    }
    return -1;
}

void tambahNamaKeKota(char nama[], char kota[]) {
    int idx = cariKota(kota);
    if (idx == -1) {
        if (jumlahKota >= MAX_KOTA) {
            printf("Kota sudah mencapai batas maksimum!\n");
            return;
        }
        strcpy(JmlKota[jumlahKota].namaKota, kota);
        JmlKota[jumlahKota].daftarNama = NULL;
        idx = jumlahKota++;
    }
    InsVLast(&JmlKota[idx].daftarNama, nama);
}

void tampilkanSemua() {
    if (jumlahKota == 0) {
        printf("Tidak ada data kota.\n");
        return;
    }

    for (int i = 0; i < jumlahKota; i++) {
        printf("\"%s\"", JmlKota[i].namaKota);

        address P = JmlKota[i].daftarNama;
        while (P != NULL) {
            printf(" \"%s\"", P->info);
            P = P->next;
        }

        printf("\n");
    }
}

void tampilkanPerKota(char kota[]) {
    int idx = cariKota(kota);
    if (idx == -1) {
        printf("Kota tidak ditemukan.\n");
        return;
    }

    printf("\"%s\"", JmlKota[idx].namaKota);

    address P = JmlKota[idx].daftarNama;
    while (P != NULL) {
        printf(" \"%s\"", P->info);
        P = P->next;
    }

    printf("\n");
}

void hapusKota(char kota[]) {
    int idx = cariKota(kota);
    if (idx == -1) {
        printf("Kota tidak ditemukan.\n");
        return;
    }

    DeleteList(&JmlKota[idx].daftarNama);
    for (int i = idx; i < jumlahKota - 1; i++) {
        JmlKota[i] = JmlKota[i + 1];
    }
    jumlahKota--;
    printf("Kota %s dan seluruh nama di dalamnya telah dihapus.\n", kota);
}

void Menu() {
    int pilihan;
    char nama[30], kota[30];

    do {
        printf("\n=== MENU DATA KOTA ===\n");
        printf("1. Tambah Nama ke Kota\n");
        printf("2. Hapus Kota\n");
        printf("3. Tampilkan Semua Data\n");
        printf("4. Tampilkan Nama per Kota\n");
        printf("0. Keluar\n");
        printf("Pilihan: "); scanf("%d", &pilihan); getchar();

        switch (pilihan) {
            case 1:
                printf("Masukkan Nama: "); fgets(nama, sizeof(nama), stdin);
                nama[strcspn(nama, "\n")] = '\0';
                printf("Masukkan Kota: "); fgets(kota, sizeof(kota), stdin);
                kota[strcspn(kota, "\n")] = '\0';
                tambahNamaKeKota(nama, kota);
                break;

            case 2:
                printf("Masukkan Kota yang ingin dihapus: "); fgets(kota, sizeof(kota), stdin);
                kota[strcspn(kota, "\n")] = '\0';
                hapusKota(kota);
                break;

            case 3:
                tampilkanSemua();
                break;

            case 4:
                printf("Masukkan Kota: "); fgets(kota, sizeof(kota), stdin);
                kota[strcspn(kota, "\n")] = '\0';
                tampilkanPerKota(kota);
                break;

            case 0:
                printf("Terima kasih!\n");
                break;

            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);
}