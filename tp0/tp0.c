#include "tp0.h"
#include <stdio.h>
/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;
}

int maximo(int vector[], int n) {
    if(n == 0)
        return -1;  
    int max = vector[0];
    size_t pos_max = 0;
    for (size_t i = 0; i < n; i++) {
        if(vector[i] > max) {
            max = vector[i];
            pos_max = i;
        }
    }
    return (int)pos_max;
}

int comparar_n_elem(int vector1[], int vector2[], int n) {
    for (size_t i = 0; i < n; i++) {
        if(vector1[i] > vector2[i])
            return 1;
        else if(vector1[i] < vector2[i])
            return -1;    
    }
    return 0;
}

int minimo(int a, int b){
    return a > b? b: a;
}

int comparar(int vector1[], int n1, int vector2[], int n2) {
    int comp = comparar_n_elem(vector1, vector2, minimo(n1, n2));
    if(comp)
        return comp;
    if(n1 == n2)    
        return 0;
    else return n1 > n2? 1: -1;    
}

void seleccion(int vector[], int n) {
    for (int i = 0; i < n; i++) {
        int pos_max = maximo(vector, n - i);
        swap(&vector[pos_max], &vector[n - i - 1]);
    }
}
