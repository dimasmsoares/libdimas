#ifndef LIBDIMAS_H
#define LIBDIMAS_H

typedef struct ConfigMenu {
    char titulo[64];
    char opcoes[256];
    char separador[2];
} ConfigMenu;

int menu(const ConfigMenu *cm); 

#endif
