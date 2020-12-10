#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Drive.h"

#define MAX_IME 50
#define MAX_KORISNIKA 1000
int brojKorisnika=0;
int brojFoldera=0;
int brojPodFoldera=0;
int brojFajlova=0;
int main()
{
     FILE *f;
   if((f=fopen("nalozi.txt", "r+"))==NULL)
   {
        printf(" *** Greska prilikom otvaranja fajla!");
        return;
   }
     FILE *f1;
    if((f1=fopen("folderi.txt","r+"))==NULL)
    {
        printf(" *** Greska prilikom otvaranja fajla!");
        return;
    }
    FILE *f2;
    if((f2=fopen("podfolderi.txt","r+"))==NULL)
    {
        printf(" *** Greska prilikom otvaranja fajla!");
        return;
    }
    FILE *f3;
    if((f3=fopen("fajlovi.txt","r+"))==NULL)
    {
        printf(" *** Greska prilikom otvaranja fajla!");
        return;
    }
   Meni(f,f1,f2,f3);


    return 0;
}
