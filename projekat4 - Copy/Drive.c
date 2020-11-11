#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Drive.h"

#define MAX_IME 50
#define MAX_KORISNIKA 1000
extern int brojKorisnika;

void ucitajKorisnike(FILE *f, Korisnik *x)
{
   fscanf(f, "%s%s%s%s%s", x->ime,x->prezime,x->email,x->nickname,x->password1);
}
void Meni(FILE *f)
{
    int i;
    brojKorisnika=0;
    f=fopen("nalozi.txt", "r+");
    while (1)
   {
       ucitajKorisnike(f, &nizKorisnika[brojKorisnika]);
        if(feof(f))
        {
            break;
        }
        brojKorisnika++;


   }
    printf("\nDobrodosli na Drive!\n1. Kreirajte novi nalog\n2. Ulogujte se\nIzaberite jednu od opcija: ");
    scanf("%i",&i);

    switch(i)
    {
    case 1:
        printf("Izabrali ste da napravite novi nalog.");
        noviNalog(f);
        break;
    case 2:
        printf("Izabrali ste da se ulogujete.");
        Login(f);
        break;
    default:
        printf("Pogresan unos!");
        break;

    }
}
void noviNalog(FILE *f)
{
    char p[100],p1[100];
    int isto,pom,duzina,t,g,i,k;
    pom=brojKorisnika++;
    printf("\nMolim va unesite sledece podatke: ");
    printf("\nIme: ");
    fflush(stdin);
    gets(nizKorisnika[pom].ime);
    printf("\nPrezime: ");
    fflush(stdin);
    gets(nizKorisnika[pom].prezime);
email:
    t=0;
    g=0;
    printf("\nEmail: ");
    fflush(stdin);
    gets(p1);
    duzina=strlen(p1);
    for(i=0;i<=duzina;i++)
    {
        if(p1[i]=='@')
        {
            t=1;
        }
        if(t==1 && p1[i]=='.')
        {
            g=1;
        }
    }
    if(t!=1 || g!=1)
    {
        printf("Niste dobro uneli mejl molim vas unesite ga ponovo!");
        goto email;
    }
    for(k=0;k<brojKorisnika;k++)
    {
        if(strcmp(nizKorisnika[k].email,p1)==0)
        {
            printf("Ovaj email je vec iskoristen!");
            goto email;
        }
    }
    strcpy(nizKorisnika[pom].email,p1);
    printf("\nNickname: ");
    fflush(stdin);
    gets(nizKorisnika[pom].nickname);
    printf("\nPassword: ");
    fflush(stdin);
    gets(nizKorisnika[pom].password1);
    printf("\nMolim vas unesite ponovo password: ");
    fflush(stdin);
    gets(p1);
    isto=strcmp(nizKorisnika[pom].password1,p1);
    while(isto!=0)
    {
        printf("Passwordi se ne slazu, molim vas unesite ponove password: ");
        fflush(stdin);
        gets(p1);
        isto=strcmp(nizKorisnika[pom].password1,p1);

    }
    UpisiKorisnika(f,&nizKorisnika[pom]);
    //system("cls");
    printf("Uspesno ste napravili novi nalog!");
    f=fclose(f);
    Meni(f);


    return 0;
}
void Login(FILE *f)
{
     int i,j,isto,l;
     char naziv1[MAX_IME],naziv2[MAX_IME];
ovdje:
    l=0;
     printf("\nMolim vas unesite nickname ili email: ");
     fflush(stdin);
     gets(naziv1);
     for(j=0;j<=brojKorisnika;j++)
     {
         if(strcmp(nizKorisnika[j].nickname,naziv1)==0||strcmp(nizKorisnika[j].email,naziv1)==0)
         {
             l=1;
             printf("\nUnesite password: ");
             fflush(stdin);
             gets(naziv2);
             while(strcmp(nizKorisnika[j].password1,naziv2)!=0)
             {
                 printf("Password nije dobro unet, molim vas unesite ga ponovo: ");
                 fflush(stdin);
                 gets(naziv2);
             }
             printf("1. Izmena Naloga\n2. Brisanje Naloga \n3. Logout\nIzaberite jednu od opcija: ");
             scanf("%i",&i);
             switch(i)
                {
                case 1:
                    izmenaNaloga(f,j);
                    Meni(f);
                    break;
                case 2:
                    brisanjeNaloga(f,j);
                    break;
                case 3:
                    Logout(f);
                    break;
                default:
                    printf("Niste izabrali jednu od opcija!");
                    break;
                }
                break;

         }

     }
     if(l==0)
     {
         printf("\nNe postoji korisnik sa ovim nikom ili emailom, Molim vas probaj te ponovo!\n");
         goto ovdje;
     }


}
void brisanjeNaloga(FILE *f,int j)
{
    int s;
    char pom[100];
    printf("Da li ste sigurni da ocete da izbrisete nalog(unesite da ili ne): ");
    fflush(stdin);
    gets(pom);
    f=fopen("nalozi.txt", "w");
    if(strcmp(pom,"da")==0||strcmp(pom,"Da")==0||strcmp(pom,"dA")==0||strcmp(pom,"DA")==0)
    {
        brojKorisnika--;
        for(s=0;s<=brojKorisnika;s++)
        {
            if(s!=j)
            {
                fprintf(f,"%s %s %s %s %s\n",nizKorisnika[s].ime,nizKorisnika[s].prezime,nizKorisnika[s].email,nizKorisnika[s].nickname,nizKorisnika[s].password1);
            }
        }
        printf("\nUspesno ste obrisali nalog sa nickom %s",nizKorisnika[j].nickname);

    }
    f=fclose(f);
    Meni(f);


}
void izmenaNaloga(FILE *f,int x)
{
   int y,g,t,i,k,duzina;
   char p1[100];
   printf("Izaberite sta zelite da izmenite: \n1. Ime\n2. Prezime\n3. Email\n4. Nickname\n5. Password\nIzaberite jednu od opcija: ");
   scanf("%i",&y);
   f=fopen("nalozi.txt","w");
   printf("%i",brojKorisnika);
   switch(y)
   {
     case 1:
      printf("Molim vas unesite novo ime: ");
      fflush(stdin);
      gets(nizKorisnika[x].ime);
      upisiSve(f);
      break;
     case 2 :
      printf("Molim vas unesite novo prezime: ");
      fflush(stdin);
      gets(nizKorisnika[x].prezime);
      upisiSve(f);
      break;
     case 3:
      printf("Molim vas unesite novi email: ");
email1:
      fflush(stdin);
      t=0;
      g=0;
    gets(p1);
    duzina=strlen(p1);
    for(i=0;i<=duzina;i++)
    {
        if(p1[i]=='@')
        {
            t=1;
        }
        if(t==1 && p1[i]=='.')
        {
            g=1;
        }
    }
    if(t!=1 || g!=1)
    {
        printf("Niste dobro uneli mejl molim vas unesite ga ponovo!");
        goto email1;
    }
    for(k=0;k<brojKorisnika;k++)
    {
        if(strcmp(nizKorisnika[k].email,p1)==0)
        {
            printf("Ovaj email je vec iskoristen!");
            goto email1;
        }
    }
    strcpy(nizKorisnika[x].email,p1);
      upisiSve(f);
      break;
     case 4:
      printf("Molim vas unesite novi nickname: ");
      fflush(stdin);
      gets(nizKorisnika[x].nickname);
      upisiSve(f);
      break;
     case 5:
      printf("Molim vas unesite novi password: ");
      fflush(stdin);
      gets(nizKorisnika[x].password1);
      upisiSve(f);
      break;
   }

}
void Logout(FILE *f)
{
    system("cls");
    printf("Izbrali ste opciju da se izlogujete.\n ");
    f=fclose(f);
    Meni(f);
}
int UpisiKorisnika(FILE *f,Korisnik *x)
{
    fprintf(f,"\n%s %s %s %s %s",x->ime,x->prezime,x->email,x->nickname,x->password1);
    return 0;
}
void upisiSve(FILE *f)
{
    int j;
    f=fopen("nalozi.txt", "w");
    for(j=0;j<=brojKorisnika;j++)
     {
         fprintf(f,"%s %s %s %s %s\n",nizKorisnika[j].ime,nizKorisnika[j].prezime,nizKorisnika[j].email,nizKorisnika[j].nickname,nizKorisnika[j].password1);
     }
     f=fclose(f);
}
