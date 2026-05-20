
#ifndef SEHIROLUSTUR_H
#define SEHIROLUSTUR_H

#include "sehir.h" // şehir yapısını kullandığım için ekledim
#include <stdio.h> // dosya işlemleri için ekledim

// kullanının girmiş olduğu bilgilerle şehir yapısı oluşturur
Sehir *sehirleri_olustur(const char *il_input, int *sehirSayisiOutput);

void dosyadanIsimCek(FILE *fp, char *hedef);

#endif