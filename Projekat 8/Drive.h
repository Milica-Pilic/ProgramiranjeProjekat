#ifndef DRIVE_H_INCLUDED
#define DRIVE_H_INCLUDED

#define MAX_IME 50
#define MAX_KORISNIKA 1000
typedef struct korisnik{
       char ime[MAX_IME];
       char prezime[MAX_IME];
       char email[MAX_IME];
       char nickname[MAX_IME];
       char password1[MAX_IME];
}Korisnik;
typedef struct admini{
       char admin[MAX_IME];
}Admini;
typedef struct folder{
       char naziv[MAX_IME];
       char link[MAX_IME];
       char kreator[MAX_IME];
       int brojAdmina;
       Admini nizAdmina[MAX_KORISNIKA];
}Folder;
typedef struct podfolder{
       char naziv[MAX_IME];
       char glavni[MAX_IME];;
}Podfolder;
typedef struct fajl{
       char naziv[MAX_IME];
       char ekstenzija[MAX_IME];
       char datum[MAX_IME];
       char glavni[MAX_IME];
}Fajl;

Fajl nizFajlova[MAX_KORISNIKA];
Podfolder nizPodFoldera[MAX_KORISNIKA];
Folder nizFoldera[MAX_KORISNIKA];
Korisnik nizKorisnika[MAX_KORISNIKA];

void ucitajFolder(FILE *f1,Folder *x);
void ucitajKorisnike(FILE *f, Korisnik *x);
int UpisiKorisnika(FILE *f,Korisnik *x);
void slucajniLink();
void Meni(FILE *f,FILE *f1,FILE *f2,FILE *f3);
void noviNalog(FILE *f,FILE *f1,FILE *f2,FILE *f3);
void Login(FILE *f,FILE *f1,FILE *f2,FILE *f3);
void brisanjeNaloga(FILE *f,int j,FILE *f1,FILE *f2,FILE *f3);
void izmenaNaloga(FILE *f,int x);
void Logout(FILE *f,FILE *f1,FILE *f2,FILE *f3);
void upisiSve(FILE *f);
void upisiFoldere(FILE *f1);
void radSaFolderima(FILE *f1,int j,FILE *f2,FILE *f3);
void kreirajFolder(FILE *f1,int j);
void izlistajFoldere(FILE *f1,int j,FILE *f2,FILE *f3);
void BrisanjeFoldera(FILE *f1,int j,char pom1[MAX_IME]);
void DeljenjeFoldera(FILE *f1,int j,int trenutniFolder);
void IzmenaFoldera(FILE *f1,int j,int trenutniFolder);
void izmeniNazivFoldera(FILE *f1,int trenutniFolder);
void IzbaciAdmine(FILE *f1,int j,int trenutniFolder);
void NedeliFolder(FILE *f1,int j,int trenutniFolder);
void ucitajPodFoldere(FILE *f2,Podfolder *x);
void DodajFajl(f1,f3,j,trenutniFolder);
void pretraziFoldereFajlove(int j,FILE *f1,FILE *f2,FILE *f3);
void IzlistajSve(f1,f2,f3,j);


#endif // DRIVE_H_INCLUDED
