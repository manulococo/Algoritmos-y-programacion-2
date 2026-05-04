#include "fixcol.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    if (!archivo_leer_parametros(argc, argv)) {
        fprintf(stderr, "Error: Cantidad erronea de parametros\n");
        return 1;
    }  
    FILE *f = archivo_abrir(argc, argv);
    if (!f) {
        fprintf(stderr, "Error: archivo fuente inaccesible\n");
        return 1;
    }
    int n = atoi(argv[1]);
    if (!archivo_escribir(f, n)) {
        fclose(f);
        return 1;
    }
    fclose(f);
    return 0;
}