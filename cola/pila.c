#include "pila.h"

#include <stdlib.h>

#define MEM 10
/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...

pila_t *pila_crear(void) {
    pila_t *pila = malloc(sizeof(pila_t));
    if(pila == NULL)
        return NULL;
    pila->datos = malloc(MEM * sizeof(void *));
    if(pila->datos == NULL) {
        free(pila);
        return NULL;
    }
    pila->capacidad = MEM;
    pila->cantidad = 0;
    return pila;
}

void pila_destruir(pila_t *pila) {
    free(pila->datos);
    free(pila);
}

bool pila_redimensionar(pila_t *pila, size_t tam_nuevo) {
    void *datos_nuevo = realloc(pila->datos, tam_nuevo * sizeof(void *));
    if (datos_nuevo == NULL) {
        free(pila->datos);
        return false;
    }
    pila->datos = datos_nuevo;
    pila->capacidad = tam_nuevo;
    return true;
}

bool pila_esta_vacia(const pila_t *pila) {
    return !pila->cantidad; 
}

bool pila_apilar(pila_t *pila, void *valor) {
    if(pila->capacidad == pila->cantidad) {
        if(!pila_redimensionar(pila, pila->capacidad * 2)){
            return false;
        }
    }    
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;    
    return true;    
}

void *pila_ver_tope(const pila_t *pila) {
    if(pila_esta_vacia(pila))
        return NULL;
    return pila->datos[pila->cantidad - 1];    
}

void *pila_desapilar(pila_t *pila) {
    if(pila_esta_vacia(pila)) {
        return NULL;
    }
    if(pila->cantidad * 4 <= pila->capacidad) {
        pila_redimensionar(pila, pila->capacidad / 2);
    }
    void *tope = pila_ver_tope(pila);      
    pila->cantidad--;
    return tope; 
}