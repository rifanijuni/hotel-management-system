#include <iostream>
#include <fstream>
using namespace std;

struct Tamu {
    int id;
    string nama;
    int lantai;
    int kamar;
    int lamaInap;
};

string hotel[3][5] = {
    {"KOSONG","KOSONG","KOSONG","KOSONG","KOSONG"},
    {"KOSONG","KOSONG","KOSONG","KOSONG","KOSONG"},
    {"KOSONG","KOSONG","KOSONG","KOSONG","KOSONG"}
};

const int maxTamu = 100;
Tamu tamu[maxTamu];
int jumlahTamu = 0;

void header();
void lihatKamar();
void bookingKamar();
void cariTamu();
void laporan();
void loadFile();
void saveFile();
void totalPendapatan();
int hitungBiaya(int hari, int harga);
string spasiToUnderscore(string teks);
string underscoreToSpasi(string teks);

int main() {
    int pilih;
    char out;
    bool keluar = false;

    do {
        header();

        cout << "1. Lihat Status Kamar\n"
             << "2. Booking Kamar\n"
             << "3. Cari Data Tamu\n"
             << "4. Laporan Data Tamu (Sorting)\n"
             << "5. Hitung Total Pendapatan\n"
             << "6. Keluar Aplikasi\n"
             << "===================================================\n"
             << "Pilih menu [1-6] : ";

        cin >> pilih;

        switch (pilih) {
            case 1 :
                lihatKamar();
                break;
            case 2 :
                bookingKamar();
                break;
            case 3 :
                cariTamu();
                break;
            case 4 :
                laporan();
                break;
            case 5 :
                totalPendapatan();
                break;
            case 6 :
                cout << "Apakah anda yakin ingin keluar? (y/n) : ";
                cin >> out;
                if (out == 'y' || out == 'Y') {
                    cout << "Terima kasih telah menggunakan program!\n";
                    keluar = true;
                    system("pause");
                }
                break;
            default :
                cout << "Menu tidak valid!\n";
                system("pause");
                break;
        }
    } while (keluar == false);
    return 0;
}

void header(){
    system("cls");
    cout << "===================================================\n"
        << "              HOTEL MANAGEMENT SYSTEM              \n"
        << "===================================================\n";
}

string spasiToUnderscore(string teks) {
    for(int i = 0; i < teks.length(); i++) {
        if(teks[i] == ' ') {
            teks[i] = '_';
        }
    }
    return teks;
}

string underscoreToSpasi(string teks) {
    for(int i = 0; i < teks.length(); i++) {
        if(teks[i] == '_') {
            teks[i] = ' ';
        }
    }
    return teks;
}

void lihatKamar(){
    header();
    cout << "\n------------------- Lihat Kamar -------------------\n";

    system("pause");
}

/**
 * Input Data
 */
void bookingKamar(){
    header();
    
}

/**
 * Searching Data
 */
void cariTamu(){
    header();
    
}

/**
 * Sorting Data
 */
void laporan(){
    header();
    
}

/**
 * Rekursif hitung pendapatan
 */

int hitungBiaya(int hari, int harga) {
    if(hari <= 0)
        return 0;

    return harga + hitungBiaya(hari - 1, harga);
}

void totalPendapatan() {
    header();

    int hargaPerMalam = 300000;
    int total = 0;

    for(int i = 0; i < jumlahTamu; i++) {
        total += hitungBiaya(tamu[i].lamaInap, hargaPerMalam);
    }

    cout << "Total Tamu : " << jumlahTamu << " orang" << endl;
    cout << "Total Pendapatan : Rp " << total << endl;
    system("pause");
}

/**
 * File
 */
void loadFile() {
    ifstream file("data_tamu.txt");
	if (file.is_open()){
		cout << "File ditemukan. Memuat data...\n";
		while (jumlahTamu < maxTamu && file >> tamu[jumlahTamu].id >> tamu[jumlahTamu].nama >> tamu[jumlahTamu].lantai >> tamu[jumlahTamu].kamar >> tamu[jumlahTamu].lamaInap) {
			tamu[jumlahTamu].id = tamu[jumlahTamu].id;
			tamu[jumlahTamu].nama = underscoreToSpasi(tamu[jumlahTamu].nama);
			tamu[jumlahTamu].lantai = tamu[jumlahTamu].lantai;
			tamu[jumlahTamu].kamar = tamu[jumlahTamu].kamar;
			tamu[jumlahTamu].lamaInap = tamu[jumlahTamu].lamaInap;
			jumlahTamu++;
		}
		file.close();
		system("pause");
	} else {
		cout << "File tidak ditemukan! Memulai program dengan data kosong\n";
		system("pause");
	}
}

void saveFile() {
    ofstream file("data_tamu.txt", ios::app);

    for(int i = 0; i < jumlahTamu; i++) {
        file << tamu[i].id << " "
            << spasiToUnderscore(tamu[i].nama) << " "
            << tamu[i].lantai << " "
            << tamu[i].kamar << " "
            << tamu[i].lamaInap
            << endl;
    }

    file.close();
    jumlahTamu++;
    cout << "Data berhasil disimpan!\n";
    system("pause");
}