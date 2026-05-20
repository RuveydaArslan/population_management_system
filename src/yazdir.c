
#include <stdio.h>
#include "yazdir.h"

// şehirlerin toplam nüfus bilgilerini ekrana düzenli bir şekilde ekrana yazdırmak için kullanılır
void yazdirSehirler(Sehir *sehirler, int size)
{
    // tüm şehirleri sırasıyla dolaşır
    for (int i = 0; i < size; i++)
    {
        // toplam nüfus verisi [] içinde yazdırır
        printf("[%d]", sehirler[i].toplamNufus);

        // eğer son eleman değilse son satırsa değilse nüfus bilgileirnin ayrılmaıs için - işareti konulur
        if ((i + 1) % 5 != 0 && (i + 1) != size)
            printf("-");

        // her 5 şehirde alt satıra geçilir
        if ((i + 1) % 5 == 0)
            printf("\n");
    }

    if (size % 5 != 0)
        printf("\n");

    printf("\n");
}