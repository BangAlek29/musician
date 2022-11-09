#include "header.h"

adr_penyanyi create_musisi(string nama, string ttl){
    //create address buat penyanyi
    adr_penyanyi P = new elm_penyanyi;
    P->nama = nama;
    P->tempatTanggalLahir = ttl;
    P->next = NULL;
    P->list_lagu.first = NULL;
    return P;
}
adr_lagu create_lagu(string nama, string artis, string collab, int tahun_rilis){
    //create address buat lagu
    adr_lagu P = new elm_lagu;
    P->judul = nama;
    P->artis = artis;
    P->collab = collab;
    P->tahunRilis = tahun_rilis;
    P->terhubungArtis;
    P->terhubungCollab;
    P->next = NULL;

    return P;
}
void create_listMusisi(musisi &M){
    //create list musisi
    M.first = NULL;
    M.last = NULL;
}
void create_listLagu(lagu &L){
    //create list lagu
    L.first = NULL;
}

void insert_penyanyi(musisi &M, lagu &L, adr_penyanyi P){
    //memasukkan adr penyanyi ke list musisi
    if(M.first == NULL && M.last == NULL) {
        M.first = P;
        M.last = P;
    } else {
        next(P) = M.first;
        prev(next(P)) = P;
        M.first = P;
    }

    adr_lagu X = L.first;
    while(X != NULL) {
        if ((X->artis == P->nama) && (X->terhubungArtis == false)) {
            add_lagu_to_musisi(M, L, P->nama, X->judul);
            X->terhubungArtis = true;
        } else if ((X->collab == P->nama) && (X->terhubungCollab == false)) {
            add_lagu_to_musisi(M, L, P->nama, X->judul);
            X->terhubungCollab = true;
        }
        X = next(X);
    }
}

void delete_penyanyi(musisi &M, string nama) {
    //menghapus penyanyi dari list
    adr_penyanyi P = find_penyanyi(M, nama);

    if (P == NULL) {
        cout << "Tidak ada penyanyi dengan nama tersebut" << endl;
    } else if (P == M.first) {
        if (next(P) == NULL) {
            M.first = NULL;
            M.last = NULL;
        } else {
            M.first = next(P);
            next(P) = NULL;
            P = NULL;
        }
    } else if (P == M.last) {
        M.last = prev(M.last);
        next(M.last) = NULL;
        P = NULL;
    } else {
        adr_penyanyi Q = M.first;
        while (next(Q) != P) {
            Q = next(Q);
        }
        next(Q) = next(P);
        prev(next(P)) = Q;
        P = NULL;
    }
}

void show_penyanyi(musisi M) {
    //menampilkan list penyanyi
    adr_penyanyi P = M.first;
    if(P == NULL) {
        cout << "DAFTAR PENYANYI KOSONG" << endl;
    } else {
        int i = 1;
        while (P != NULL) {
            cout << "[" << i++ << "]" << endl;
            cout << "Nama Penyanyi        : " << P->nama << endl;
            cout << "Tempat Tanggal Lahir : " << P->tempatTanggalLahir << endl;
            P = next(P);
        }
        cout << endl;
    }
}

adr_penyanyi find_penyanyi(musisi M, string nama) {
    //mencari alamat penyanyi berdasarkan nama
    adr_penyanyi P = M.first;
    if (P == NULL) {
        return NULL;
    } else {
        if (nama == M.first->nama) {
            return M.first;
        } else if (nama == M.last->nama) {
            return M.last;
        } else {
            while (P->nama != nama) {
                P = next(P);
                if (P == NULL) {
                    return NULL;
                }
            }
            return P;
        }
    }
}

void insert_lagu(lagu &L, adr_lagu P){
    if (L.first == NULL) {
        L.first = P;
    } else {
        P->next = L.first;
        L.first = P;
    }
}

void delete_lagu(lagu &L, string judul){
    //menghapus lagu dari list
    adr_lagu P = find_lagu(L, judul);
    adr_lagu Q = L.first;

    if (P == NULL) {
        cout << "Tidak ada lagu dengan judul tersebut" << endl;
    } else if (P == L.first) {
        if (next(P) == NULL) {
            L.first = NULL;
        } else {
            L.first = next(P);
            next(P) = NULL;
        }
    } else if (P != L.first && next(P) == NULL) {
        while (next(Q) != P) {
            Q = next(Q);
        }
        next(Q) = NULL;
    } else {

        while (next(Q) != P) {
            Q = next(Q);
        }
        next(Q) = next(P);
        P = NULL;
    }
}

adr_lagu find_lagu(lagu L, string judul){
    //mencari alamat lagu berdasarkan judul
    adr_lagu P = L.first;

    if (P == NULL) {
        return NULL;
    } else {
        while(judul != P->judul && P != NULL) {
            P = next(P);
        }
        return P;
    }
}


void add_lagu_to_musisi(musisi &M, lagu &L, string nama, string judul){

    adr_penyanyi P = find_penyanyi(M, nama);
    adr_lagu Q = find_lagu(L, judul);

    if(P != NULL) {

        if(Q->artis == P->nama || Q->collab == P->nama) {
            adr_lagu R = create_lagu(Q->judul, Q->artis, Q->collab, Q->tahunRilis);

            insert_lagu(P->list_lagu, R);
        } else {
            Q->terhubungArtis = false;
            Q->terhubungCollab = false;
        }
    } else {
        Q->terhubungArtis = false;
        Q->terhubungCollab = false;
    }
}

void del_lagu(musisi &M, lagu &L, string judul){
    //delete lagu di dalam list dan lagu dalam semua musisi
    adr_lagu P = find_lagu(L, judul);

    if (P == NULL) {
        cout << "Tidak ada lagu dengan judul tersebut" << endl;
    } else {
        adr_penyanyi X = find_penyanyi(M, P->artis);
        //cout << "X : " << X << endl;
        if (X != NULL) {
            //cout << "X tidak NULL" << endl;
            delete_lagu(X->list_lagu, judul);
            //cout << "X selesai delete lagu" << endl;
        }

        if (P->collab != "-") {
            adr_penyanyi Y = find_penyanyi(M, P->collab);
            //cout << "Y : " << Y << endl;
            if (Y != NULL) {
                //cout << "Y tidak NULL" << endl;
                delete_lagu(Y->list_lagu, judul);
                //cout << "Y selesai delete lagu" << endl;
            }
        }
        delete_lagu(L, judul);
    }
    //cout << "SELESAI PENGKONDISIAN" << endl;

}

void show_lagu(musisi M, string nama) {
    //menampilkan lagu penyanyi berdasarkan nama yang dicari
    adr_penyanyi P = find_penyanyi(M, nama);

    if (P == NULL) {
        cout << "Tidak ada Penyanyi didalam list" << endl;
    } else if (P->list_lagu.first == NULL) {
        cout << "tidak ada lagu yang dibuat oleh penyanyi" << endl;
    } else {

        adr_lagu X = P->list_lagu.first;
        int i = 1;
        while (X != NULL) {
            cout << "[" << i++ << "]" << endl;
            cout << "Judul  : " << X->judul << endl;
            cout << "Artis  : " << X->artis << endl;
            cout << "Collab : " << X->collab << endl;
            cout << "Rilis  : " << X->tahunRilis << endl;
            X = next(X);
        }
    }
}


void show_all_lagu(lagu L){
    if (L.first == NULL) {
        cout<<"tidak ada lagu dalam list"<<endl;
    } else {
        adr_lagu X = first(L);
        int i = 1;
        while (X != NULL) {
            cout << "[" << i++ << "]" << endl;
            cout << "Judul  : " << X->judul << endl;
            cout << "Artis  : " << X->artis << endl;
            cout << "Collab : " << X->collab << endl;
            cout << "Rilis  : " << X->tahunRilis << endl;
            X = next(X);
        }
    }
}

void show_semua_musisi_dengan_lagunya(musisi M) {
//show all data, musisi dan lagunya
    adr_penyanyi P = M.first;
    adr_lagu x;
    int i = 1;
    if (P == NULL) {
        cout << "Tidak ada Penyanyi dalam list" << endl;
    } else {
        while (P != NULL) {
            cout<<"["<<i++<<"]"<<endl;
            cout<<"Nama Musisi: "<<P->nama<<endl;
            cout<<"TTL: "<<P->tempatTanggalLahir<<endl;

            cout<<"Lagu yang dibuat:"<<endl;
            x = P->list_lagu.first;
            if (x == NULL) {
                cout<<"   [TIDAK ADA]"<<endl;
            }
            while (x != NULL) {
                cout<<"-"<<x->judul;
                if (x->collab != "-") {
                    if (x->collab == P->nama) {
                        cout<<" By "<<x->artis<<" ft. "<<x->collab<<endl;
                    } else {
                        cout<<" ft. "<<x->collab<<endl;
                    }

                } else {
                    cout<<endl;
                }
                x = x->next;
            }
            P = P->next;
            cout<<endl;
        }
    }
}

void show_lagu_penyanyi_berdasarkan_rilis(musisi M, string nama) {
    string pilihan;
    int rilis;

    adr_penyanyi P = find_penyanyi(M, nama);

    if (P == NULL) {
        cout << "Tidak ada penyanyi tersebut" << endl;
    } else {
        adr_lagu X = P->list_lagu.first;
        adr_lagu Q;

        cout << "Rilis berdasarkan? (terbaru/terlama) : ";
        cin >> pilihan;

        if (X == NULL) {
            cout << "Lagu Kosong" << endl;
        } else if (next(X) == NULL) {
            Q = X;
        } else {
            rilis = X->tahunRilis;

            if (pilihan == "terbaru") {
                while (X != NULL) {
                    if (X->tahunRilis >= rilis) {
                        rilis = X->tahunRilis;
                        Q = X;
                    }
                    X = next(X);
                }
            } else if (pilihan == "terlama") {
                while (X != NULL) {
                    if (X->tahunRilis <= rilis) {
                        rilis = X->tahunRilis;
                        Q = X;
                    }
                    X = next(X);
                }
            }
        }
        cout << "Judul : " << Q->judul << endl;
        cout << "Artis : " << Q->artis << endl;
        cout << "Collab: " << Q->collab << endl;
        cout << "Rilis : " << Q->tahunRilis << endl;
    }
}

int menu(){
    cout<<"--- Menu ---"<<endl<<endl;
    cout<<"Silahkan Pilih Apa yang anda ingin lakukan:"<<endl;
    cout<<"1. Input Penyanyi"<<endl;
    cout<<"2. Input Lagu"<<endl;
    cout<<"3. Delete Penyanyi"<<endl;
    cout<<"4. Delete Lagu"<<endl;
    cout<<"5. Show semua Penyanyi"<<endl;
    cout<<"6. Show semua lagu yang ada di sistem"<<endl;
    cout<<"7. Show lagu yang dibuat oleh seorang penyanyi"<<endl;
    cout<<"8. Show semua penyanyi dengan lagunya"<<endl;
    cout<<"9. Show lagu penyanyi berdasarkan rilisnya"<<endl;
    cout<<"0. Exit"<<endl;
    cout<<endl<<endl;
    cout<<"Input nomor: ";
    int angka;
    cin>>angka;

    return angka;
}



