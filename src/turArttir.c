
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "turArttir.h"
#include "sehirOlustur.h"
#include "yazdir.h"
#include "kisi.h"

// verilen bir şehrin toplam nüfusunu hesaplamak için kullandığım fonksiyon
// ilçeye bağlı mahalledeki kisi sayılarını topluyor
int hesaplaNufus(Sehir *sehir)
{
    int toplam = 0;

    // güvenlik kontrolü yaparak başlıyorum
    if (sehir == NULL || sehir->ilceler == NULL)
        return 0;

    for (int i = 0; i < sehir->ilceSayisi; i++)
    {
        Ilce *ilce = &sehir->ilceler[i];
        // eğer mahalle yoksa geçilir
        if (ilce->mahalleler == NULL)
            continue;
        // mahalleleri gezer
        for (int j = 0; j < ilce->mahalleSayisi; j++)
        {
            Mahalle *m = &ilce->mahalleler[j];
            // mahalledeki kisi sayısını ekleyerek kaydeder
            toplam += m->kisiSayisi;
        }
    }
    return toplam;
}
// yeni bir şehir ekler
// dinamik dizi kullanarak büyüttüm
void sehirEkle(Sehir **sehirler, int *sehirSayisi, Sehir yeniSehir)
{
    *sehirler = realloc(*sehirler, (*sehirSayisi + 1) * sizeof(Sehir));
    (*sehirler)[*sehirSayisi] = yeniSehir;
    (*sehirSayisi)++;
}
// her turda nüfus artışı yapılır yaşlar artılır ve şehir bölünme kontrolü sağlanır
void turArttir(Sehir **sehirlerPtr, int *sehirSayisi)
{
    Sehir *sehirler = *sehirlerPtr;

    // isim üretimi için dosyları açıyorum
    FILE *fSehir = fopen("data/sehir.txt", "r");
    FILE *fIlce = fopen("data/ilce.txt", "r");
    FILE *fMahalle = fopen("data/mahalle.txt", "r");
    FILE *fKisi = fopen("data/kisiler.txt", "r");

    // nüfus artışı döngüsü
    for (int s = 0; s < *sehirSayisi; s++)
    {
        Sehir *sehir = &sehirler[s];
        // son toplam nüfus verisinin onlar ve birler basamağını alıyorum
        int onlar = (sehir->toplamNufus / 10) % 10;
        int birler = sehir->toplamNufus % 10;
        // birler ve onlar basamağını toplayarak artış oranını buluyorum
        int artisOran = onlar + birler;
        // eğer birler ve onlar basamak toplamı 0 ise artış oranını 1e eşitliyorum
        if (artisOran == 0)
            artisOran = 1;
        // ilçeleri geziyor
        for (int i = 0; i < sehir->ilceSayisi; i++)
        {
            Ilce *ilce = &sehir->ilceler[i];
            // mahalleleri geziyor
            for (int j = 0; j < ilce->mahalleSayisi; j++)
            {
                Mahalle *mahalle = &ilce->mahalleler[j];
                // mahallelerdeki kişi sayısını alıyorum
                int mevcut = mahalle->kisiSayisi;
                // kurala göre hesaplanan artış oranını hesaplayarak eklenmesi gerek nüfus sayısını hesaplıyor
                int eklenecek = (artisOran - 1) * mevcut;

                if (eklenecek > 0)
                {
                    // kişi listesi dinamik bir şekilde büyütülüyor
                    mahalle->kisiler = realloc(mahalle->kisiler, (mevcut + eklenecek) * sizeof(Kisi));
                    // yeni kişiler oluşturuluyor
                    for (int k = 0; k < eklenecek; k++)
                    {
                        char isim[50];
                        dosyadanIsimCek(fKisi, isim);
                        mahalle->kisiler[mahalle->kisiSayisi].id = kisiCounter++;
                        mahalle->kisiler[mahalle->kisiSayisi].mahalleId = mahalle->base.id;
                        // isimler kopyalanıyor
                        strncpy(mahalle->kisiler[mahalle->kisiSayisi].adSoyad, isim, 50);
                        // 0 ile 50 arasında rastgele yaş veriliyor
                        mahalle->kisiler[mahalle->kisiSayisi].yas = rand() % 51;
                        mahalle->kisiSayisi++;
                    }
                }
                // her turda kişilerin yaşlarını 1 artıyor
                for (int k = 0; k < mahalle->kisiSayisi; k++)
                {
                    mahalle->kisiler[k].yas++;
                }
            }
        }
        // şehrin toplam nüfusu güncelleniyor
        sehir->toplamNufus = hesaplaNufus(sehir);
    }
    //printf("----- Artis sonrasindaki nufuslar -----\n");
    //yazdirSehirler(sehirler, *sehirSayisi);

    int ilkSehirSayisi = *sehirSayisi;
    int herhangiBirBolunmeOlduMu = 0;

    for (int s = 0; s < ilkSehirSayisi; s++)
    {
        Sehir *eskiSehir = &sehirler[s];

        // eğer artış sonrasında nüfus sayısı 4 basamaklı olursa bölünme kuralı başlar
        if (eskiSehir->toplamNufus >= 1000)
        {
            herhangiBirBolunmeOlduMu = 1;
            // eğer 1den fazla ilçe varsa ilçe tabanlı bölünme gerçekleşir
            if (eskiSehir->ilceSayisi >= 2)
            {
                int tasinacakIlceSayisi = eskiSehir->ilceSayisi / 2;
                char yeniSehirAdi[50];
                dosyadanIsimCek(fSehir, yeniSehirAdi);

                Sehir yeniSehir = sehir_olustur(sehirCounter++, yeniSehirAdi);
                yeniSehir.ilceler = malloc(tasinacakIlceSayisi * sizeof(Ilce));
                yeniSehir.ilceSayisi = tasinacakIlceSayisi;
                // ilçelerin yarısı yeni bir şehre taşınır
                for (int i = 0; i < tasinacakIlceSayisi; i++)
                {
                    Ilce tasinanIlce = eskiSehir->ilceler[eskiSehir->ilceSayisi - 1];
                    tasinanIlce.sehirId = yeniSehir.base.id;
                    yeniSehir.ilceler[i] = tasinanIlce;
                    eskiSehir->ilceSayisi--;
                }
                // nüfuslar taşınma sonrasında hesapla fonksiyonu ile hesaplanıp güncellenir
                eskiSehir->toplamNufus = hesaplaNufus(eskiSehir);
                yeniSehir.toplamNufus = hesaplaNufus(&yeniSehir);
                sehirEkle(sehirlerPtr, sehirSayisi, yeniSehir);
                sehirler = *sehirlerPtr;
            }
            // eğer sadece 1 ilçe varsa mahalle tabanlı bölünme gerçeklenir
            else if (eskiSehir->ilceSayisi == 1)
            {
                Ilce *tekIlce = &eskiSehir->ilceler[0];
                // eğer mahalle sayısı 2den fazla ise çalışır
                if (tekIlce->mahalleSayisi >= 2)
                {
                    // mahalle sayısı yarıya bölünür yeni şehir oluşturulur ve dosyadan yeni isim verilir
                    int tasinacakMahalle = tekIlce->mahalleSayisi / 2;
                    char yeniSehirAdi[50], yeniIlceAdi[50];
                    dosyadanIsimCek(fSehir, yeniSehirAdi);
                    dosyadanIsimCek(fIlce, yeniIlceAdi);

                    Sehir yeniSehir = sehir_olustur(sehirCounter++, yeniSehirAdi);
                    yeniSehir.ilceSayisi = 1;
                    yeniSehir.ilceler = malloc(sizeof(Ilce));

                    Ilce yeniIlce = ilceOlustur(ilceCounter++, yeniSehir.base.id, yeniIlceAdi);
                    yeniIlce.mahalleSayisi = tasinacakMahalle;
                    yeniIlce.mahalleler = malloc(tasinacakMahalle * sizeof(Mahalle));

                    // mahallelerin yarısı taşınır
                    for (int i = 0; i < tasinacakMahalle; i++)
                    {
                        Mahalle m = tekIlce->mahalleler[tekIlce->mahalleSayisi - 1];
                        m.ilceId = yeniIlce.base.id;
                        yeniIlce.mahalleler[i] = m;
                        tekIlce->mahalleSayisi--;
                    }
                    yeniSehir.ilceler[0] = yeniIlce;
                    eskiSehir->toplamNufus = hesaplaNufus(eskiSehir);
                    yeniSehir.toplamNufus = hesaplaNufus(&yeniSehir);
                    sehirEkle(sehirlerPtr, sehirSayisi, yeniSehir);
                    sehirler = *sehirlerPtr;
                }
                // eğer mahalle sayısı 1 ise bu sefer kişi bölünmesi gerçekleşir
                else if (tekIlce->mahalleSayisi == 1)
                {
                    Mahalle *eskiMahalle = &tekIlce->mahalleler[0];
                    int yarisi = eskiMahalle->kisiSayisi / 2;

                    char yeniSehirAdi[50], yeniIlceAdi[50], yeniMahalleAdi[50];
                    dosyadanIsimCek(fSehir, yeniSehirAdi);
                    dosyadanIsimCek(fIlce, yeniIlceAdi);
                    dosyadanIsimCek(fMahalle, yeniMahalleAdi);

                    Sehir yeniSehir = sehir_olustur(sehirCounter++, yeniSehirAdi);
                    yeniSehir.ilceSayisi = 1;
                    yeniSehir.ilceler = malloc(sizeof(Ilce));

                    Ilce yeniIlce = ilceOlustur(ilceCounter++, yeniSehir.base.id, yeniIlceAdi);
                    yeniIlce.mahalleSayisi = 1;
                    yeniIlce.mahalleler = malloc(sizeof(Mahalle));

                    Mahalle yeniMahalle = mahalleOlustur(mahalleCounter++, yeniIlce.base.id, yeniMahalleAdi);
                    yeniMahalle.kisiSayisi = yarisi;
                    yeniMahalle.kisiler = malloc(yarisi * sizeof(Kisi));
                    // kişilerin yarısı taşınır
                    for (int i = 0; i < yarisi; i++)
                    {
                        Kisi k = eskiMahalle->kisiler[eskiMahalle->kisiSayisi - 1];
                        k.mahalleId = yeniMahalle.base.id;
                        yeniMahalle.kisiler[i] = k;
                        eskiMahalle->kisiSayisi--;
                    }
                    yeniIlce.mahalleler[0] = yeniMahalle;
                    yeniSehir.ilceler[0] = yeniIlce;

                    eskiSehir->toplamNufus = hesaplaNufus(eskiSehir);
                    yeniSehir.toplamNufus = hesaplaNufus(&yeniSehir);
                    sehirEkle(sehirlerPtr, sehirSayisi, yeniSehir);
                    sehirler = *sehirlerPtr;
                }
            }
        }
    }
    // eğer bölünme işlemi olduysa ekrana yazdırılır
    if (herhangiBirBolunmeOlduMu)
    {
        printf("----- Bolunme sonrasindaki nufuslar -----\n");
        yazdirSehirler(*sehirlerPtr, *sehirSayisi);
    }
    // döngü sonrasında dosyalar kapanır
    fclose(fSehir);
    fclose(fIlce);
    fclose(fMahalle);
    fclose(fKisi);
}