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
    bool status;
};

bool hotel[3][5] = {0};
const int maxTamu = 200;
Tamu tamu[maxTamu];
int jumlahTamu = 0;
int nextId = 1;

void header();
void lihatKamar();
void bookingKamar();
void checkOutKamar();
void cariTamu();
void laporan();
void loadFile();
bool saveFile(Tamu* t);
void rewriteFile();
void totalPendapatan();
int hitungBiaya(int hari);
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
             << "3. Check Out Kamar\n"
             << "4. Cari Data Tamu\n"
             << "5. Laporan Data Tamu (Sorting)\n"
             << "6. Hitung Total Pendapatan\n"
             << "7. Keluar Aplikasi\n"
             << "===================================================\n"
             << "Pilih menu [1-7] : ";

        cin >> pilih;

        switch (pilih) {
            case 1 :
                lihatKamar();
                break;
            case 2 :
                bookingKamar();
                break;
            case 3 :
                checkOutKamar();
                break;
            case 4 :
                cariTamu();
                break;
            case 5 :
                laporan();
                break;
            case 6 :
                totalPendapatan();
                break;
            case 7 :
                cout << "Apakah anda yakin ingin keluar? (y/n) : ";
                cin >> out;
                if (out == 'y' || out == 'Y') {
                    cout << "Terima kasih telah menggunakan program!\n";
                    keluar = true;
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
    string status = (t->status) ? "Aktif/Menginap" : "Sudah Check Out";

    cout << "--------------------------------------------------\n"
		<< "ID          : " << t->id << "\n"
		<< "Nama        : " << t->nama << "\n"
        << "Lantai      : " << t->lantai + 1 << "\n"
        << "Kamar       : " << noKamar << "\n"
        << "Lama Inap   : " << t->lamaInap << "\n"
        << "Status      : " << status << "\n";
}

void lihatKamar(){
    header();
    cout << "\n------------------- Lihat Kamar -------------------\n\n";

    string statusKamar;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 5; j++){
            statusKamar = hotel[i][j] ? "TERISI" : "KOSONG";
            cout << "[Kamar " << i+1 << getAbjadKamar(j) << " " << statusKamar << "]";
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

    inputTamu.id = nextId; 
    cout << "ID : " << inputTamu.id << " (Otomatis)\n";

    cout << "Nama : "; 
    cin.ignore(); 
    getline(cin, inputTamu.nama); 
    
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

        if (hotel[inputTamu.lantai][inputTamu.kamar] == true) {
            cout << "Kamar " << noKamar << " sudah terisi! Silakan pilih yang kosong.\n";
            continue;
        }
        kamarValid = true;

    }while (kamarValid == false);
    
    cout << "Lama Inap : "; cin >> inputTamu.lamaInap;
    inputTamu.status = true;

    if (saveFile(&inputTamu) == true) {
        tamu[jumlahTamu] = inputTamu;
        hotel[inputTamu.lantai][inputTamu.kamar] = 1;
        jumlahTamu++;
        nextId++;
        cout << "Berhasil booking kamar\n";
    } else {
        cout << "Gagal booking kamar\n";
    }

    cout << "--------------------------------------------------\n\n";
    system("pause");
}

/**
 * Update Data
 */
void checkOutKamar() {
    header();
    cout << "\n----------------- Check Out Kamar -----------------\n\n";

    if (jumlahTamu == 0) {
        cout << "Data tamu kosong. Tidak ada yang bisa dicheckout.\n";
        system("pause");
        return;
    }

    int id;
    cout << "Masukkan ID Tamu : ";
    cin >> id;

    bool ditemukan = false;
    for (int i = 0; i < jumlahTamu; i++) {
        if (tamu[i].id == id) {
            ditemukan = true;
            if (!tamu[i].status) {
                cout << "Tamu dengan ID " << id << " sudah check out.\n";
            } else {
                int tagihan = hitungBiaya(tamu[i].lamaInap);

                cout << "\n===================================================\n";
                cout << "                 INVOICE CHECK OUT                 \n";
                cout << "===================================================\n";
                cout << "ID          : " << tamu[i].id << "\n";
                cout << "Nama        : " << tamu[i].nama << "\n";
                cout << "Kamar       : " << tamu[i].lantai + 1 << getAbjadKamar(tamu[i].kamar) << "\n";
                cout << "Lama Inap   : " << tamu[i].lamaInap << " malam\n";
                cout << "Total Biaya : Rp " << tagihan << "\n";
                cout << "===================================================\n";

                tamu[i].status = false; 
                hotel[tamu[i].lantai][tamu[i].kamar] = 0; 
                rewriteFile(); 
                
                cout << "\nCheck Out Berhasil! Kamar sudah dikosongkan.\n";
            }
            break;
        }
    }

    if (!ditemukan) {
        cout << "Tamu dengan ID " << id << " tidak ditemukan.\n";
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
        system("pause");
        return;
    }
    
    int cari;
    cout << "Pilih kategori pencarian:\n"
        << "1. ID\n"
        << "2. Nama\n"
        << "3. Kamar\n"
        << "4. Terakhir Booking\n"
        << "Pilih menu [1-4] : ";
    cin >> cari;

    bool ditemukan = false;
    cout << "\nHasil Pencarian:\n";

    if (cari == 1) { // binary search
        int keyword;
        cout << "Masukkan ID : "; 
        cin >> keyword;
        
        bubbleSort(); 

        int awal = 0;
        int akhir = jumlahTamu - 1;
        int tengah;

        while (awal <= akhir) {
            tengah = (awal + akhir) / 2;
            
            if (tamu[tengah].id == keyword) {
                printData(&tamu[tengah]);
                ditemukan = true;
                break; 
            } else if (tamu[tengah].id < keyword) {
                awal = tengah + 1;
            } else {
                akhir = tengah - 1;
            }
        }
    } else if (cari == 2) { // linear search
        string keyword;
        cout << "Masukkan Nama : "; 
        cin.ignore();
        getline(cin, keyword);
        string upperKeyword = stringToupper(keyword);
        for (int i = 0; i < jumlahTamu; i++) {
            if (stringToupper(tamu[i].nama) == upperKeyword) {
                printData(&tamu[i]);
                ditemukan = true;
            }
        }
    } else if (cari == 3) { // linear search
        string keyword;
        cout << "Masukkan Nomor Kamar (Contoh: 1A) : "; 
        cin >> keyword;
        if (keyword.length() == 2) {
            int lantaiCari = keyword[0] - '1';
            int kamarCari = getIndexKamar(keyword[1]);
            for (int i = 0; i < jumlahTamu; i++) {
                if (tamu[i].lantai == lantaiCari && tamu[i].kamar == kamarCari) {
                    printData(&tamu[i]);
                    ditemukan = true;
                }
            }
        } else {
            cout << "Format kamar salah!\n";
        }
    } else if (cari == 4) {
        printData(&tamu[jumlahTamu - 1]);
        ditemukan = true;
    } else {
        cout << "Pilihan tidak valid!\n";
    }

    if (!ditemukan && cari >= 1 && cari <= 4) {
        cout << "Data tidak ditemukan.\n";
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

    int filter;
    cout << "Pilih filter laporan:\n"
        << "1. Tamu Aktif\n"
        << "2. Tamu Check Out\n"
        << "3. Semua Tamu\n"
        << "Pilih filter [1-3] : ";
    cin >> filter;

    bubbleSort();
    
    int count = 0;
    cout << "\n";
    
    for (int i = 0; i < jumlahTamu; i++) {
        if (filter == 1 && tamu[i].status == true) {
            printData(&tamu[i]);
            count++;
        } else if (filter == 2 && tamu[i].status == false) {
            printData(&tamu[i]);
            count++;
        } else if (filter == 3) {
            printData(&tamu[i]);
            count++;
        }
    }

    if (filter < 1 || filter > 3) {
        cout << "Pilihan tidak valid!\n";
    }

    cout << "--------------------------------------------------\n";
    cout << "Total Tamu Ditampilkan : " << count << " orang" << endl;
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
int hitungBiaya(int hari) {
    int harga = 300000;
    if(hari <= 0)
        return 0;

    return harga + hitungBiaya(hari - 1);
}

void totalPendapatan() {
    header();
    cout << "\n------------------- Total Pendapatan -------------------\n\n";

    if (jumlahTamu == 0) {
        cout << "Data tamu kosong. Belum ada pendapatan\n";
        system("pause");
        return;
    }

    int total = 0;

    cout << "Rincian pendapatan per tamu:\n";
    cout << "--------------------------------------------------\n";

    for(int i = 0; i < jumlahTamu; i++) {
        int biayaTamu = hitungBiaya(tamu[i].lamaInap);
        total += biayaTamu;

        cout << i + 1 << ". " 
            << tamu[i].nama 
            << " - " << tamu[i].lamaInap << " malam : Rp " << biayaTamu << "\n";
    }

    cout << "--------------------------------------------------\n";
    cout << "Total Tamu       : " << jumlahTamu << " orang" << endl;
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
        int maxId = 0;
        while (jumlahTamu < maxTamu && file >> tamu[jumlahTamu].id >> tamu[jumlahTamu].nama >> tamu[jumlahTamu].lantai >> tamu[jumlahTamu].kamar >> tamu[jumlahTamu].lamaInap >> tamu[jumlahTamu].status) {
            
            tamu[jumlahTamu].nama = underscoreToSpasi(tamu[jumlahTamu].nama);
            
            if (tamu[jumlahTamu].status) {
                hotel[tamu[jumlahTamu].lantai][tamu[jumlahTamu].kamar] = 1;
            }
            
            if (tamu[jumlahTamu].id > maxId) {
                maxId = tamu[jumlahTamu].id;
            }

            jumlahTamu++;
        }
        nextId = maxId + 1;
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
             << t->lamaInap << " "
             << t->status
             << endl;
        file.close();
        return true;
    }
}

void rewriteFile() {
    ofstream file("data_tamu.txt", ios::trunc); 

    if(file.is_open()){
        for (int i = 0; i < jumlahTamu; i++) {
            file << tamu[i].id << " "
                 << spasiToUnderscore(tamu[i].nama) << " "
                 << tamu[i].lantai << " "
                 << tamu[i].kamar << " "
                 << tamu[i].lamaInap << " "
                 << tamu[i].status
                 << endl;
        }
        file.close();
    }
}