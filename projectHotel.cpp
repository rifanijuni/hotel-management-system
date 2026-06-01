#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
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
void printData(Tamu* t);
void bubbleSort();
string spasiToUnderscore(string teks);
string underscoreToSpasi(string teks);
string stringToupper(string text);

int main() {
    system("cls");
    loadFile();

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

void printData(Tamu* t) {
    string abjadKamar = "ABCDE";
    string noKamar;
    for (int i = 0; i < 5; i++){
        noKamar = abjadKamar[t->kamar];
    }

    cout << "--------------------------------------------------\n"
		<< "ID          : " << t->id << "\n"
		<< "Nama        : " << t->nama << "\n"
        << "Lantai      : " << t->lantai << "\n"
        << "Kamar       : " << noKamar << "\n"
        << "Lama Inap   : " << t->lamaInap << "\n";
}

void lihatKamar(){
    header();
    cout << "\n------------------- Lihat Kamar -------------------\n\n";

    string abjadKamar = "ABCDE";

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 5; j++){
            cout << "[Kamar " << i+1 << abjadKamar[j] << " " << hotel[i][j] << "]";
        }
        cout << endl;
    }

    cout << endl;
    system("pause");
}

/**
 * Input Data
 */
void bookingKamar(){
    header();
    cout << "\n------------------- Booking Kamar -------------------\n\n";
    
    Tamu inputTamu;
    string noKamar;

    cout << "Data tamu :\n";
    cout << "ID : "; cin >> inputTamu.id;
    cout << "Nama : "; cin.ignore(); getline(cin, inputTamu.nama); 
    cout << "Nomor Kamar : "; cin >> noKamar;
    cout << "Lama Inap : "; cin >> inputTamu.lamaInap;

    inputTamu.lantai = noKamar[0] - '1';

    string abjadKamar = "ABCDE";
    for (int i = 0; i < 5; i++){
        if (abjadKamar[i] == toupper(noKamar[1])){
            inputTamu.kamar = i;
        }
    }

    tamu[jumlahTamu] = inputTamu;
    hotel[inputTamu.lantai][inputTamu.kamar] = "TERISI";
    jumlahTamu++;

    cout << "Berhasil booking kamar\n";
    system("pause");
}

/**
 * Searching Data
 */
void cariTamu(){
    header();
    cout << "\n------------------- Cari Data Tamu -------------------\n\n";

    if (jumlahTamu == 0) {
        cout << "Data tamu kosong. Tidak ada data yang bisa dicari. Silakan booking kamar\n";
        return;
    }
    
	string keyword;
	cout << "Masukkan nama :"; 
    cin.ignore(); 
    getline(cin, keyword);
	
	cout << "\nHasil Pencarian:\n";
	
	bool ditemukan = false;
    for (int i = 0; i < jumlahTamu; i++) {
        if (tamu[i].nama == keyword) {
            cout << "\nData Ditemukan!\n";
            printData(&tamu[i]);
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) {
        cout << "Data dengan nama " << keyword << " tidak ditemukan.\n";
    }
    system("pause");
}



/**
 * Sorting Data
 */
void laporan(){
    header();
    cout << "\n------------------- Laporan Data Tamu -------------------\n\n";
    
    if (jumlahTamu == 0) {
        cout << "Data tamu kosong.\n";
        system("pause");
        return;
    }

    bubbleSort();
    for (int i = 0; i < jumlahTamu; i++) {
        printData(&tamu[i]);
    }
    
    totalPendapatan();
    system("pause");
}

void bubbleSort() {
    for (int i = 0; i < jumlahTamu - 1; i++) {
        for (int j = 0; j < jumlahTamu - i - 1; j++) {
            if (tamu[j].id > tamu[j + 1].id) {
                Tamu temp = tamu[j];
                tamu[j] = tamu[j + 1];
                tamu[j + 1] = temp;
            }
        }
    }
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
    cout << "--------------------------------------------------\n\n";

    int hargaPerMalam = 300000;
    int total = 0;

    for(int i = 0; i < jumlahTamu; i++) {
        total += hitungBiaya(tamu[i].lamaInap, hargaPerMalam);
    }

    cout << "Total Tamu : " << jumlahTamu << " orang" << endl;
    cout << "Total Pendapatan : Rp " << total << endl;
    cout << "--------------------------------------------------\n\n";
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