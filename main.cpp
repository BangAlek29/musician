#include "header.h"


int main()
{
    //list tetap
    musisi M;
    lagu L;

    //create list
    create_listMusisi(M);
    create_listLagu(L);

    //define adr
    adr_penyanyi P;
    adr_lagu X;

    //buat input penyanyi
    std::string nama;
    string TTL;

    //buat input lagu
    string judul;
    string pembuat1;
    string pembuat2;
    int tahun_rilis;
    string iscollab;

    //buat ulang
    string answer;


    int pilihan = menu();

    while (pilihan > 0 && pilihan <= 9){
        switch (pilihan) {
    case 1:
        std::cin.ignore();
        cout<<"Masukkan nama Penyanyi: ";
        std::getline(cin, nama);


        cout<<"Masukkan Tempat dan tanggal lahir Penyanyi: ";
        std::getline(cin, TTL);

        P = create_musisi(nama, TTL);
        insert_penyanyi(M, L, P);

        cout<<"Kembali ke menu utama? (Y/N): ";
            cin>>answer;
            cout<<endl;
            if (answer == "Y") {
                pilihan = menu();
                break;
            } else{
                break;
            }

    case 2:
        cout<<"Masukkan Judul lagu: ";
        std::cin.ignore();
        std::getline(cin, judul);

        cout<<"Masukkan nama pembuat: ";
        std::getline(cin, pembuat1);

        cout<<"Ada Collab?(Y/N): ";
        cin>>iscollab;

        if (iscollab == "Y") {
            cout<<"Masukkan nama collab: ";
            std::cin.ignore();
            std::getline(cin, pembuat2);
        } else {
            pembuat2 = "-";
        }

        cout<<"Masukkan Tahun Rilis: ";
        cin>>tahun_rilis;

        X = create_lagu(judul, pembuat1, pembuat2, tahun_rilis);
        insert_lagu(L, X);


        add_lagu_to_musisi(M, L, pembuat1, judul);


        if (iscollab == "Y") {
            add_lagu_to_musisi(M, L, pembuat2, judul);
        }

        cout<<"Kembali ke menu utama? (Y/N) :";
            cin>>answer;
            cout<<endl;
            if (answer == "Y") {
                pilihan = menu();
                break;
            } else{
                break;
            }

    case 3:
        cout<<"Masukkan nama penyanyi yang ingin di delete: ";
        std::cin.ignore();
        std::getline(cin, nama);

        delete_penyanyi(M, nama);

        cout<<"Kembali ke menu utama? (Y/N) :";
            cin>>answer;
            cout<<endl;
            if (answer == "Y") {
                pilihan = menu();
                break;
            } else{
                break;
            }

    case 4:
        cout<<"Masukkan Judul Lagu yang ingin di delete: ";
        std::cin.ignore();
        std::getline(cin, judul);

        del_lagu(M, L, judul);

        cout<<"Kembali ke menu utama? (Y/N) :";
            cin>>answer;
            cout<<endl;
            if (answer == "Y") {
                pilihan = menu();
                break;
            } else{
                break;
            }

    case 5:
        show_penyanyi(M);

        cout<<"Kembali ke menu utama? (Y/N) :";
            cin>>answer;
            cout<<endl;
            if (answer == "Y") {
                pilihan = menu();
                break;
            } else{
                break;
            }

    case 6:
        show_all_lagu(L);

        cout<<"Kembali ke menu utama? (Y/N) :";
            cin>>answer;
            cout<<endl;
            if (answer == "Y") {
                pilihan = menu();
                break;
            } else{
                break;
            }

    case 7:
        cout<<"Masukkan nama penyanyi: ";
        std::cin.ignore();
        std::getline(cin, nama);

        show_lagu(M, nama);

        cout<<"Kembali ke menu utama? (Y/N) :";
            cin>>answer;
            cout<<endl;
            if (answer == "Y") {
                pilihan = menu();
                break;
            } else{
                break;
            }

    case 8:
        cout<<"list musisi dan lagunya: "<<endl;
        show_semua_musisi_dengan_lagunya(M);

        cout<<"Kembali ke menu utama? (Y/N) :";
            cin>>answer;
            cout<<endl;
            if (answer == "Y") {
                pilihan = menu();
                break;
            } else{
                break;
            }

    case 9:
        cout<<"Masukkan nama penyanyi: ";
        std::cin.ignore();
        std::getline(cin, nama);

        show_lagu_penyanyi_berdasarkan_rilis(M, nama);

        cout<<"Kembali ke menu utama? (Y/N) :";
        cin>>answer;
        cout<<endl;
            if (answer == "Y") {
                pilihan = menu();
                break;
            } else{
                break;
            }
        }
    }

    return 0;
}
