#include <iostream>
#include <stack>
#include <string>
#include <iomanip>

using namespace std;

struct Item {
    string kodeItem;
    string tanggalMasuk;
};

void displayLIFO(stack<Item> lifoStack) {
    cout << "\nInventori Gudang (LIFO - Last In First Out):\n";
    cout << left << setw(15) << "Kode Item" << setw(20) << "Tanggal Masuk" << endl;
    while (!lifoStack.empty()) {
        Item item = lifoStack.top();
        lifoStack.pop();
        cout << left << setw(15) << item.kodeItem << setw(20) << item.tanggalMasuk << endl;
    }
}

int main() {
    stack<Item> lifoStack;
    int pilihan;

    do {
        cout << "\nMenu Inventori Gudang:\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan LIFO\n";
        cout << "3. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            Item item;
            cout << "Masukkan Kode Item: ";
            cin >> item.kodeItem;
            cout << "Masukkan Tanggal Masuk (YYYY-MM-DD): ";
            cin >> item.tanggalMasuk;

            lifoStack.push(item);

            cout << "Barang berhasil ditambahkan.\n";
        } else if (pilihan == 2) {
            if (lifoStack.empty()) {
                cout << "Tidak ada barang dalam inventori (LIFO).\n";
            } else {
                displayLIFO(lifoStack);
            }
        } else if (pilihan != 3) {
            cout << "Pilihan tidak valid. Coba lagi.\n";
        }

    } while (pilihan != 3);

    cout << "Program selesai.\n";
    return 0;
}
