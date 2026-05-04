#include "cola.h"

#include <stdlib.h>

typedef struct nodo {
    void *dato;
    struct nodo *prox;
} nodo_t;

nodo_t *nodo_crear(void *dato) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if(nodo == NULL)
        return NULL;
    nodo->dato = dato;
    nodo->prox = NULL;
    return nodo;
}

void nodo_destruir(nodo_t *nodo) {
    free(nodo);
}

struct cola {
    nodo_t *prim;
    nodo_t *ult;
};

cola_t *cola_crear(void) {
    cola_t *cola = malloc(sizeof(cola_t));
    if(cola == NULL)
        return NULL;
    cola->prim = NULL;
    cola->ult = NULL;
    return cola;    
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)) {   
    while(cola->prim != NULL) {
        nodo_t *aux = cola->prim;
        cola->prim = cola->prim->prox;
        if(destruir_dato != NULL)
            destruir_dato(aux->dato);
        nodo_destruir(aux);
    }
    free(cola);
}

bool cola_esta_vacia(const cola_t *cola) {
    return (!cola->prim && !cola->ult); 
}


bool cola_encolar(cola_t *cola, void *valor) {
    nodo_t *nodo = nodo_crear(valor);
    if(nodo == NULL)
        return false;
    if(cola_esta_vacia(cola)) {
        cola->prim = nodo;
    } 
    else {
        cola->ult->prox = nodo;
    }
    cola->ult = nodo;
    return true;    
}

void *cola_ver_primero(const cola_t *cola) {
    if(cola_esta_vacia(cola))
        return NULL;
    return cola->prim->dato;
}

void *cola_desencolar(cola_t *cola) {
    if(cola_esta_vacia(cola))
        return NULL;
    void *dato = cola->prim->dato;
    nodo_t *aux = cola->prim;
    cola->prim = cola->prim->prox;
    if(aux == cola->ult)
        cola->ult = NULL;
    nodo_destruir(aux);
    return dato;
}

