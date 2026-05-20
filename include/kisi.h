
#ifndef KISI_H
#define KISI_H

typedef struct
{
    int id;           // kişinin benzersiz id bilgisi
    int mahalleId;    // bağlı olduğu mahalle id bilgisi
    char adSoyad[50]; // kişinin adı soyadı
    int yas;
} Kisi;
extern int kisiCounter;

Kisi kisiOlustur(int id, int mahalleId, const char *adSoyad, int yas);

#endif