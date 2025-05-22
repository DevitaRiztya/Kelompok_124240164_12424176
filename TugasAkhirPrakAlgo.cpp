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