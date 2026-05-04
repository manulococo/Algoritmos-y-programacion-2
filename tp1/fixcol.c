#define _POSIX_C_SOURCE 200809L
#include "fixcol.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

static bool es_numero(const char *a) {
    for (size_t i = 0; a[i]!= '\0'; i++) {
        if (!isdigit(a[i]))
        return false;
    }
    return true;
}

bool archivo_leer_parametros(int argc, char const *argv[]) {
    if (argc > 3 || argc < 2){
        return false;
    }
    return es_numero(argv[1]) && atoi(argv[1]) > 0;
}

FILE *archivo_abrir(int argc, char const *argv[]) {
    if (argc == 2) 
        return stdin;
    else 
        return fopen(argv[2], "r");
}

static size_t lineas_a_separar(int n, size_t largo){
    if (largo <= n)
        return 1;
    return largo % (size_t)n? (largo / (size_t)n) + 1: largo / (size_t)n;
}

static bool linea_escribir(char *linea, int n, size_t largo) {              
    if (linea[largo] != '\n')
        largo++;
    size_t num_lineas = lineas_a_separar(n, largo);
    size_t i, j;
    for (i = 0; i < num_lineas; i++) {
        for (j = 0; j < n && linea[j + n  * i] != '\n' && j < largo; j++) {
            printf("%c", linea[j + n * i]);
        }
        printf("\n");   
    }
    return true;     
}

bool archivo_escribir(FILE *f, int n) {
    char *linea = NULL;
    size_t tam = 0;
    ssize_t carac_leidos;
    while ((carac_leidos = getline(&linea, &tam, f)) != EOF) {
        if (!linea_escribir(linea, n, carac_leidos - 1)) {
            free(linea);
            return false;
        }
    }
    free(linea);
    return true;
}