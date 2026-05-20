
#ifndef SEHIR_H
#define SEHIR_H

#include "yerlesim.h" // ortak üst yapı
#include "ilce.h"     // şehir içinde ilce dizisi olduğu için kullanmak için ekledim
typedef struct
{
    Yerlesim base; // ortak bilgiler
    Ilce *ilceler; // şehirdeki ilçeler

    // şehir oluşturduğum zaman kullandığım değişkenler
    int ilceSayisi;
    int mahalleSayisi;
    int kisiMahalle;
    int toplamNufus;
    int sabitMahalleSayisi;
    int sabitIlceSayisi;

} Sehir;
extern int sehirCounter;
Sehir sehir_olustur(int id, const char *ad);

#endif