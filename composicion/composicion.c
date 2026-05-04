#include "composicion.h"
#include <pila.h>
#include <stdlib.h>

struct composicion {
    pila_t *func;
};

composicion_t *composicion_crear() {
    composicion_t *comp = malloc(sizeof(composicion_t *));
    if(!comp)   
        return NULL;
    comp->func = pila_crear();
    if(!comp->func) {
        free(comp);
        return NULL;
    }
    return comp;
}

void composicion_destruir(composicion_t *comp) {
    pila_destruir(comp->func);
    free(comp);
}

bool composicion_agregar_funcion(composicion_t *comp, funcion_t f) {
    return pila_apilar(comp->func, (void *)f);
}

double composicion_aplicar(composicion_t *comp, double x) { 
    double res = x;
    while(!pila_esta_vacia(comp->func)) {
        res = ((funcion_t)pila_desapilar(comp->func))(res);
    }
    return res;
}