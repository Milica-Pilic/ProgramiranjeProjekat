#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Drive.h"

#define MAX_IME 50
#define MAX_KORISNIKA 1000
int brojKorisnika=0;
int main()
{
     FILE *f;
   if((f=fopen("nalozi.txt", "r+"))==NULL)
   {
        printf(" *** Greska prilikom otvaranja fajla!");
        return;
   }
   Meni(f);


    return 0;
}
