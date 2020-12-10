#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<conio.h>
#include "Drive.h"

#define MAX_IME 50
#define MAX_KORISNIKA 1000
extern int brojKorisnika;
extern int brojFoldera;
extern int brojPodFoldera;
extern int brojFajlova;
void ucitajFolder(FILE *f1, Folder *x)
{
    int i;
        fscanf(f1, "%s%s%s", x->naziv,x->link,x->kreator);
        fscanf(f1,"%i",&(x->brojAdmina));
        if(x->brojAdmina>0)
        {
            for (i=0;i<x->brojAdmina;i++)
            {
                fscanf(f1," %s ",x->nizAdmina[i].admin);
            }
        }
}
void ucitajKorisnike(FILE *f, Korisnik *x)
{
   fscanf(f, "%s%s%s%s%s", x->ime,x->prezime,x->email,x->nickname,x->password1);
}
void ucitajPodFoldere(FILE *f2,Podfolder *x)
{
    fscanf(f2, "%s%s", x->naziv,x->glavni);

}
void ucitajFajlove(FILE *f3,Fajl *x)
{
    fscanf(f3, "%s%s%s%s", x->naziv,x->ekstenzija,x->datum,x->glavni);
}
void Meni(FILE *f,FILE *f1,FILE *f2,FILE *f3)
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
    brojFoldera=0;
    f1=fopen ("folderi.txt","r+");
    while (feof(f1)==0)
    {
       ucitajFolder(f1, &nizFoldera[brojFoldera]);
        if(feof(f1))
        {
            break;
        }
        brojFoldera++;

    }
    brojPodFoldera=0;
    f2=fopen ("podfolderi.txt","r+");
    while (feof(f2)==0)
    {
       ucitajPodFoldere(f2, &nizPodFoldera[brojPodFoldera]);
        if(feof(f2))
        {
            break;
        }
        brojPodFoldera++;

    }
    brojFajlova=0;
    f3=fopen ("fajlovi.txt","r+");
    while (feof(f3)==0)
    {
       ucitajFajlove(f3, &nizFajlova[brojFajlova]);
        if(feof(f3))
        {
            break;
        }
        brojFajlova++;

    }
    printf("\nDobrodosli na Drive!\n1. Kreirajte novi nalog\n2. Ulogujte se\nIzaberite jednu od opcija: ");
    scanf("%i",&i);

    switch(i)
    {
    case 1:
        printf("Izabrali ste da napravite novi nalog.");
        noviNalog(f,f1,f2,f3);
        break;
    case 2:
        printf("Izabrali ste da se ulogujete.");
        Login(f,f1,f2,f3);
        break;
    default:
        printf("Pogresan unos!");
        break;

    }
}
void noviNalog(FILE *f,FILE *f1,FILE *f2,FILE *f3)
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
    Meni(f,f1,f2,f3);


    return 0;
}
void Login(FILE *f,FILE *f1,FILE *f2,FILE *f3)
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
             printf("1. Izmena Naloga\n2. Brisanje Naloga \n3. Logout\n4. Rad Sa Folderima\nIzaberite jednu od opcija: ");
             scanf("%i",&i);
             switch(i)
                {
                case 1:
                    izmenaNaloga(f,j);
                    Meni(f,f1,f2,f3);
                    break;
                case 2:
                    brisanjeNaloga(f,j,f1,f2,f3);
                    break;
                case 3:
                    Logout(f,f1,f2,f3);
                    break;
                case 4:
                    radSaFolderima(f1,j,f2,f3);
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
void brisanjeNaloga(FILE *f,int j,FILE *f1,FILE *f2,FILE *f3)
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
    Meni(f,f1,f2,f3);


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
void Logout(FILE *f,FILE *f1,FILE *f2,FILE *f3)
{
    system("cls");
    printf("Izbrali ste opciju da se izlogujete.\n ");
    f=fclose(f);
    Meni(f,f1,f2,f3);
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
void radSaFolderima(FILE *f1,int j,FILE *f2,FILE *f3)
{
    int i;
    //system("cls");
    printf("Dobrodosli u rad sa folderima!");
    printf("\n1.Kreirajte folder\n2.Izaberite folder\n3.Pretrazite foldere i fajlove\n4.Izlistaj foldere,podfoldere i fajlove");
    printf("\nMolim vas izaberite jednu od opcija: ");
    scanf("%i",&i);
    switch(i)
    {
    case 1:
        kreirajFolder(f1,j);
        break;
    case 2:
        izlistajFoldere(f1,j,f2,f3);
        break;
    case 3:
        pretraziFoldereFajlove(j,f1,f2,f3);
        break;
    case 4:
        IzlistajSve(f1,f2,f3,j);
        break;
    }
}
void kreirajFolder(FILE *f1,int j)
{
    int pom,i;
    char a[6]={0};
    pom=brojFoldera+1;
    printf("Molim vas unesite ime novog foldera: \n");
    fflush(stdin);
    gets(nizFoldera[pom].naziv);
    slucajniLink(a);
    strcpy(nizFoldera[pom].link,a);
    strcpy(nizFoldera[pom].kreator,nizKorisnika[j].nickname);
    printf("Unesite koliko admina ima folder: \n");
    fflush(stdin);
    scanf("%i",&(nizFoldera[pom].brojAdmina));
    if(nizFoldera[pom].brojAdmina>0)
    {
        for(i=0;i<nizFoldera[pom].brojAdmina;i++)
        {
            printf("Unesite %i. admina: ",i+1);
            fflush(stdin);
            gets(nizFoldera[pom].nizAdmina[i].admin);
        }
    }
    brojFoldera++;
    upisiFoldere(f1);

}
void upisiFoldere(FILE *f1)
{
    int p,k,f,pom;
    f1=fopen("folderi.txt", "w+");
    fprintf(f1,"%s %s %s %i",nizFoldera[0].naziv,nizFoldera[0].link,nizFoldera[0].kreator,nizFoldera[0].brojAdmina);
    if(nizFoldera[0].brojAdmina!=0)
    {
        for(f=0;f<nizFoldera[0].brojAdmina;f++)
        {
            fprintf(f1," %s",nizFoldera[0].nizAdmina[f].admin);
        }
    }
    for(p=1;p<=brojFoldera;p++)
     {
         fprintf(f1,"\n%s %s %s %i",nizFoldera[p].naziv,nizFoldera[p].link,nizFoldera[p].kreator,nizFoldera[p].brojAdmina);
         pom=nizFoldera[p].brojAdmina;
         if(pom>0)
            {
                for(k=0;k<pom;k++)
                    {
                        fprintf(f1," %s",nizFoldera[p].nizAdmina[k].admin);
                    }

            }
     }


     f1=fclose(f1);
}
void slucajniLink(char a[6])
{
    srand(time(NULL));
    //char a[6] = {0};
    for (int i = 0; i < 5; ++i) {
        int r = rand() % 36;
        a[i] = r < 26
               ? 'A' + r
               : '0' + r - 26;
    }
   // puts(a);
}
void izlistajFoldere(FILE *f1,int j,FILE *f2,FILE *f3)
{
    int i,k,u,trenutniFolder,v;
    char pom1[MAX_IME];
    printf("Vi ste kreator sledecih foldera: \n");
    for(i=0;i<=brojFoldera;i++)
    {
        if(strcmp(nizKorisnika[j].nickname,nizFoldera[i].kreator)==0)
        {
            printf("%s\n",nizFoldera[i].naziv);

        }
    }
    printf("a admin sledecih foldera: \n");
    for(i=0;i<=brojFoldera;i++)
    {
        for(k=0;k<=nizFoldera[i].brojAdmina;k++)
        {
            if(strcmp(nizKorisnika[j].nickname,nizFoldera[i].nizAdmina[k].admin)==0)
            {
                printf("%s\n",nizFoldera[i].naziv);
            }
        }
    }
    printf("Izaberite jedan od foldera: \n");
    fflush(stdin);
    gets(pom1);
    for(v=0;v<=brojFoldera;v++)
    {
        if(strcmp(pom1,nizFoldera[v].naziv)==0)
        {
            trenutniFolder=v;
        }
    }
    printf("1. Deljenje Foldera\n2. Izmena Foldera\n3. Brisanje Foldera\n4.Dodaj podfolder\n5. Dodaj fajl\n");
    printf("Izaberite jednu od opcija: ");
    scanf("%i",&u);
    switch(u)
    {
    case 1:
        DeljenjeFoldera(f1,j,trenutniFolder);
        break;
    case 2:
        IzmenaFoldera(f1,j,trenutniFolder);
        break;
    case 3:
        BrisanjeFoldera(f1,j,pom1);
        break;
    case 4:
        DodajPodfolder(f1,f2,j,trenutniFolder);
    case 5:
        DodajFajl(f1,f3,j,trenutniFolder);
    }
}
void BrisanjeFoldera(FILE *f1,int j,char pom1[MAX_IME])
{
    int s,t;
    char temp[100];
    printf("Da li ste sigurni da hocete da izbrisete folder(unesite da ili ne): ");
    fflush(stdin);
    gets(temp);
    f1=fopen("folderi.txt", "w");
    if(strcmp(temp,"da")==0||strcmp(temp,"Da")==0||strcmp(temp,"dA")==0||strcmp(temp,"DA")==0)
    {
        for(s=0;s<=brojFoldera;s++)
        {
            if(strcmp(pom1,nizFoldera[s].naziv)!=0)
            {
                fprintf(f1,"%s %s %s %i",nizFoldera[s].naziv,nizFoldera[s].link,nizFoldera[s].kreator,nizFoldera[s].brojAdmina);
                for(t=0;t<nizFoldera[s].brojAdmina;t++)
                {
                    fprintf(f1," %s ",nizFoldera[s].nizAdmina[t].admin);
                }
                fprintf(f1,"\n");
            }
        }
        printf("\nUspesno ste obrisali folder sa nazivom %s",pom1);

    }
    brojFoldera--;
    f1=fclose(f1);

}
void DeljenjeFoldera(FILE *f1,int j,int trenutniFolder)
{
    int br,trenutniKorisnik,v;
    char pom2[MAX_IME],temp1[MAX_IME]="t";
    printf("Unesite mejlove korisnika sa kojim hocete da delite folder,a slovo t za prekid unosa: ");
    br=nizFoldera[trenutniFolder].brojAdmina;
    do
    {
        fflush(stdin);
        gets(pom2);
        if(strcmp(pom2,temp1)!=0)
        {
            printf("test1");
            for(v=0;v<=brojKorisnika;v++)
            {
                if(strcmp(pom2,nizKorisnika[v].email)==0)
                {
                    trenutniKorisnik=v;
                }
            }
            br++;
            strcpy(nizFoldera[trenutniFolder].nizAdmina[br].admin,nizKorisnika[trenutniKorisnik].nickname);
        }
    }
    while(strcmp(pom2,temp1)!=0);
    nizFoldera[trenutniFolder].brojAdmina=br;
    upisiFoldere(f1);



}
void IzmenaFoldera(FILE *f1,int j,int trenutniFolder)
{
    int w;
    printf("Izaberite sta hocete da izmenite: ");
    printf("\n1. Naziv\n2. Izbaci nekog od admina\n3. Ne deli folder\n");
    scanf("%i",&w);
    switch(w)
    {
    case 1:
        izmeniNazivFoldera(f1,trenutniFolder);
        break;
    case 2:
        IzbaciAdmine(f1,j,trenutniFolder);
        break;
    case 3:
        NedeliFolder(f1,j,trenutniFolder);
        break;
    }
}
void izmeniNazivFoldera(FILE *f1,int trenutniFolder)
{
    char pom5[MAX_IME];
    printf("Unesite novi naziv foldera: ");
    fflush(stdin);
    gets(pom5);
    strcpy(nizFoldera[trenutniFolder].naziv,pom5);
    upisiFoldere(f1);
    printf("\nUspesno ste promenili ime foldera.");
}
void IzbaciAdmine(FILE *f1,int j,int trenutniFolder)
{
    int g,kontrola=0;
    int p,k,pom,f,b;
    char temp1[MAX_IME]="t";
    char pom6[MAX_IME];
    if(strcmp(nizKorisnika[j].nickname,nizFoldera[trenutniFolder].kreator)==0)
    {
        printf("Admini ovog foldera su: ");
        for(g=0;g<nizFoldera[trenutniFolder].brojAdmina;g++)
        {
            printf("%s ",nizFoldera[trenutniFolder].nizAdmina[g].admin);
        }
        printf("\nUnesite admine koje hocete da izbacite(ili slovo t za prekid unosa): ");
        do
        {
            fflush(stdin);
            gets(pom6);
            if(strcmp(pom6,temp1)!=0)
            {
                nizFoldera[trenutniFolder].brojAdmina--;
                for(p=0;p<nizFoldera[trenutniFolder].brojAdmina;p++)
                {
                    if(strcmp(pom6,nizFoldera[trenutniFolder].nizAdmina[p].admin)==0)
                    {
                        for(k=p;k<nizFoldera[trenutniFolder].brojAdmina;k++)
                        {
                            strcpy(nizFoldera[trenutniFolder].nizAdmina[p].admin,nizFoldera[trenutniFolder].nizAdmina[p+1].admin);
                        }
                    }
                }
            }
        }
        while(strcmp(pom6,temp1)!=0);
        upisiFoldere(f1);
    }
    else
    {
        printf("Vi niste kreator ovog foldera i ne mozete da izbacite admine!");
    }
}
void NedeliFolder(FILE *f1,int j,int trenutniFolder)
{
    char pom7[MAX_IME];
    if(strcmp(nizKorisnika[j].nickname,nizFoldera[trenutniFolder].kreator)==0)
    {
        printf("Da li ste sigurni da hocete da izbacite sve admine:\n");
        fflush(stdin);
        gets(pom7);
        if(strcmp(pom7,"da")==0||strcmp(pom7,"Da")==0||strcmp(pom7,"dA")==0||strcmp(pom7,"DA")==0)
        {
            nizFoldera[trenutniFolder].brojAdmina=0;
        }
        upisiFoldere(f1);

    }
    else
    {
        printf("Vi niste kreator ovog foldera i ne mozete da izbacite admine");
    }


}
void DodajPodfolder(FILE *f1,FILE *f2,int j,int trenutniFolder)
{
    int pom9,i,r;
    pom9=brojPodFoldera+1;
    printf("Molim vas unesite ime novog podfoldera: \n");
    fflush(stdin);
    gets(nizPodFoldera[pom9].naziv);
    strcpy(nizPodFoldera[pom9].glavni,nizFoldera[trenutniFolder].naziv);
    brojPodFoldera++;
    f2=fopen("podfolderi.txt", "w+");
    fprintf(f2,"%s %s",nizPodFoldera[0].naziv,nizPodFoldera[0].glavni);
    for(r=1;r<=brojPodFoldera;r++)
    {
            fprintf(f2,"\n%s %s",nizPodFoldera[r].naziv,nizPodFoldera[r].glavni);
    }
    fclose(f2);
}
void DodajFajl(FILE *f1,FILE *f3,int j,int trenutniFolder)
{
    int pom10,i,r;
    char temp10[MAX_IME],str[80];
    pom10=brojFajlova+1;
    printf("Molim vas unesite ime novog fajla: \n");
    fflush(stdin);
    gets(nizFajlova[pom10].naziv);
    printf("Molim vas unesite ekstenziju fajla: \n");
    fflush(stdin);
    gets(nizFajlova[pom10].ekstenzija);

    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    char output1[50];
    char output2[50];
    char output3[50];
    snprintf(output1, 50, "%i",tm.tm_mday);
    snprintf(output2, 50, "%i",tm.tm_mon+1);
    snprintf(output3, 50, "%i",tm.tm_year+1900);
    strcpy(str,output1);
    strcat(str,"/");
    strcat(str,output2);
    strcat(str,"/");
    strcat(str,output3);
    strcpy(nizFajlova[pom10].datum,str);

    strcpy(nizFajlova[pom10].glavni,nizFoldera[trenutniFolder].naziv);
    brojFajlova++;
    f3=fopen("fajlovi.txt", "w+");
    fprintf(f3,"%s %s %s %s",nizFajlova[0].naziv,nizFajlova[0].ekstenzija,nizFajlova[0].datum,nizFajlova[0].glavni);
    for(r=1;r<=brojPodFoldera;r++)
    {
            fprintf(f3,"\n%s %s %s %s",nizFajlova[r].naziv,nizFajlova[r].ekstenzija,nizFajlova[r].datum,nizFajlova[r].glavni);
    }
    fclose(f3);

}
void pretraziFoldereFajlove(int j,FILE *f1,FILE *f2,FILE *f3)
{
    int q,i,k,e,d;
    char pom11[MAX_IME];
    printf("Unesite rec za pretragu: ");
    fflush(stdin);
    gets(pom11);
    printf("Folderi koji sadrze zadatu rec, a vi ste kreator su: \n");
    for(i=0;i<=brojFoldera;i++)
    {
        if(strcmp(nizKorisnika[j].nickname,nizFoldera[i].kreator)==0)
        {
            if(strstr(nizFoldera[i].naziv,pom11)!=0)
            {
                printf("%s\n",nizFoldera[i].naziv);
            }

        }
    }
    printf("Folderi koji sadrze zadatu rec, a vi ste admin su: \n");
    for(i=0;i<=brojFoldera;i++)
    {
        for(k=0;k<=nizFoldera[i].brojAdmina;k++)
        {
            if(strcmp(nizKorisnika[j].nickname,nizFoldera[i].nizAdmina[k].admin)==0)
            {
                if(strstr(nizFoldera[i].naziv,pom11)!=0)
                {
                    printf("%s\n",nizFoldera[i].naziv);
                }
            }
        }
    }

    printf("Podfolderi koji sadrze zadatu rec su: \n");
    for(q=0;q<=brojPodFoldera;q++)
    {
        if(strstr(nizPodFoldera[q].naziv,pom11)!=0)
        {
            for(d=0;d<brojFoldera;d++)
            {
                if(strcmp(nizPodFoldera[q].glavni,nizFoldera[d].naziv)==0)
                {
                    if(strcmp(nizKorisnika[j].nickname,nizFoldera[d].kreator)==0)
                    {
                        printf("%s\n",nizPodFoldera[q].naziv);
                    }
                    for(e=0;e<nizFoldera[d].brojAdmina;e++)
                    {
                        if(strcmp(nizKorisnika[j].nickname,nizFoldera[d].nizAdmina[e].admin)==0)
                           {
                               printf("%s\n",nizPodFoldera[q].naziv);
                           }
                    }
                }
            }
        }
    }
    printf("Fajlovi koji sadrze zadatu rec su: \n");
    for(q=0;q<=brojFajlova;q++)
    {
        if(strstr(nizFajlova[q].naziv,pom11)!=0)
        {
            for(d=0;d<brojFoldera;d++)
            {
                if(strcmp(nizFajlova[q].glavni,nizFoldera[d].naziv)==0)
                {
                    if(strcmp(nizKorisnika[j].nickname,nizFoldera[d].kreator)==0)
                    {
                        printf("%s\n",nizFajlova[q].naziv);
                    }
                    for(e=0;e<nizFoldera[d].brojAdmina;e++)
                    {
                        if(strcmp(nizKorisnika[j].nickname,nizFoldera[d].nizAdmina[e].admin)==0)
                           {
                               printf("%s\n",nizFajlova[q].naziv);
                           }
                    }
                }
            }
        }
    }
}
void IzlistajSve(FILE *f1,FILE *f2,FILE *f3,int j)
{
    int q,e,d,i,k;
    printf("Ovo su svi Folderi, Podfolderi i Fajlovi kojim imate pristup: \n");
    printf("Folderi: \n");
    for(i=0;i<=brojFoldera;i++)
    {
        if(strcmp(nizKorisnika[j].nickname,nizFoldera[i].kreator)==0)
        {
                printf("     %s\n",nizFoldera[i].naziv);
        }
    }
    for(i=0;i<=brojFoldera;i++)
    {
        for(k=0;k<=nizFoldera[i].brojAdmina;k++)
        {
            if(strcmp(nizKorisnika[j].nickname,nizFoldera[i].nizAdmina[k].admin)==0)
            {
                    printf("     %s\n",nizFoldera[i].naziv);
            }
        }
    }
    printf("Podfolderi: \n");
    for(q=0;q<=brojPodFoldera;q++)
    {
            for(d=0;d<brojFoldera;d++)
            {
                if(strcmp(nizPodFoldera[q].glavni,nizFoldera[d].naziv)==0)
                {
                    if(strcmp(nizKorisnika[j].nickname,nizFoldera[d].kreator)==0)
                    {
                        printf("     %s\n",nizPodFoldera[q].naziv);
                    }
                    for(e=0;e<nizFoldera[d].brojAdmina;e++)
                    {
                        if(strcmp(nizKorisnika[j].nickname,nizFoldera[d].nizAdmina[e].admin)==0)
                           {
                               printf("     %s\n",nizPodFoldera[q].naziv);
                           }
                    }
                }

            }
    }
            printf("Fajlovi: \n");
    for(q=0;q<=brojFajlova;q++)
    {
            for(d=0;d<brojFoldera;d++)
            {
                if(strcmp(nizFajlova[q].glavni,nizFoldera[d].naziv)==0)
                {
                    if(strcmp(nizKorisnika[j].nickname,nizFoldera[d].kreator)==0)
                    {
                        printf("     %s\n",nizFajlova[q].naziv);
                    }
                    for(e=0;e<nizFoldera[d].brojAdmina;e++)
                    {
                        if(strcmp(nizKorisnika[j].nickname,nizFoldera[d].nizAdmina[e].admin)==0)
                           {
                               printf("     %s\n",nizFajlova[q].naziv);
                           }
                    }
                }
            }
    }
    radSaFolderima(f1,j,f2,f3);
}
