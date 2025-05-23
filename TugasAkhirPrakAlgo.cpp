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