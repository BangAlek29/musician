#include "header.h"

int main() {
    musisi M;
    lagu L;
    create_listMusisi(M);
    create_listLagu(L);

    int choice;
    do {
            cout << "1. Add Penyanyi" << endl;
            cout << "2. Add Lagu" << endl;
            cout << "3. Display Penyanyi" << endl;
            cout << "4. Display Lagu" << endl;
            cout << "5. Display All" << endl;
            cout << "6. Delete Lagu" << endl;
            cout << "7. Save Data to File" << endl;
            cout << "8. Load Data from File" << endl;
            cout << "9. Exit" << endl;
            cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: {
                // Add penyanyi
                string nama, ttl;
                cout << "Nama: ";
                cin >> nama;
                cout << "Tempat Tanggal Lahir: ";
                cin >> ttl;
                insert_penyanyi(M, L, create_musisi(nama, ttl));
                break;
            }
            case 2: {
                // Add lagu
                string judul, artis, collab;
                int tahun;
                cout << "Judul: ";
                cin >> judul;
                cout << "Artis: ";
                cin >> artis;
                cout << "Collab: ";
                cin >> collab;
                cout << "Tahun Rilis: ";
                cin >> tahun;
                insert_lagu(L, create_lagu(judul, artis, collab, tahun));
                break;
            }
            case 3: {
                // Delete penyanyi
                string nama;
                cout << "Nama: ";
                cin >> nama;
                del_penyanyi(M, nama);
                break;
            }
            case 4: {
                // Delete lagu
                string judul;
                cout << "Judul: ";
                cin >> judul;
                del_lagu(M, L, judul);
                break;
            }
            case 5: {
                // Show all penyanyi with their lagu
                show_semua_musisi_dengan_lagunya(M);
                break;
            }
            case 6: {
                // Show all lagu
                show_all_lagu(L);
                break;
            }
            case 7: {
                // Save to file
                string filename;
                cout << "Nama file: ";
                cin >> filename;
                save_data_to_file(M, L, filename);
                break;
            }
            case 8: {
                // Load from file
                string filename;
                cout << "Nama file: ";
                cin >> filename;
                load_data_from_file(M, L, filename);
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
