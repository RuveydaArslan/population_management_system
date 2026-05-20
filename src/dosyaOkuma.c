
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dosyaOkuma.h"
#include "ilce.h"
#include "mahalle.h"
#include "kisi.h"
#include "sehir.h"

Sehir sehir_olustur(int id, const char *ad);
Ilce ilceOlustur(int id, int sehirId, const char *ad);
Mahalle mahalleOlustur(int id, int ilceId, const char *ad);
Kisi kisiOlustur(int id, int mahalleId, const char *adSoyad, int yas);

// şehir verilerini dosyadan okur ve dinamik bir şekilde oluştururur
static Sehir *sehirleriOku(int *sehirSayisi)
{
    FILE *fp = fopen("data/sehir.txt", "r");

    if (!fp)
        return NULL; // eğer dosya açılmazsa null döner

    Sehir *sehirler = NULL;
    *sehirSayisi = 0;

    char satir[100];

    // her satırı okur ve şehir oluşturur
    while (fgets(satir, sizeof(satir), fp))
    {
        int id;
        char ad[50];

        sscanf(satir, "%d|%[^\\n]", &id, ad);

        Sehir s = sehir_olustur(id, ad);

        sehirler = realloc(sehirler, (*sehirSayisi + 1) * sizeof(Sehir)); // dinamik şehir listesi büyüyor
        sehirler[(*sehirSayisi)++] = s;
    }
    fclose(fp);
    return sehirler;
}
// ilçeleri okur ve şehre bağlar sehrin idsi ile ilişki sağlanır
static void ilceleriOku(Sehir *sehirler, int sehirSayisi)
{
    FILE *fp = fopen("data/ilce.txt", "r");
    if (!fp)
        return;

    char satir[100];

    while (fgets(satir, sizeof(satir), fp))
    {
        int id, sehirId;
        char ad[50];

        sscanf(satir, "%d|%d|%[^\\n]", &id, &sehirId, ad);

        Ilce ilce = ilceOlustur(id, sehirId, ad);

        // bağlı olduğu şehri döngü sayesinde bulur ve ilçeyi şehre ekler
        for (int i = 0; i < sehirSayisi; i++)
        {
            if (sehirler[i].base.id == sehirId)
            {
                sehirler[i].ilceler = realloc(
                    sehirler[i].ilceler,
                    (sehirler[i].ilceSayisi + 1) * sizeof(Ilce));
                sehirler[i].ilceler[sehirler[i].ilceSayisi++] = ilce;
                break;
            }
        }
    }
    fclose(fp);
}
// mahalleleri okur ve ilçeye bağlar ilce id bilgisi ile bağlantı sağlanır
static void mahalleleriOku(Sehir *sehirler, int sehirSayisi)
{
    FILE *fp = fopen("data/mahalle.txt", "r");
    if (!fp)
        return;

    char satir[100];

    while (fgets(satir, sizeof(satir), fp))
    {
        int id, ilceId;
        char ad[50];

        sscanf(satir, "%d|%d|%[^\n]", &id, &ilceId, ad);

        Mahalle mahalle = mahalleOlustur(id, ilceId, ad);

        // ilçeyi bularak mahalleyi ekler
        for (int i = 0; i < sehirSayisi; i++)
        {
            for (int j = 0; j < sehirler[i].ilceSayisi; j++)
            {
                if (sehirler[i].ilceler[j].base.id == ilceId)
                {
                    Ilce *ilce = &sehirler[i].ilceler[j];

                    ilce->mahalleler = realloc(
                        ilce->mahalleler,
                        (ilce->mahalleSayisi + 1) * sizeof(Mahalle));
                    ilce->mahalleler[ilce->mahalleSayisi++] = mahalle;
                    goto next_line; // ilçeyi bulunca donguden çıkar
                }
            }
        }
    next_line:;
    }
    fclose(fp);
}
// kişileri okur ve mahallelere paylaştırır mahalle id bilgisi ile yapar
static void kisileriOku(Sehir *sehirler, int sehirSayisi)
{
    FILE *fp = fopen("data/kisiler.txt", "r");
    if (!fp)
        return;

    char satir[200];
    while (fgets(satir, sizeof(satir), fp))
    {
        int id, mahalleId, yas;
        char adSoyad[100];

        // sadece isim bilgisini almaya çalıştım ama bütün satırı tek bir string olarak gördüğü için almadı
        if (sscanf(satir, "%d|%d|%[^|]|%d", &id, &mahalleId, adSoyad, &yas) != 4)
        {
            continue;
        }

        Kisi kisi = kisiOlustur(kisiCounter++, mahalleId, adSoyad, yas);

        for (int i = 0; i < sehirSayisi; i++)
        {
            for (int j = 0; j < sehirler[i].ilceSayisi; j++)
            {
                for (int k = 0; k < sehirler[i].ilceler[j].mahalleSayisi; k++)
                {
                    Mahalle *m = &sehirler[i].ilceler[j].mahalleler[k];

                    if (m->id == mahalleId)
                    {
                        m->kisiler = realloc(
                            m->kisiler,
                            (m->kisiSayisi + 1) * sizeof(Kisi));
                        m->kisiler[m->kisiSayisi++] = kisi;
                        goto next_kisi; // kişi bulunca döngüden çıkar
                    }
                }
            }
        }
    next_kisi:;
    }
    fclose(fp);
}

// tüm dosyaları okuyarak ve şehir yapısını kuran fonksiyon
Sehir *sistemi_kur(int *sehirSayisi)
{
    Sehir *sehirler = sehirleriOku(sehirSayisi);

    if (sehirler == NULL || *sehirSayisi == 0)
    {
        printf("Sehir verisi okunamadi\n");
        return NULL;
    }
    ilceleriOku(sehirler, *sehirSayisi);
    mahalleleriOku(sehirler, *sehirSayisi);
    kisileriOku(sehirler, *sehirSayisi);

    return sehirler;
}