
#include <string.h>
#include "kisi.h"

int kisiCounter = 1;
// parametreler ile yeni bir kisi oluşturur
Kisi kisiOlustur(int id, int mahalleId, const char *adSoyad, int yas)
{
    Kisi k;

    k.id = id;
    k.mahalleId = mahalleId;
    k.yas = yas;

    strcpy(k.adSoyad, adSoyad); // isim kopyalama

    return k;
}