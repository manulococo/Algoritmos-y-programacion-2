#include "lista.h"
#include <stdlib.h>
/* ******************************************************************
 *                             NODO
 * *****************************************************************/
typedef struct nodo nodo_t;

struct nodo{
    void* dato;
    struct nodo* proximo;
};


nodo_t* nodo_crear(void* valor){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo) return NULL;
    nodo->dato = valor;
    nodo->proximo = NULL;
    return nodo;
}

void nodo_destruir(nodo_t* nodo) {
    free(nodo);
}

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

struct lista{
    nodo_t *primero;
    nodo_t *ultimo;
    size_t largo;
};

lista_t *lista_crear(void){
    lista_t* lista = malloc(sizeof(lista_t));
    if (!lista) return NULL;
    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista){
    return lista->primero == NULL;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
    nodo_t* nuevo_nodo = nodo_crear(dato);
    if (!nuevo_nodo) return false;
    
    if (lista_esta_vacia(lista)) {
        lista->primero = nuevo_nodo;
        lista->ultimo = nuevo_nodo;
    } else {
        nodo_t* nodo_aux = lista->primero;
        lista->primero = nuevo_nodo;
        lista->primero->proximo = nodo_aux;
    }
    
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
    nodo_t* nuevo_nodo = nodo_crear(dato);
    if (!nuevo_nodo) return false;
    
    if (!lista_esta_vacia(lista)) {
        lista->ultimo->proximo = nuevo_nodo;
    } else {
        lista->primero = nuevo_nodo;
    }
    lista->largo++;
    lista->ultimo = nuevo_nodo;
    return true;
}

void *lista_borrar_primero(lista_t *lista) {
    if (lista_esta_vacia(lista)) return NULL;
    void* dato = lista->primero->dato;
    nodo_t* nodo_aux = lista->primero;
    if (lista->ultimo == lista->primero)
        lista->ultimo = lista->primero->proximo;
    lista->primero = lista->primero->proximo;
    nodo_destruir(nodo_aux);
    lista->largo--;
    return dato;
}

void *lista_ver_primero(const lista_t *lista){
    if (lista_esta_vacia(lista)) return NULL;
    return lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
    if (lista_esta_vacia(lista)) return NULL;
    return lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista){
    return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
    while (!lista_esta_vacia(lista)) {
        void* dato = lista_borrar_primero(lista);
        if (destruir_dato != NULL) {
            destruir_dato(dato);
        }
    }
    free(lista);
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/


struct lista_iter {
    nodo_t *actual;
    nodo_t *anterior;
    lista_t *lista;
};

lista_iter_t *lista_iter_crear(lista_t *lista) {
    lista_iter_t *iter = malloc(sizeof(lista_iter_t));
    if (!iter) return NULL;
    iter->actual = lista->primero;
    iter->anterior = NULL;
    iter->lista = lista;
    return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
    if(!lista_iter_al_final(iter)) {
        iter->anterior = iter->actual;
        iter->actual = iter->actual->proximo;
        return true;
    }
    return false;
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
    if (lista_esta_vacia(iter->lista) || lista_iter_al_final(iter))
        return NULL;
    return iter->actual->dato;
} 

bool lista_iter_al_final(const lista_iter_t *iter) {
    return !iter->actual;
}

void lista_iter_destruir(lista_iter_t *iter) {
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
    nodo_t *nuevo_nodo = nodo_crear(dato);
    if (!nuevo_nodo) return false;
    nuevo_nodo->proximo = iter->actual;
    if (!iter->anterior) {
        iter->lista->primero = nuevo_nodo;
    } else {
        iter->anterior->proximo = nuevo_nodo;
    }
    if (lista_iter_al_final(iter)) {
        iter->lista->ultimo = nuevo_nodo;
    }
    iter->actual = nuevo_nodo;
    iter->lista->largo++;
    return true;
}

void *lista_iter_borrar(lista_iter_t *iter) {
    if (lista_esta_vacia(iter->lista) || lista_iter_al_final(iter)) return NULL;
    void *dato;
    nodo_t *aux = iter->actual;
    if (iter->actual == iter->lista->ultimo) {
        iter->lista->ultimo = iter->anterior;
    }
    if (iter->actual == iter->lista->primero) {
        iter->lista->primero = iter->actual->proximo;
    }
    if (iter->anterior) {
        iter->anterior->proximo = aux->proximo;
    }
    iter->actual = aux->proximo;
    dato = aux->dato;
    nodo_destruir(aux);
    iter->lista->largo--;
    return dato;
}

/* ******************************************************************
 *                         ITERADOR INTERNO
 * *****************************************************************/



void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
    nodo_t *actual = lista->primero;
    while (actual) {
        if (!visitar(actual->dato, extra)) return;
        actual = actual->proximo;
    }
}