#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED


//Muhammad Naufal Abdillah - 1301201586
//Johanes Raphael Nandaputra - 1301204243


#include <iostream>
#include <string>

#define next(P) (P)->next
#define prev(P) (P)->prev
#define first(L) ((L).first)

using namespace std;

typedef struct elm_penyanyi *adr_penyanyi;
typedef struct elm_lagu *adr_lagu;

struct elm_lagu
{
    string judul;
    string artis;
    string collab;
    int tahunRilis;
    bool terhubungArtis;
    bool terhubungCollab;
    adr_lagu next;
};

struct lagu {
    adr_lagu first;
};

struct elm_penyanyi
{
    string nama;
    string tempatTanggalLahir;
    adr_penyanyi next;
    adr_penyanyi prev;
    lagu list_lagu;
};

struct musisi
{
    adr_penyanyi first;
    adr_penyanyi last;
};



adr_penyanyi create_musisi(string nama, string ttl);
adr_lagu create_lagu(string judul, string artis, string collab, int tahun_rilis);
void create_listMusisi(musisi &M);
void create_listLagu(lagu &L);

//buat penyanyi
void insert_penyanyi(musisi &M, lagu &L, adr_penyanyi P);
void delete_penyanyi(musisi &M, string nama);
void show_penyanyi(musisi M);
adr_penyanyi find_penyanyi(musisi M, string nama);


//buat lagu
void insert_lagu(lagu &L, adr_lagu P);
void delete_lagu(lagu &L, string judul);
adr_lagu find_lagu(lagu L, string judul);
void add_lagu_to_musisi(musisi &M, lagu &L, string nama, string judul);
void del_lagu_from_musisi(musisi &M, lagu &L, string nama, string judul);
void show_lagu(musisi M, string nama);
void show_all_lagu(lagu L);

//bersihin relasi
void del_penyanyi(musisi &M, string nama);
void del_lagu(musisi &M, lagu &L, string judul);


//buat menu
int menu();


//tugas
void show_semua_musisi_dengan_lagunya(musisi M);
void show_lagu_penyanyi_berdasarkan_rilis(musisi M, string nama);

#endif // HEADER_H_INCLUDED
