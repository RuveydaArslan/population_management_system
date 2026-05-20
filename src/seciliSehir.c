
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "seciliSehir.h"

// kullanıcının detayını görmek istediği şehir bilgisini ekrana yazdıran fonksiyon
void seciliSehir(Sehir *sehirler, int sehirSayisi)
{
    int devam = 1;

    // kullanıcı çıkış yapana kadar devam eden döngü
    while (devam)
    {
        int satir, sutun;

        // kullanıcıdan şehirlerin son durumlarına göre detayını görmek istediği şehrin koordinati alınır
        printf("Satir numarasi (0'dan baslayarak girin): ");
        scanf("%d", &satir);

        printf("Sutun numarasi (0'dan baslayarak girin): ");
        scanf("%d", &sutun);

        int indeks = satir * 5 + sutun;
        // olmayan bir indeks girerse uyarı verilmesi sağlanır ve kontrol edilir
        if (indeks >= sehirSayisi)
        {
            printf("Gecersiz indeks\n");
            return;
        }
        printf("\n\n");
        // seçilen şehre pointer ile erişim (daha hızlı olsun diye)
        Sehir *seciliSehir = &sehirler[indeks];
        int sehirNufus = 0;
        // şehrin toplam nüfusunu hesaplama
        for (int i = 0; i < seciliSehir->ilceSayisi; i++)
        {
            Ilce *ilce = &seciliSehir->ilceler[i];

            for (int j = 0; j < ilce->mahalleSayisi; j++)
            {
                Mahalle *mahalle = &ilce->mahalleler[j];
                sehirNufus += mahalle->kisiSayisi;
            }
        }
        // şehir bilgisini ekrana yazdırır
        printf("Sehir: %s - Nufus: %d\n", seciliSehir->base.ad, sehirNufus);

        for (int i = 0; i < seciliSehir->ilceSayisi; i++)
        {
            Ilce *ilce = &seciliSehir->ilceler[i];
            int ilceNufus = 0;
            // ilçeler döngü ile gezilir ve ilçe bilgileri yazdırılır
            for (int j = 0; j < ilce->mahalleSayisi; j++)
            {
                ilceNufus += ilce->mahalleler[j].kisiSayisi;
            }
            printf("Ilce: %s - Nufus: %d\n", ilce->base.ad, ilceNufus);
            // mahalleler gezilir ve bilgileri yazdırılır
            for (int j = 0; j < ilce->mahalleSayisi; j++)
            {
                Mahalle *mahalle = &ilce->mahalleler[j];

                printf("Mahalle: %s - Nufus: %d\n", mahalle->base.ad, mahalle->kisiSayisi);

                printf("Kisiler: \n");
                // mahallede bulunan kişiler yazdırılır
                for (int k = 0; k < mahalle->kisiSayisi; k++)
                {
                    Kisi *kisi = &mahalle->kisiler[k];

                    printf("\t%d - %s - %d\n", k + 1, kisi->adSoyad, kisi->yas);
                }
            }
        }
        printf("\n");
        // kullanıcıdan devam edip etmeyeceği sorulur
        char cevap;
        printf("Baska sehir bilgisi gormek ister misiniz? (e/h): ");
        scanf(" %c", &cevap);
        // eğer çıkmak isterse döngüden çıkılır
        if (cevap == 'h' || cevap == 'H')
        {
            devam = 0;
        }
    }

    // oyunun tamamen bitmesi için kullanıcıdan işlem yapması istenilir
    printf("Oyunu bitirmek icin bir tusa basin \n");
    getchar();
    getchar();

    printf("Oyun bitti\n");
}