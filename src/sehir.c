
#include <stdlib.h>
#include "sehir.h"

int sehirCounter = 1; // otomatik olarak artan şehir id bilgisi
// yeni bir şehir nesnesi oluşturulur ve başlangıç değer verilerini atar
Sehir sehir_olustur(int id, const char *ad)
{
    Sehir s;

    s.base = yerlesimOlustur(id, ad); // ortak bilgi olan id ve ad bilgisi atanır
    s.ilceler = NULL;                 // başlangıçta şehirde ilçe yok olarak kabul edilir
    s.ilceSayisi = 0;

    s.mahalleSayisi = 0;
    s.toplamNufus = 0;
    s.sabitMahalleSayisi = 0;
    s.sabitIlceSayisi = 0;

    return s; // oluşturulan şehir verisi geri döndürülür
}