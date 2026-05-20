#ifndef ILCE_H
#define ILCE_H

#include "yerlesim.h" // kalıtım benzetimi yaptığım dosya
#include "mahalle.h"  // mahalle dizisini kullanacağım için ekledim

// yerleşimden türemüş gibi davranan ilce dosyası
typedef struct
{
    Yerlesim base; // ortak özellikleri tutuyor
    int sehirId;   // ilçenin bağlı olduğu şehrin id bilgisi

    Mahalle *mahalleler; // ilçeye bağlı mahallelerin dinamik dizisi
    int mahalleSayisi;   // bu ilçedeki toplam mahalle sayısı
    int toplamNufus;     // ilçenin toplam nüfusu
} Ilce;
extern int ilceCounter;
Ilce ilceOlustur(int id, int sehirId, const char *ad); // yeni bir ilçe nesnesi oluşturuyor

#endif