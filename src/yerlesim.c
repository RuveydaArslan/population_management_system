
#include <string.h>
#include "yerlesim.h"
// yerleşim nesnesi oluşturulur
Yerlesim yerlesimOlustur(int id, const char *ad)
{
    Yerlesim y;
    y.id = id;
    strncpy(y.ad, ad, 49); // gelen ismi güvenli bir şekilde kopyalamaişlemi yapar
    y.ad[49] = '\0';       // string sonlandırma işlemi
    return y;
}