
#include <stdlib.h>
#include <string.h>
#include "ilce.h"

int ilceCounter = 1;
Ilce ilceOlustur(int id, int sehirId, const char *ad)
{
    Ilce i;

    i.base.id = id;
    strncpy(i.base.ad, ad, 49); // ilçe adını kopyalar
    i.base.ad[49] = '\0';
    i.sehirId = sehirId; // hangi şehre ait olduğu bilgisini tutar

    i.mahalleler = NULL; // dinamik mahalle listesi başta boş
    i.mahalleSayisi = 0;

    i.toplamNufus = 0; // ilçenin toplam nüfusu en başta 0

    return i;
}