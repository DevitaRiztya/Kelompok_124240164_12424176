//24-hour Networked Parking System
#include <iostream>
#include <string.h> 

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

//fungsi untuk mengelompokan pemasukan perminggu
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

//fungsi pembulatan menit lebih
int hitungMenit(int jamMasuk, int menitMasuk, int jamKeluar, int menitKeluar) {
    int totalMasuk = (jamMasuk * 60) + menitMasuk;
    int totalKeluar = (jamKeluar * 60) + menitKeluar;
    int durasi = totalKeluar - totalMasuk;

    // Kalau durasi negatif, berarti nyebrang hari (misalnya jam masuk 21.00, keluar 08.00)
    if (durasi < 0) {
        durasi += 24 * 60; // tambah 1 hari (dalam menit)
    }

    int durasiJam = durasi / 60;

    // Kalau masih ada sisa menit, bulatkan ke atas
    if (durasi % 60 != 0) {
        durasiJam++;
    }
    return durasiJam;
}

//fungsi menghitung biaya per jenis kendaraan
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

//menambahkan data parkir baru ke dalam linked list
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

//menampilkan data yang sudah diinput
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

//sorting data parkir sesuai tanggal 
void sortByTanggal() {
    if(head==NULL){
        return;
    }
    parkir* temp1=head;
    while(temp1!=NULL){
        parkir*temp2=temp1->next;
        while(temp2!=NULL){
            if(temp1->tgl.tanggal > temp2->tgl.tanggal) {
                swap(*temp1, *temp1);
                swap(temp1->next, temp2->next);
            }
            temp2=temp2->next;
        }
        temp1=temp1->next;
    }
}

//menghitung total pemasukan dalam minggu
void totalPerMinggu() {
    int total[4] = {0};
    parkir* temp = head; 
    while(temp) {
        int minggu = omsetPerMinggu(temp->tgl.tanggal)-1; 
        total[minggu] += temp->biaya; 
        temp = temp->next; 
    }
    cout << "===== Pendapatan Per-Minggu =====" << endl;
    for (int i = 0; i < 4; i++) { 
        cout << "Minggu ke-" << i+1 << " : Rp " << total[i] << ",-" << endl;
    }
    cout << "Total bulan ini : Rp " << total[0] + total[1] + total[2] + total[3] << ",-" << endl;
}

//search data
void cariParkir(char* keyword) {
    parkir* temp = head; 
    int ditemukan = 0; 
    while(temp) { 
        if (strstr(temp->plat, keyword) || strstr(temp->jenis, keyword)){ 
            cout << "Plat        : " << temp->plat << endl;
            cout << "Jenis       : " << temp->jenis << endl;
            cout << "Tanggal     : " << temp->tgl.tanggal << "-" << temp->tgl.bulan << "-" << temp->tgl.tahun << endl;
            cout << "Jam Masuk   : " << temp->jamMasuk << ":" << temp->menitMasuk << endl;
            cout << "Jam Keluar  : " << temp->jamKeluar << ":" << temp->menitKeluar << endl;
            cout << "Durasi      : " << temp->durasiJam << " jam" << endl;
            cout << "Biaya       : Rp " << temp->biaya << ",-" << endl;
            cout << endl;
            ditemukan = 1; 
        }
        temp = temp->next; 
    }
    if(!ditemukan)
        cout << "Data tidak ditemukan." << endl;
}

//simpan ke file
void simpanKeFile() {
    FILE *file = fopen("DataParkir.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    parkir* temp = head;
    while (temp != NULL) {
        fprintf(file, "_______________________\n");
        fprintf(file, "Plat       : %s\n", temp->plat);
        fprintf(file, "Jenis      : %s\n", temp->jenis);
        fprintf(file, "Tanggal    : %02d-%02d-%04d\n", temp->tgl.tanggal, temp->tgl.bulan, temp->tgl.tahun);
        fprintf(file, "Jam Masuk  : %02d:%02d\n", temp->jamMasuk, temp->menitMasuk);
        fprintf(file, "Jam Keluar : %02d:%02d\n", temp->jamKeluar, temp->menitKeluar);
        fprintf(file, "Durasi     : %d jam\n", temp->durasiJam);
        fprintf(file, "Biaya      : Rp %d,-\n", temp->biaya);
        temp = temp->next;
    }
    fclose(file);
    printf("Data berhasil disimpan ke file (DataParkir.txt).\n");
}

//menu
void menu() {
    char plat[20];
    char jenis[10];
    int tanggal, bulan, tahun, jamMasuk, jamKeluar, durasiMenit, menitMasuk, menitKeluar, durasiJam, n, x;

    do {
        system("cls");
        cout << "======== SISTEM PARKIR ========" << endl;
        cout << "1. Tambah Data Parkir" << endl;
        cout << "2. Tampilkan Semua Data" << endl;
        cout << "3. Tampilkan Total Per Minggu" << endl;
        cout << "4. Cari Data Parkir" << endl;
        cout << "5. Simpan Ke File" << endl;
        cout << "0. Exit" << endl;
        cout << "Pilihan : "; cin >> n;
        cout << endl;
        cin.ignore();
        
        switch(n) {
            case 1 :
            {
                cout << "Berapa banyak kendaraan yang mau anda input? "; cin >> x;
                cout << endl;
                cin.ignore();

                for (int i = 0; i < x; i++){
                    cout << "________________________________" << endl;
                    cout << "Data ke-" << i+1 << endl;
                    cout << "Plat nomor          : "; cin.getline(plat, sizeof(plat));
                    while (true) {
                        cout << "Jenis (motor/mobil) : "; cin.getline(jenis, sizeof(jenis));
                        if (strcmp(jenis, "motor") == 0 || strcmp(jenis, "mobil") == 0) {
                            break; // valid
                        } else {
                            cout << "Jenis kendaraan tidak valid! Hanya 'motor' atau 'mobil'. Ulangi input.\n";
                        }
                    }
                    printf("Tanggal             : "); scanf("%d-%d-%d", &tanggal, &bulan, &tahun);
                    printf("Jam Masuk           : "); scanf("%d.%d", &jamMasuk, &menitMasuk);
                    printf("Jam Keluar          : "); scanf("%d.%d", &jamKeluar, &menitKeluar);
                    cout << endl;
                    cin.ignore();

                    int totalMasuk = jamMasuk * 60 + menitMasuk;
                    int totalKeluar = jamKeluar * 60 + menitKeluar;
                    if (tanggal < 1 || tanggal > 31 || jamMasuk < 0 || jamKeluar > 24 || totalMasuk == totalKeluar) {
                        cout << "Input tidak valid!" << endl;
                        i--;
                    }
                    else {
                        durasiJam = hitungMenit(jamMasuk, menitMasuk, jamKeluar, menitKeluar);
                        tambahParkir(plat, jenis, tanggal, bulan, tahun, jamMasuk, jamKeluar, menitMasuk, menitKeluar, durasiJam);
                    }
                    // if(tanggal<1 || tanggal>31 || jamMasuk<0 || jamKeluar>24 || jamKeluar<=jamMasuk) {
                    //     cout << "Input tidak valid!" << endl;
                    //     i--;
                    // } else {
                    //     durasiJam = hitungMenit(jamMasuk, menitMasuk, jamKeluar, menitKeluar);
                    //     tambahParkir(plat, jenis, tanggal, bulan, tahun, jamMasuk, jamKeluar, menitMasuk, menitKeluar, durasiJam);
                    // }
                }
                system("pause");
                break;
            }
            case 2:
            {
                sortByTanggal();
                tampilkanData();
                system("pause");
                break;
            }
            case 3:
            {
                totalPerMinggu();
                system("pause");
                break;
            }
            case 4:
            {
                cout << "Masukan plat nomor : "; cin.getline(plat, sizeof(plat));
                cout << endl;
                cariParkir(plat);
                system("pause");
                break;
            }  
            case 5:
            {
                simpanKeFile();
                system("pause");
                break;
            } 
            case 0:
            {
                cout << "Keluar dari program" << endl;
                break;
            }
            default:
            {
                cout << "pilihan tidak valid" << endl;
            }   
        }
    } while(n!=0);
}

int main() {
    menu();
    parkir* temp; 
    while (head != NULL) { 
        temp = head; 
        head = head->next;
        delete temp; 
    }
    return 0;
}