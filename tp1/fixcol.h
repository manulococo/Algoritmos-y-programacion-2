#ifndef FIXCOL_H
#define FIXCOL_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


//Devuelve false si argc es menor a 2 o mayor que 3
//Devuelve false si argv[1] no es un numero o si es menor o igual a 0
bool archivo_leer_parametros(int argc, char const *argv[]);

//si hay un archivo para abrir lo abre en modo lectura y lo devuelve como FILE*
//si no hay un archivo para abrir, devuelve stdin
FILE *archivo_abrir(int argc, char const *argv[]); 

//recibe un archivo abierto en modo lectura y la cantidad de columnas a separar
//Escribe lineas en stdout que tengan hasta n columnas
//Devuelve false en caso de error
bool archivo_escribir(FILE *f, int n);

#endif