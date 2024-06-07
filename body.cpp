#include "header.h"
#include <vector>
#include <algorithm>

adr_penyanyi create_musisi(string nama, string ttl) {
    adr_penyanyi P = new elm_penyanyi;
    P->nama = nama;
    P->tempatTanggalLahir = ttl;
    P->next = NULL;
    P->list_lagu.first = NULL;
    return P;
}

adr_lagu create_lagu(string nama, string artis, string collab, int tahun_rilis) {
    adr_lagu P = new elm_lagu;
    P->judul = nama;
    P->artis = artis;
    P->collab = collab;
    P->tahunRilis = tahun_rilis;
    P->terhubungArtis = false;
    P->terhubungCollab = false;
    P->next = NULL;

    return P;
}

void create_listMusisi(musisi &M) {
    M.first = NULL;
    M.last = NULL;
}

void create_listLagu(lagu &L) {
    L.first = NULL;
}

void insert_penyanyi(musisi &M, lagu &L, adr_penyanyi P) {
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

void insert_lagu(lagu &L, adr_lagu P) {
    if (L.first == NULL) {
        L.first = P;
    } else {
        P->next = L.first;
        L.first = P;
    }
}

void delete_lagu(lagu &L, string judul) {
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

adr_lagu find_lagu(lagu L, string judul) {
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

void add_lagu_to_musisi(musisi &M, lagu &L, string nama, string judul) {
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

void del_lagu_from_musisi(musisi &M, lagu &L, string nama, string judul) {
    adr_penyanyi P = find_penyanyi(M, nama);
    adr_lagu Q = find_lagu(P->list_lagu, judul);

    if (P != NULL) {
        delete_lagu(P->list_lagu, judul);
    }
}

void show_lagu(musisi M, string nama) {
    adr_penyanyi P = find_penyanyi(M, nama);

    if (P == NULL) {
        cout << "Penyanyi tidak ditemukan!" << endl;
    } else {
        adr_lagu Q = P->list_lagu.first;
        if (Q == NULL) {
            cout << "DAFTAR LAGU KOSONG" << endl;
        } else {
            while (Q != NULL) {
                cout << "Judul  : " << Q->judul << endl;
                cout << "Artis  : " << Q->artis << endl;
                cout << "Collab : " << Q->collab << endl;
                cout << "Tahun  : " << Q->tahunRilis << endl;
                cout << endl;
                Q = next(Q);
            }
        }
    }
}

void show_all_lagu(lagu L) {
    adr_lagu P = L.first;

    if (P == NULL) {
        cout << "DAFTAR LAGU KOSONG" << endl;
    } else {
        while (P != NULL) {
            cout << "Judul  : " << P->judul << endl;
            cout << "Artis  : " << P->artis << endl;
            cout << "Collab : " << P->collab << endl;
            cout << "Tahun  : " << P->tahunRilis << endl;
            cout << endl;
            P = next(P);
        }
    }
}

void del_penyanyi(musisi &M, string nama) {
    delete_penyanyi(M, nama);
}

void del_lagu(musisi &M, lagu &L, string judul) {
    delete_lagu(L, judul);

    adr_penyanyi P = M.first;

    while(P != NULL) {
        adr_lagu Q = P->list_lagu.first;
        if(Q->judul == judul) {
            delete_lagu(P->list_lagu, judul);
        }
        P = next(P);
    }
}

void show_semua_musisi_dengan_lagunya(musisi M) {
    adr_penyanyi P = M.first;
    if (P == NULL) {
        cout << "DAFTAR PENYANYI KOSONG" << endl;
    } else {
        int i = 1;
        while (P != NULL) {
            cout << "[" << i++ << "]" << endl;
            cout << "Nama Penyanyi        : " << P->nama << endl;
            cout << "Tempat Tanggal Lahir : " << P->tempatTanggalLahir << endl;

            adr_lagu Q = P->list_lagu.first;
            if (Q != NULL) {
                cout << "Daftar Lagu:" << endl;
                while (Q != NULL) {
                    cout << "  Judul: " << Q->judul << endl;
                    cout << "  Artis: " << Q->artis << endl;
                    cout << "  Collab: " << Q->collab << endl;
                    cout << "  Tahun Rilis: " << Q->tahunRilis << endl;
                    Q = next(Q);
                }
            } else {
                cout << "  Tidak ada lagu yang terhubung" << endl;
            }

            cout << endl;
            P = next(P);
        }
    }
}

void show_lagu_penyanyi_berdasarkan_rilis(musisi M, string nama) {
    adr_penyanyi P = find_penyanyi(M, nama);

    if (P == NULL) {
        cout << "Penyanyi tidak ditemukan!" << endl;
    } else {
        adr_lagu Q = P->list_lagu.first;
        if (Q == NULL) {
            cout << "DAFTAR LAGU KOSONG" << endl;
        } else {
            vector<adr_lagu> lagu_list;
            while (Q != NULL) {
                lagu_list.push_back(Q);
                Q = next(Q);
            }
            sort(lagu_list.begin(), lagu_list.end(), [](adr_lagu a, adr_lagu b) {
                return a->tahunRilis < b->tahunRilis;
            });

            for (adr_lagu lagu : lagu_list) {
                cout << "Judul  : " << lagu->judul << endl;
                cout << "Artis  : " << lagu->artis << endl;
                cout << "Collab : " << lagu->collab << endl;
                cout << "Tahun  : " << lagu->tahunRilis << endl;
                cout << endl;
            }
        }
    }
}

void save_data_to_file(musisi M, lagu L, const string &filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    adr_penyanyi P = M.first;
    while (P != NULL) {
        file << "Penyanyi:" << endl;
        file << P->nama << endl;
        file << P->tempatTanggalLahir << endl;
        
        adr_lagu Q = P->list_lagu.first;
        while (Q != NULL) {
            file << "Lagu:" << endl;
            file << Q->judul << endl;
            file << Q->artis << endl;
            file << Q->collab << endl;
            file << Q->tahunRilis << endl;
            Q = next(Q);
        }
        P = next(P);
    }

    file << "Lagu Lainnya:" << endl;
    adr_lagu R = L.first;
    while (R != NULL) {
        file << R->judul << endl;
        file << R->artis << endl;
        file << R->collab << endl;
        file << R->tahunRilis << endl;
        R = next(R);
    }

    file.close();
}


void load_data_from_file(musisi &M, lagu &L, const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    create_listMusisi(M);
    create_listLagu(L);

    string line;
    adr_penyanyi current_penyanyi = NULL;

    while (getline(file, line)) {
        if (line == "Penyanyi:") {
            string nama, ttl;
            getline(file, nama);
            getline(file, ttl);
            current_penyanyi = create_musisi(nama, ttl);
            insert_penyanyi(M, L, current_penyanyi);
        } else if (line == "Lagu:") {
            string judul, artis, collab;
            int tahunRilis;
            getline(file, judul);
            getline(file, artis);
            getline(file, collab);
            file >> tahunRilis;
            file.ignore();

            adr_lagu new_lagu = create_lagu(judul, artis, collab, tahunRilis);
            if (current_penyanyi != NULL) {
                insert_lagu(current_penyanyi->list_lagu, new_lagu);
            }
        } else if (line == "Lagu Lainnya:") {
            while (getline(file, line)) {
                string judul = line;
                string artis, collab;
                int tahunRilis;
                getline(file, artis);
                getline(file, collab);
                file >> tahunRilis;
                file.ignore();

                adr_lagu new_lagu = create_lagu(judul, artis, collab, tahunRilis);
                insert_lagu(L, new_lagu);
            }
        }
    }

    file.close();
}

