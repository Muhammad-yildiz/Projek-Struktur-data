#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Struktur untuk menyimpan data barang
struct Item {
    string kodeItem;
    string tanggalMasuk;
};

// Struktur untuk menyimpan data pembeli
struct Pembeli {
    string ktp;
    string waktuKedatangan;
    string kodeItemBarang;
};

// Fungsi untuk mengecek login admin dan mendapatkan nama admin
bool cekLoginAdmin(const string& ktp, const string& password, string& namaAdmin) {
    ifstream fileAdmin("data_ktp.txt"); // Pastikan file ada di direktori yang sama
    if (!fileAdmin.is_open()) {
        cout << "Gagal membuka file data admin.\n";
        return false;
    }

    string fileKTP, filePassword, fileNama;
    while (fileAdmin >> fileKTP >> filePassword >> fileNama) {
        if (fileKTP == ktp && filePassword == password) {
            namaAdmin = fileNama; // Simpan nama admin jika login berhasil
            fileAdmin.close();
            return true;
        }
    }

    fileAdmin.close();
    return false;
}

// Fungsi untuk menampilkan data barang dengan sistem LIFO
void displayLIFO(Item lifoArray[], int count) {
    if (count == 0) {
        cout << "\nInventori kosong.\n";
        return;
    }

    cout << "\nInventori Gudang (LIFO - Last In First Out):\n";
    cout << "Kode Item\tTanggal Masuk\n";
    cout << "-----------------------------\n";

    for (int i = count - 1; i >= 0; --i) {
        cout << lifoArray[i].kodeItem << "\t" << lifoArray[i].tanggalMasuk << "\n";
    }
}

// Fungsi untuk menampilkan data barang dengan sistem FIFO
void displayFIFO(Pembeli queue[], int front, int rear) {
    if (front == rear) {
        cout << "\nAntrian pembeli kosong.\n";
        return;
    }

    cout << "\nDaftar Pembeli (FIFO - First In First Out):\n";
    cout << "KTP\t\tWaktu Kedatangan\tKode Item\n";
    cout << "-----------------------------------------\n";

    for (int i = front; i < rear; ++i) {
        cout << queue[i].ktp << "\t" << queue[i].waktuKedatangan << "\t" << queue[i].kodeItemBarang << "\n";
    }
}

int main() {
    Item lifoArray[100]; // Array untuk menyimpan barang (LIFO)
    Pembeli queue[100];  // Array untuk menyimpan pembeli (FIFO)
    int count = 0;       // Jumlah barang saat ini
    int front = 0, rear = 0; // Indeks untuk antrian pembeli
    int pilihan;

    // Admin Sign In saat program dimulai
    string ktp, password, namaAdmin;
    cout << "Masukkan KTP Admin: ";
    cin >> ktp;
    cout << "Masukkan Password: ";
    cin >> password;

    if (!cekLoginAdmin(ktp, password, namaAdmin)) {
        cout << "Login gagal! Program akan keluar.\n";
        return 0;
    }

    cout << "Login berhasil! Selamat datang, Admin " << namaAdmin << ".\n";

    do {
        // Menu utama
        cout << "\nMenu:\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Jual Barang (FIFO)\n";
        cout << "3. Catat Pembeli\n";
        cout << "4. Cetak Daftar Barang (LIFO)\n";
        cout << "5. Cetak Daftar Pembeli (FIFO)\n";
        cout << "6. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                // Tambah barang
                if (count < 100) {
                    cout << "Masukkan Kode Item: ";
                    cin >> lifoArray[count].kodeItem;
                    cout << "Masukkan Tanggal Masuk (YYYY-MM-DD): ";
                    cin >> lifoArray[count].tanggalMasuk;

                    cout << "Barang ditambahkan: Kode=" << lifoArray[count].kodeItem 
                         << ", Tanggal=" << lifoArray[count].tanggalMasuk << "\n";

                    count++;
                    cout << "Barang berhasil ditambahkan.\n";
                } else {
                    cout << "Gudang penuh, tidak bisa menambah barang lagi.\n";
                }
                break;
            }
            case 2: {
                // Jual barang (FIFO - layani pembeli berdasarkan antrian)
                if (front < rear && count > 0) {
                    cout << "Pembeli dengan KTP=" << queue[front].ktp 
                         << " dilayani, barang kode=" << lifoArray[count - 1].kodeItem << " dijual.\n";

                    cout << "Pembeli dengan KTP " << queue[front].ktp << " dilayani.\n";
                    cout << "Barang dengan kode " << lifoArray[count - 1].kodeItem << " telah dijual.\n";
                    front++;
                    count--;
                } else {
                    cout << "Antrian kosong atau barang tidak tersedia.\n";
                }
                break;
            }
            case 3: {
                // Catat pembeli
                if (rear < 100) {
                    cout << "Masukkan KTP Pembeli: ";
                    cin >> queue[rear].ktp;
                    cout << "Masukkan Waktu Kedatangan (HH:MM): ";
                    cin >> queue[rear].waktuKedatangan;
                    cout << "Masukkan Kode Item Barang: ";
                    cin >> queue[rear].kodeItemBarang;

                    cout << "Pembeli dicatat: KTP=" << queue[rear].ktp 
                         << ", Waktu=" << queue[rear].waktuKedatangan 
                         << ", Kode Barang=" << queue[rear].kodeItemBarang << "\n";

                    rear++;
                    cout << "Pembeli berhasil dicatat.\n";
                } else {
                    cout << "Antrian penuh, tidak bisa menambah pembeli lagi.\n";
                }
                break;
            }
            case 4: {
                // Cetak daftar barang (LIFO)
                displayLIFO(lifoArray, count);
                break;
            }
            case 5: {
                // Cetak daftar pembeli (FIFO)
                displayFIFO(queue, front, rear);
                break;
            }
            case 6:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);

    return 0;
}

