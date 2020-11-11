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

Korisnik nizKorisnika[MAX_KORISNIKA];

void ucitajKorisnike(FILE *f, Korisnik *x);
int UpisiKorisnika(FILE *f,Korisnik *x);
void Meni(FILE *f);
void noviNalog(FILE *f);
void Login(FILE *f);
void brisanjeNaloga(FILE *f,int j);
void izmenaNaloga(FILE *f,int x);
void Logout(FILE *f);
void upisiSve(FILE *f);


#endif // DRIVE_H_INCLUDED
