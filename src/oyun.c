
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "oyun.h"
#include "dosyaOkuma.h"
#include "turArttir.h"
#include "seciliSehir.h"
#include "sehirOlustur.h"
#include "yazdir.h"

// oyunun akışını başlatan fonksiyon
void oyun_baslat(char *il, int tur, Oyun *oyun)
{
    // gelen şehir bilgilerine göre şehir yapısını oluşturur
    oyun->sehirler = sehirleri_olustur(il, &oyun->sehirSayisi);
    system("cls");
    printf("Baslangic nufuslar:\n"); // kullanıcının ilk başta girdiği nüfus bilgileri gösterilir

    yazdirSehirler(oyun->sehirler, oyun->sehirSayisi);
    // tur döngüsü başlanır
    for (int t = 1; t <= tur; t++)
    {
        system("cls");
        turArttir(&oyun->sehirler, &oyun->sehirSayisi);
        printf("%d. tur sonrasi nufuslar:\n", t);

        yazdirSehirler(oyun->sehirler, oyun->sehirSayisi);
    }
    seciliSehir(oyun->sehirler, oyun->sehirSayisi);
}