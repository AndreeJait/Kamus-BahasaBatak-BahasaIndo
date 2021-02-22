#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct kamus
{
    char *batak;
    char *indo;
    char *text;
    char *hasil;
};

void inputdata(struct kamus kamus, char *bahasaIndo, char *BahasaBatak);
char *bacadata(char *pathdata);
void lihatdaftar(char *kamus1, char *kamus2);
void terjemahkan(struct kamus kamus);
void inputhasil(struct kamus kamus, char *text);
char *cek(struct kamus kamus, char *text);
void inputtanda(struct kamus kamus, char tanda);
char * abc(char *a);
int main()
{
    struct kamus kamus;
    kamus.batak = "kata_batak.txt";
    kamus.indo = "kata_indonesia.txt";
    int pil;
str:
{
    printf("\n");
    printf("1. Input Kedalam Kamus\n");
    printf("2. Terjemahan\n");
    printf("3. List Kamus\n");
    printf("4. Exit\n");
    printf("Masukkan Pilihan Anda : ");
    scanf("%d", &pil);

    if (pil == 4)
    {
        printf("\n");
        printf("++++++++++++++++++++++++++\n");
        printf("++++++ Terima KASIH ++++++\n");
        printf("++++++++++++++++++++++++++\n");
    }
    if (pil == 1)
    {
    input:
    {
        printf("\n");
        char batak[50], indo[50];
        printf("---- Input Data ----\n");
        printf("Masukkan Bahasa Batak : ");
        scanf("%s", &batak);
        printf("Masukkan Arti Kata dalam Bahasa Indonesia : ");
        scanf("%s", &indo);
        inputdata(kamus, indo, batak);
        printf("\n");
    }
        char re[5];
        printf("Input Data Lagi (y/t) ?");
        scanf("%s", &re);
        if (strcmp(re, "y") == 0)
            goto input;
        else
            goto str;
    }
    else if (pil == 2)
    {
        kamus.text = "fileindo.txt";
        kamus.hasil = "indonesia_ke_batak.txt";
        terjemahkan(kamus);
        goto str;
    }
    else if (pil == 3)
    {
        char *kamus1 = bacadata(kamus.batak);
        char *kamus2 = bacadata(kamus.indo);
        printf("\n\n");
        lihatdaftar(kamus1, kamus2);
        goto str;
    }
}
    getch();
    return 0;
}

// input data kedalam kamus
void inputdata(struct kamus kamus, char *bahasaIndo, char *BahasaBatak)
{
    FILE *f;
    FILE *fd;
    if ((f = fopen(kamus.batak, "a")) == NULL)
    {
        puts("Unable to open database.");
        exit(1);
    }
    else if ((fd = fopen(kamus.indo, "a")) == NULL)
    {
        puts("Unable to open database.");
        exit(1);
    }
    else
    {
        strcat(bahasaIndo, "|");
        strcat(BahasaBatak, "|");
        fprintf(f, "%s", BahasaBatak);
        fprintf(fd, "%s", bahasaIndo);
        puts("*--------------------------------*");
        puts("| DATA ANDA BERHASIL DITAMBAHKAN |");
        puts("*--------------------------------*");
    }
    fclose(f);
    fclose(fd);
}
void inputhasil(struct kamus kamus, char *text)
{
    FILE *f;
    if ((f = fopen(kamus.hasil, "a")) == NULL)
    {
        puts("Unable to open database.");
        exit(1);
    }
    else
    {
        fprintf(f, "%s", text);
    }
    fclose(f);
}
char *bacadata(char *pathdata)
{
    int sizepertama = 1;
    char *arrData = (char *)malloc(sizepertama * sizeof(char));
    int c;
    FILE *f;

    if ((f = fopen(pathdata, "r")) == NULL)
    {
        puts("Tidak dapat membuka data.");
        exit(1);
    }
    else
    {
        do
        {
            c = fgetc(f);
            if (feof(f))
                break;
            else
            {
                arrData[sizepertama - 1] = c;
                sizepertama += 1;
                arrData = (char *)realloc(arrData, sizepertama);
            }
        } while (1);
    }
    fclose(f);
    return arrData;
}

void terjemahkan(struct kamus kamus)
{
    char *batak = bacadata(kamus.batak);
    char *indo = bacadata(kamus.indo);
    char *datatext = bacadata(kamus.text);

    char *token_sharp = ".";
    char *temp;
    char *rest = datatext;
    while ((temp = strtok_r(rest, token_sharp, &rest)))
    {
        char *token_pipe = " ";
        char *satu;
        char *last = temp;
        int zz = 0;
        while ((satu = strtok_r(last, token_pipe, &last)))
        {
            zz = 1;
            char *text = NULL;
            inputhasil(kamus, cek(kamus, satu));
            if (strchr(satu, ','))
            {
                inputtanda(kamus, ',');
            }
            else if (strchr(satu, '?'))
            {
                inputtanda(kamus, '?');
            }
            else if (strchr(satu, '!'))
            {
                inputtanda(kamus, '!');
            }
            else if (strchr(satu, '-'))
            {
                inputtanda(kamus, '-');
            }
            else{
                inputtanda(kamus,' ');
            }
        }
        if (zz == 1)
        {
            inputtanda(kamus, '.');
        }
    }
    printf("Berhasil Menerjemahkan\n");
}
void lihatdaftar(char *kamus1, char *kamus2)
{
    char *token = "|";
    puts("Bahas Indonesia\t| Bahasa Batak");
    char *satu;
    char *dua;
    char *restsatu = kamus1;
    char *restdua = kamus2;

    while ((satu = strtok_r(restsatu, token, &restsatu)) && (dua = strtok_r(restdua, token, &restdua)))
    {
        char *batak = NULL;
        char *indo = NULL;
        if (batak == NULL)
        {
            int len = strlen(satu);
            batak = (char *)malloc(len * sizeof(char));
            strcpy(batak, satu);
        }
        if (indo == NULL)
        {
            int len = strlen(dua);
            indo = (char *)malloc(len * sizeof(char));
            strcpy(indo, dua);
        }
        if (batak != NULL && indo != NULL)
        {
            printf("%s\t| %s\n", indo, batak);
        }
    }

    printf("\n\n");
}
char *cek(struct kamus kamus, char *text)
{
    char *token = "|";
    char *satu;
    char *dua;
    char *restsatu = bacadata(kamus.batak);
    char *restdua = bacadata(kamus.indo);
    
    while ((satu = strtok_r(restsatu, token, &restsatu)) && (dua = strtok_r(restdua, token, &restdua)))
    {
        char *batak = NULL;
        char *indo = NULL;
        if (strlen(text) == 2)
        {
            if (strcmp(dua, abc(text)) == 0)
            {
                return satu;
                break;
            }
        }
        else
        {
            if (strstr(abc(text), abc(dua)))
            {
                return satu;
                break;
            }
        }
    }
}
void inputtanda(struct kamus kamus, char tanda)
{
    FILE *f;
    if ((f = fopen(kamus.hasil, "a")) == NULL)
    {
        puts("Unable to open database.");
        exit(1);
    }
    else
    {
        fprintf(f, "%c ", tanda);
    }
    fclose(f);
}
char * abc(char *a)
{
    int i;
    for(i=0;i<15;i++)
   {
        if(a[i]>=65&&a[i]<=90)
       {
            a[i]=a[i]+32;
       }
   }
   return a;
}