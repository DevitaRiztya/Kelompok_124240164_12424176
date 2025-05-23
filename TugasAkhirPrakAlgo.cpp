//Networked Parking System
#include <iostream>
#include <string.h> 
#include <fstream>

using namespace std;


struct Tanggal{
    int tanggal;
    int bulan;
    int tahun;
};

//struct parkir
struct parkir {
    char plat[20];
    char jenis[10]; 
    int jamMasuk;
    int jamKeluar;
    int menitMasuk;
    int menitKeluar;
    int durasiJam;
    int biaya;
    Tanggal tgl;
    parkir* next; 
};

struct parkir* head = NULL;

int omsetPerMinggu(int tanggal) {
    if(tanggal >= 1 && tanggal <= 7) {
        return 1;
    }
    else if(tanggal >= 8 && tanggal <= 14) {
        return 2;
    }
    else if(tanggal >= 15 && tanggal <= 21) {
        return 3;
    }
    else{
        return 4;
    }
}

int hitungMenit(int jamMasuk, int menitMasuk, int jamKeluar, int menitKeluar) {
    int totalMasuk = (jamMasuk * 60) + menitMasuk;
    int totalKeluar = (jamKeluar * 60) + menitKeluar;
    int durasi = totalKeluar - totalMasuk;

    int durasiJam = durasi / 60;
    if (durasi % 60 != 0) {
        durasiJam++;
    }
    return durasiJam;
}

int hitungBiaya(char* jenis, int durasiJam) {
    if(strcmp(jenis, "motor") == 0) {
        return durasiJam * 2000;
    } 
    else if(strcmp(jenis, "mobil") == 0) {
        return durasiJam * 5000;
    } else {
        return 0; 
    }
}

void tambahParkir(char *plat, char *jenis, int tanggal, int bulan, int tahun, int jamMasuk, int jamKeluar, int menitMasuk, int menitKeluar, int durasiJam) {
    parkir *newparkir = new parkir;
    strcpy(newparkir->plat, plat);
    strcpy(newparkir->jenis, jenis);
    newparkir->tgl.tanggal = tanggal;
    newparkir->tgl.bulan = bulan;
    newparkir->tgl.tahun = tahun;
    newparkir->jamMasuk = jamMasuk;
    newparkir->jamKeluar = jamKeluar;
    newparkir->menitMasuk = menitMasuk;
    newparkir->menitKeluar = menitKeluar;
    newparkir->durasiJam = durasiJam;
    newparkir->biaya = hitungBiaya(jenis,newparkir-> durasiJam);
    newparkir->next = head;
    head = newparkir;
    cout << "Data parkir berhasil ditambahkan!" << endl;
}

void tampilkanData() {
    parkir* temp = head;
    if (temp == NULL) {
        cout << "Belum ada data parkir." << endl;
        return;
    }
    cout <<"====== Riwayat Parkir ======" << endl;
    cout << endl;
    while(temp!=NULL) {
        cout << "Plat           : " << temp->plat << endl;
        cout << "Jenis          : " << temp->jenis << endl;
        cout << "Tanggal        : " << temp->tgl.tanggal << "-" << temp->tgl.bulan << "-" << temp->tgl.tahun << endl;
        cout << "Jam Masuk      : " << temp->jamMasuk << ":" << temp->menitMasuk << endl;
        cout << "Jam Keluar     : " << temp->jamKeluar << ":" << temp->menitKeluar << endl;
        cout << "Durasi         : " << temp->durasiJam << " jam" << endl;
        cout << "Biaya          : Rp." << temp->biaya << "-" << endl;
        cout << endl;
        temp = temp->next;

    }
}