
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sehir.h"
#include "ilce.h"
#include "mahalle.h"
#include "kisi.h"

// dosydan satır satır okuyarak sadece isim kısmını almaya çalıştım
void dosyadanIsimCek(FILE *fp, char *hedef)
{
    if (fgets(hedef, 50, fp))
    {
        // yeni satır karakterini temizler
        hedef[strcspn(hedef, "\r\n")] = 0;
    }
    else
    {
        // eğer dosya biterse boş isim yazması yerine bilinmeyen yazmasını sağladım
        strcpy(hedef, "Bilinmeyen");
    }
}
// kullanıcının girdiği sayılara göre tüm şehir yapısını kurar
Sehir *sehirleri_olustur(const char *il_input, int *sehirSayisiOutput)
{
    // tüm veri dosylarını açar

    FILE *fSehir = fopen("data/sehir.txt", "r");
    FILE *fIlce = fopen("data/ilce.txt", "r");
    FILE *fMahalle = fopen("data/mahalle.txt", "r");
    FILE *fKisi = fopen("data/kisiler.txt", "r");
    // kullanıcının inputu kopyalanır
    // eğer strtok kullansaydım orijinali bozmuş olurdum
    char tempInput[500];
    strcpy(tempInput, il_input);

    int sehirAdedi = 0;
    Sehir *sehirler = NULL;
    // input boşluklarına göre parçalar
    char *token = strtok(tempInput, " ");

    while (token != NULL)
    {
        // string ifadeyi integer ifade çevirdim
        int sayi = atoi(token);

        int birler = sayi % 10; // mahalle sayısının bilgisi
        int onlar = sayi / 10;  // ilçe sayısının bilgisi
        int sabitIlceSayisi = onlar;
        int sabitMahalleSayisi = birler;

        if (sabitMahalleSayisi == 0)
        { // eğer mahalle sayısı 0 ise ilçe sayısı kadar mahallenin olmasını sağladım
            sabitMahalleSayisi = sabitIlceSayisi;
        }
        else if (sabitMahalleSayisi % sabitIlceSayisi != 0)
        { // mahalle sayısı ilçelere eşit paylaştırılamıyorsa düzeltme işlemi
            // mahalle sayısını ilçe sayısından mahalle sayısının ilçe sayısına bölümünden kalan değerinden çıkararak artacak sayıyı hesapladım
            int artiralacakMahalleSayisi = sabitIlceSayisi - (sabitMahalleSayisi % sabitIlceSayisi);
            // nüfusa hesaplanan artırılacak sayısının toplayıp ilçe sayısına baktım ve eğer ilçe sayısı bozuluyorsa azaltma işlemi yaptım
            if (((sayi + artiralacakMahalleSayisi) / 10) != sabitIlceSayisi)
            {
                sabitMahalleSayisi -= (sabitMahalleSayisi % sabitIlceSayisi);
            }
            else
            {
                sabitMahalleSayisi += artiralacakMahalleSayisi;
            }
        }
        // uygulanan kurallar sonunda son toplam nüfusu hesapladım
        int toplamNufus = sabitIlceSayisi * 10 + sabitMahalleSayisi;
        // eğer son hesaplanan toplam nüfus verisi mahalle sayısına tam bir şekilde paylaştırılamıyorsa toplam nüfus verisi tekrardan düzenlenir
        if (toplamNufus % sabitMahalleSayisi != 0)
        {
            int artiralacakNufus = sabitMahalleSayisi - (toplamNufus % sabitMahalleSayisi);
            toplamNufus += artiralacakNufus;
        }
        // her mahallede kaç kişi olduğunu hesaplayıp tuttum
        int kisiMahalle = toplamNufus / sabitMahalleSayisi;
        // her ilçede kaç mahalle olduğunu hesaplayıp tuttum
        int mahallePerIlce = sabitMahalleSayisi / sabitIlceSayisi;
        // şehir listesini dinamik bir şekilde büyüttüm
        sehirler = realloc(sehirler, (sehirAdedi + 1) * sizeof(Sehir));
        char sehirAdi[50]; // şehir adını dosyadan almaya çalıştım
        dosyadanIsimCek(fSehir, sehirAdi);
        // şehir oluşturma işlemi gerçekleşiyor
        Sehir s = sehir_olustur(sehirCounter++, sehirAdi);
        // yukarıda hesapladığım değerlerini tur arttir fonksiyonundan çağırmak için tuttum
        s.kisiMahalle = kisiMahalle;
        s.toplamNufus = toplamNufus;
        s.sabitMahalleSayisi = sabitMahalleSayisi;
        s.sabitIlceSayisi = sabitIlceSayisi;
        s.ilceSayisi = sabitIlceSayisi;
        // ilçe dizisi oluşturuluyor
        s.ilceler = (Ilce *)malloc(sabitIlceSayisi * sizeof(Ilce));
        // ilçeler oluşturuluyor
        for (int i = 0; i < sabitIlceSayisi; i++)
        {
            char ilceAdi[50];
            dosyadanIsimCek(fIlce, ilceAdi);
            s.ilceler[i] = ilceOlustur(ilceCounter++, s.base.id, ilceAdi);
            s.ilceler[i].mahalleSayisi = mahallePerIlce; // ilçeye mahalle sayısı atanır
            // mahalle dizisi oluşturuluyor
            s.ilceler[i].mahalleler = (Mahalle *)malloc(mahallePerIlce * sizeof(Mahalle));
            // mahalleler oluşturuluyor
            for (int j = 0; j < mahallePerIlce; j++)
            {
                char mahalleAdi[50];
                dosyadanIsimCek(fMahalle, mahalleAdi);
                s.ilceler[i].mahalleler[j] = mahalleOlustur(mahalleCounter++, s.ilceler[i].base.id, mahalleAdi);

                Mahalle *m = &s.ilceler[i].mahalleler[j];
                m->kisiSayisi = kisiMahalle;                             // mahalleye kişi sayısı atanır
                m->kisiler = (Kisi *)malloc(kisiMahalle * sizeof(Kisi)); // kişi dizisi oluşturuluyor
                                                                         // kişiler oluşturuluyor
                for (int k = 0; k < kisiMahalle; k++)
                {
                    char kisiAd[50];
                    dosyadanIsimCek(fKisi, kisiAd);
                    // 0 ile 50 arası yaşlar rastgele oluşturulup veriliyor
                    m->kisiler[k] = kisiOlustur(kisiCounter++, m->base.id, kisiAd, rand() % 51);
                }
            }
        }
        // oluşturulan şehir listeye eklenir
        sehirler[sehirAdedi++] = s;
        token = strtok(NULL, " ");
    }
    *sehirSayisiOutput = sehirAdedi;
    fclose(fSehir);
    fclose(fIlce);
    fclose(fMahalle);
    fclose(fKisi);
    return sehirler;
}