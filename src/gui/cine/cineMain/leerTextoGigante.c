#include <stdio.h>
#include <stdlib.h>
#include "leerTextoGigante.h"
#include <wchar.h>
#include <locale.h>

int leerTcine(){
    FILE *fichero;
    char c;
    fichero = fopen("src/gui/cine/cineMain/textoGigante.txt", "r");
    if (fichero == NULL) {
        printf("No se ha podido abrir el fichero\n");
        return 1;
    }
    while ((c = fgetwc(fichero)) != EOF) {
        printf("%c", c);
    }
    fclose(fichero);
    return 0;

}
/*
int main() {
    leerTcine();
    return 0;
}
*/