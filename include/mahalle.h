
#ifndef MAHALLE_H
#define MAHALLE_H

#include "yerlesim.h"
#include "kisi.h"

typedef struct
{
   Yerlesim base; // ortak özellikler
   Kisi *kisiler; // mahalledeki kişiler
   int id;
   int kisiSayisi;

   int ilceId; // bağlı olduğu ilçe id bilgisi

} Mahalle;
extern int mahalleCounter;
Mahalle mahalleOlustur(int id, int ilceId, const char *ad);

int mahalleKisiSayisi(Mahalle *m); // mahalledeki kişi sayısını döndürür

#endif
