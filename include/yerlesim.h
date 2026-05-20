
#ifndef YERLESIM_H
#define YERLESIM_H

// şehir ilçe mahalle için kalıtım benzetmesini sağlar
typedef struct
{
    int id;
    char ad[50];
} Yerlesim;
Yerlesim yerlesimOlustur(int id, const char *ad);

#endif
