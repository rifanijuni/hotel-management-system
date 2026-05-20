#include <iostream>
#include <fstream>
using namespace std;

struct Tamu {
    string nama;
    int id;
    int lantai;
    int kamar;
    int lamaInap;
};

void lihatKamar();
void bookingKamar();
void cariTamu();
void laporan();
void totalPendapatan();

int main() {
    int pilih;
    char out;
    bool keluar = false;

    do {
        system("cls");

        cout << "===================================================\n"
             << "              HOTEL MANAGEMENT SYSTEM              \n"
             << "===================================================\n"
             << "1. Lihat Status Kamar\n"
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