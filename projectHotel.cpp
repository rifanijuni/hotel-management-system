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

const int maxTamu = 15;
Tamu tamu[maxTamu];
int jumlahTamu = 0;

void header();
void lihatKamar();
void bookingKamar();
void cariTamu();
void laporan();
void loadFile();
bool saveFile(Tamu* t);
void totalPendapatan();
int hitungBiaya(int hari, int harga);
void printData(Tamu* t);
void bubbleSort();
string spasiToUnderscore(string teks);
string underscoreToSpasi(string teks);
string stringToupper(string text);
char getAbjadKamar(int index);
int getIndexKamar(char huruf);

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

string stringToupper(string text){
    for(char& word : text){
        word = (char)toupper(word);
    }
    return text;
}

char getAbjadKamar(int index) {
    string abjad = "ABCDE";
    return abjad[index];
}

int getIndexKamar(char huruf) {
    string abjad = "ABCDE";
    for (int i = 0; i < 5; i++) {
        if (abjad[i] == toupper(huruf)) {
            return i;
        }
    }
    return -1; 
}

void printData(Tamu* t) {
    char noKamar = getAbjadKamar(t->kamar);

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

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 5; j++){
            cout << "[Kamar " << i+1 << getAbjadKamar(j) << " " << hotel[i][j] << "]";
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
    
    if (jumlahTamu >= maxTamu) {
        cout << "Maaf, kapasitas tamu penuh (maksimal " << maxTamu <<" tamu)!\n";
        system("pause");
        return; 
    }

    Tamu inputTamu;
    string noKamar;

    cout << "Data tamu :\n";
    cout << "--------------------------------------------------\n";
    cout << "ID : "; cin >> inputTamu.id;
    cout << "Nama : "; cin.ignore(); getline(cin, inputTamu.nama); 
    
    bool kamarValid = false;
    do {
        cout << "Nomor Kamar (Contoh: 1A): "; 
        cin >> noKamar;

        if (noKamar.length() != 2) {
            cout << "Format salah harus 2 karakter (Contoh: 1A).\n";
            continue; 
        }

        inputTamu.lantai = noKamar[0] - '1';
        inputTamu.kamar = getIndexKamar(noKamar[1]);

        if (inputTamu.lantai < 0 || inputTamu.lantai > 2 || inputTamu.kamar == -1 || toupper(noKamar[1]) > 'E') {
            cout << "Kamar tidak ada! Pilih lantai 1-3 dan abjad A-E.\n";
            continue;
        }

        if (hotel[inputTamu.lantai][inputTamu.kamar] == "TERISI") {
            cout << "Kamar " << noKamar << " sudah terisi! Silakan pilih yang kosong.\n";
            continue;
        }
        kamarValid = true;

    }while (kamarValid == false);
    
    cout << "Lama Inap : "; cin >> inputTamu.lamaInap;

    if (saveFile(&inputTamu) == true) {
        tamu[jumlahTamu] = inputTamu;
        hotel[inputTamu.lantai][inputTamu.kamar] = "TERISI";
        jumlahTamu++;
        cout << "Berhasil booking kamar\n";
    } else {
        cout << "Gagal booking kamar\n";
    }

    cout << "--------------------------------------------------\n\n";
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
        if (stringToupper(tamu[i].nama) == stringToupper(keyword)) {
            cout << "\nData Ditemukan!\n";
            printData(&tamu[i]);
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) {
        cout << "Data dengan nama " << keyword << " tidak ditemukan.\n";
    }
    cout << "--------------------------------------------------\n\n";
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

    cout << "--------------------------------------------------\n";
    cout << "Total Tamu : " << jumlahTamu << " orang" << endl;
    cout << "--------------------------------------------------\n\n";
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
    header();
    cout << "\n------------------- Total Pendapatan -------------------\n\n";

    if (jumlahTamu == 0) {
        cout << "Data tamu kosong. Belum ada pendapatan\n";
        system("pause");
        return;
    }

    int hargaPerMalam = 300000;
    int total = 0;

    cout << "Rincian pendapatan per tamu:\n";
    cout << "--------------------------------------------------\n";

    for(int i = 0; i < jumlahTamu; i++) {
        int biayaTamu = hitungBiaya(tamu[i].lamaInap, hargaPerMalam);
        total += biayaTamu;

        cout << i + 1 << ". " 
            << tamu[i].nama 
            << " - " << tamu[i].lamaInap << " malam : Rp " << biayaTamu << "\n";
    }

    cout << "--------------------------------------------------\n";
    cout << "Total Tamu : " << jumlahTamu << " orang" << endl;
    cout << "Total Pendapatan : Rp " << total << endl;
    cout << "Rata-rata/Tamu   : Rp " << (total / jumlahTamu) << endl;
    cout << "--------------------------------------------------\n\n";
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
            
            tamu[jumlahTamu].nama = underscoreToSpasi(tamu[jumlahTamu].nama);
            hotel[tamu[jumlahTamu].lantai][tamu[jumlahTamu].kamar] = "TERISI";
            
            jumlahTamu++;
        }
		file.close();
	} else {
		cout << "File tidak ditemukan! Memulai program dengan data kosong\n";
	}
    system("pause");
}

bool saveFile(Tamu* t) {
    ofstream file("data_tamu.txt", ios::app);

    if(!file.is_open()){
		return false;
	} else {
        file << t->id << " "
            << spasiToUnderscore(t->nama) << " "
            << t->lantai << " "
            << t->kamar << " "
            << t->lamaInap
            << endl;
        file.close();
        return true;
    }
}