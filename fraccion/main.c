#include <stdlib.h>
#include <stdio.h> // sprintf
//#include "fraccion.h"
#define MAX_STR 30
typedef struct fraccion {
    int numerador;
    int denominador;
} fraccion_t;

fraccion_t* fraccion_crear(int numerador, int denominador) {
    fraccion_t *fraccion = malloc(sizeof(fraccion_t));
    if(fraccion == NULL)
        return NULL;
    if(!denominador)
        return NULL; 
    fraccion->numerador = numerador;
    fraccion->denominador = denominador;  
    return fraccion;  
}

void fraccion_destruir(fraccion_t* fraccion) {
    free(fraccion);
}

fraccion_t* fraccion_sumar(fraccion_t* f1, fraccion_t* f2) {
    fraccion_t *nueva;
    if(f1->denominador == f2->denominador) {
        nueva = fraccion_crear(f1->numerador + f2->numerador, f1->denominador);
        if(!nueva)
            return NULL;
    }     
    else {
        int nuevo_denominador = f1->denominador * f2->denominador;
        int nuevo_numerador = f1->denominador * f2->numerador + f2->denominador * f1->numerador; 
        nueva = fraccion_crear(nuevo_numerador, nuevo_denominador);
        if(!nueva)
            return NULL;
    }
    fraccion_destruir(f1);
    fraccion_destruir(f2);
    return nueva;
}

fraccion_t* fraccion_mul(fraccion_t* f1, fraccion_t* f2) {
    fraccion_t *nueva = fraccion_crear(f1->numerador * f2->numerador, f1->denominador * f2->denominador);
    if(!nueva)
        return NULL;
    fraccion_destruir(f1);
    fraccion_destruir(f2);
    return nueva;
}

int fraccion_parte_entera(fraccion_t* fraccion) {
    return fraccion->numerador / fraccion->denominador;
}

int mcd(int den, int num) {
    int r;
    while(den!=0){
        r = num % den;
        num = den;
        den = r;
    }
    return num;
}
void simplificar_fraccion(fraccion_t *fraccion) {
    int dividir=mcd(fraccion->denominador, fraccion->numerador);
    fraccion->numerador/=dividir;
    fraccion->denominador/=dividir;  
}

char* fraccion_representacion(fraccion_t* fraccion) {

    simplificar_fraccion(fraccion);
    char *buffer = malloc(sizeof(char) * MAX_STR);
    if(fraccion->denominador == 1)
        sprintf(buffer, "%d", fraccion->numerador);
    else {
        sprintf(buffer, "%d/%d", fraccion->numerador, fraccion->denominador);
    }
    return buffer;
}

int main(){
    fraccion_t *fraccion = fraccion_crear(2, 3);
    char *c = fraccion_representacion(fraccion);
    printf("%s\n", c);
}
