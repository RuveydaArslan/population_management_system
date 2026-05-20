
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "oyun.h"

int main()
{
    int tur;

    // kullanıcıdan tur sayısı alınır
    printf("Oynanacak tur sayisi: ");
    scanf("%d", &tur);

    // javadaki buffer işlemi gibi temizlik için kullandım
    getchar();

    char il[500];
    // kullanıcıdan iki basamaklı nüfus bilgilerini girmesini istedim
    printf("Nufus sayilari (bosluk olacak sekilde giriniz): ");
    fgets(il, sizeof(il), stdin);

    // satır sonu karakterini temizler
    il[strcspn(il, "\n")] = 0;

    char *parcala[100];
    int dizi[100]; // sayıların tutulduğu dizi tanımladım
    int sayac = 0; // kaç adet nüfus verisi alındığını tutması için tanımladım

    char *token = strtok(il, " "); // boşluklara göre nüfus verisini stringten parçalar

    while (token != NULL)
    {
        int sayi = atoi(token); // stringten inte dönüşüm için kullanılıyor

        // sadece 2 basamaklı nüfus verilerini kabul etmek için kontrol ekledim
        if (sayi >= 10 && sayi <= 99)
        {
            dizi[sayac++] = sayi;
        }
        else
        {
            printf("Hata: sadece iki basamakli sayi giriniz\n");
            return 0;
        }
        token = strtok(NULL, " ");
    }
    char yeniIl[500] = ""; // son haline getirilen verileri ayrı yerde tutmak için tanımladım

    // kontrol edilip ayrılmış sayıları tekrardan string hale getirdim
    for (int i = 0; i < sayac; i++)
    {
        char buf[10];
        sprintf(buf, "%d", dizi[i]); // int tipinden string tipine çevirmek için kullandım
        strcat(yeniIl, buf);         // gelen verileri yeni stringe ekler

        // gelen verileri aralara boşluk gelecek şekilde düzenler
        if (i != sayac - 1)
        {
            strcat(yeniIl, " ");
        }
    }
    // oyun yapısını başlat fonksiyonunu çağırır ve oyun başlar
    Oyun oyun;
    oyun_baslat(yeniIl, tur, &oyun);
    return 0;
}
