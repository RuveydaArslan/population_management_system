
#include <stdlib.h>
#include "mahalle.h"

int mahalleCounter = 1;
Mahalle mahalleOlustur(int id, int ilceId, const char *ad)
{
    Mahalle m;

    m.base = yerlesimOlustur(id, ad);
    m.ilceId = ilceId;

    m.kisiler = NULL;
    m.kisiSayisi = 0;

    return m;
}

int mahalleKisiSayisi(Mahalle *m)
{
    return m->kisiSayisi;
}
