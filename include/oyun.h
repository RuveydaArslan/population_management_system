
#ifndef OYUN_H
#define OYUN_H

#include "sehir.h"

typedef struct
{
    Sehir *sehirler; // dinamik şehir dizisi
    int sehirSayisi; // sistemdeki toplam şehir sayısı

} Oyun;

void oyun_baslat(char *il, int tur, Oyun *oyun);

#endif
