#define _POSIX_C_SOURCE 200809L

#include "abb.h"
#include "pila.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



struct abb {
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
    size_t largo;
    nodo_t* raiz;
};



/* ******************************************************************
 *                             NODO
 * *****************************************************************/



struct nodo {
    nodo_t* izq;
    nodo_t* der;
    char* clave;
    void* dato;
};



nodo_t* nodo_crear(const char* clave, void* dato){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (nodo == NULL) return NULL;

    char* clave_aux = strdup(clave);
    if (clave_aux == NULL) {
        return NULL;
    }
    nodo->izq = NULL;
    nodo->der = NULL;
    nodo->dato = dato;
    nodo->clave = clave_aux;
    return nodo;
}



void nodo_destruir(nodo_t* nodo, abb_t* arbol) {
    free(nodo->clave);
    free(nodo);
}



/* ******************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/



nodo_t* buscar_reemplazante(nodo_t* nodo_actual){
    if(nodo_actual->der == NULL) return nodo_actual;
    return buscar_reemplazante(nodo_actual->der);
}



nodo_t* buscar_padre(nodo_t* nodo_actual, const char* clave, abb_t* arbol) {
    if (nodo_actual == NULL) return NULL;
    if (arbol->cmp(clave, nodo_actual->clave) < 0) {
        if (nodo_actual->izq == NULL) {
            return nodo_actual;
        }
        return buscar_padre(nodo_actual->izq, clave, arbol);
    } else if (arbol->cmp(clave, nodo_actual->clave) > 0) {
        if (nodo_actual->der == NULL) {
            return nodo_actual;
        }
        return buscar_padre(nodo_actual->der, clave, arbol);
    }
    return NULL;
}



nodo_t* buscar_padre_nodo_a_borrar(nodo_t* nodo_actual, const char* clave, abb_t* arbol) {
    if (nodo_actual == NULL) return NULL;
    if (arbol->cmp(clave, nodo_actual->clave) < 0) {
        if (arbol->cmp(clave, nodo_actual->izq->clave) == 0) return nodo_actual;
        return buscar_padre_nodo_a_borrar(nodo_actual->izq, clave, arbol);
    }
    else if (arbol->cmp(clave, nodo_actual->clave) > 0) {
        if (arbol->cmp(clave, nodo_actual->der->clave) == 0) return nodo_actual;
        return buscar_padre_nodo_a_borrar(nodo_actual->der, clave, arbol);
    }
    return NULL;
}



nodo_t* buscar_nodo(nodo_t* nodo_actual, const char* clave, const abb_t* arbol) {
    if (nodo_actual == NULL) return NULL;

    if (arbol->cmp(clave, nodo_actual->clave) < 0) return buscar_nodo(nodo_actual->izq, clave, arbol);
    else if (arbol->cmp(clave, nodo_actual->clave) > 0) return buscar_nodo(nodo_actual->der, clave, arbol);

    return nodo_actual;
}



int cantidad_de_hijos(nodo_t* nodo) {
    int cantidad_de_hijos = 0;

    if (nodo->izq == NULL && nodo->der == NULL) cantidad_de_hijos = 0;
    if ((nodo->izq && nodo->der == NULL) || (nodo->izq == NULL && nodo->der)) cantidad_de_hijos = 1;
    if (nodo->izq && nodo->der) cantidad_de_hijos = 2;

    return cantidad_de_hijos;
}



void* borrar_nodo_sin_hijos (abb_t *arbol, const char *clave, nodo_t* nodo) {
    void* dato = nodo->dato;

    nodo_t* padre = buscar_padre_nodo_a_borrar(arbol->raiz, clave, arbol);
    if (padre == NULL) return NULL;

    if(padre->izq && arbol->cmp(clave, padre->izq->clave) == 0) padre->izq = NULL;
    else if(padre->der && arbol->cmp(clave, padre->der->clave) == 0) padre->der = NULL;
    nodo_destruir(nodo, arbol);
    arbol->largo--;

    return dato;
}



void* borrar_nodo_un_hijo (abb_t *arbol, const char *clave, nodo_t* nodo) {
    void* dato = nodo->dato;

    if (arbol->cmp(arbol->raiz->clave, nodo->clave) == 0) {
        if (arbol->raiz->izq) {
            nodo_t* nodo_aux = arbol->raiz->izq;
            nodo_destruir(arbol->raiz, arbol);
            arbol->raiz = nodo_aux;
        } else if(arbol->raiz->der){
            nodo_t* nodo_aux = arbol->raiz->der;
            nodo_destruir(arbol->raiz, arbol);
            arbol->raiz = nodo_aux;
        }
        arbol->largo--;
        return dato;
    }

    nodo_t* padre = buscar_padre_nodo_a_borrar(arbol->raiz, clave, arbol);
    if (padre == NULL) return NULL;

    if (padre->izq && arbol->cmp(clave, padre->izq->clave) == 0) {
        if (nodo->izq) padre->izq = nodo->izq;
        else if (nodo->der) padre->izq = nodo->der;
    } else if (padre->der && arbol->cmp(clave, padre->der->clave) == 0) {
        if (nodo->izq) padre->der = nodo->izq;
        else if (nodo->der) padre->der = nodo->der;
    }
    nodo_destruir(nodo, arbol);
    arbol->largo--;

    return dato;
}



void* borrar_nodo_dos_hijos(abb_t *arbol, const char *clave, nodo_t* nodo) {
    void* dato = nodo->dato;

    nodo_t* nodo_reemplazante = buscar_reemplazante(nodo->izq);
    char* clave_reemplazante = strdup(nodo_reemplazante->clave);
    void* dato_reemplazante = abb_borrar(arbol, nodo_reemplazante->clave);
    free(nodo->clave);
    nodo->clave = clave_reemplazante;
    nodo->dato = dato_reemplazante;

    return dato;
}



/* ******************************************************************
 *                       PRIMITIVAS DEL ABB
 * *****************************************************************/



abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* abb = malloc(sizeof(abb_t));
    if (abb == NULL) return NULL;
    abb->cmp = cmp;
    abb->destruir_dato = destruir_dato;
    abb->largo = 0;
    abb->raiz = NULL;
    return abb;
}



bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    if (abb_pertenece(arbol,clave)) {
        nodo_t* nodo = buscar_nodo(arbol->raiz, clave, arbol);
        if (nodo == NULL) return false;
        if(arbol->destruir_dato) arbol->destruir_dato(nodo->dato);
        nodo->dato = dato;
        return true;
    }

    nodo_t* nuevo_nodo = nodo_crear(clave, dato);
    if (nuevo_nodo == NULL) return false;

    if (arbol->raiz == NULL) {
        arbol->raiz = nuevo_nodo;
        arbol->largo++;
        return true;
    }

    nodo_t* nodo_padre = buscar_padre(arbol->raiz, clave, arbol);
    if (nodo_padre == NULL) return false;

    if(arbol->cmp(clave, nodo_padre->clave) < 0) {
        nodo_padre->izq = nuevo_nodo;
    } else if (arbol->cmp(clave, nodo_padre->clave) > 0) {
        nodo_padre->der = nuevo_nodo;
    }
    arbol->largo++;
    return true;
}



void *abb_borrar(abb_t *arbol, const char *clave){
    nodo_t* nodo = buscar_nodo(arbol->raiz, clave, arbol);
    if (nodo == NULL) return NULL;

    if (arbol->largo == 1) {
        void* dato = arbol->raiz->dato;
        arbol->raiz = NULL;
        nodo_destruir(nodo, arbol);
        arbol->largo--;
        return dato;
    }

    if (cantidad_de_hijos(nodo) == 0) {
        return borrar_nodo_sin_hijos(arbol, clave, nodo);
    }
    else if (cantidad_de_hijos(nodo) == 1) {
        return borrar_nodo_un_hijo(arbol,clave,nodo);
    }

    return borrar_nodo_dos_hijos(arbol,clave, nodo);
}



void *abb_obtener(const abb_t *arbol, const char *clave){
    nodo_t* nodo = buscar_nodo(arbol->raiz, clave, arbol);
    if (nodo == NULL) return NULL;
    return nodo->dato;
}



bool abb_pertenece(const abb_t *arbol, const char *clave){
    nodo_t* nodo = buscar_nodo(arbol->raiz, clave, arbol);
    if (nodo == NULL) return false;
    return true;
}



size_t abb_cantidad(const abb_t *arbol){
    if (arbol->raiz == NULL) return 0;
    return arbol->largo;
}



void _abb_destruir(abb_t *arbol, nodo_t* nodo) {
    if (nodo == NULL) {
        return;
    }
    _abb_destruir(arbol, nodo->izq);
    _abb_destruir(arbol, nodo->der);
    if (arbol->destruir_dato) {
        arbol->destruir_dato(nodo->dato);
    }
    nodo_destruir(nodo, arbol);
}

void abb_destruir(abb_t *arbol) {
    _abb_destruir(arbol, arbol->raiz);
    free(arbol);
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

struct abb_iter {
    pila_t *pila;
};

void apilar_hijos_izq(const abb_iter_t *iter, nodo_t *nodo) {
    if (!nodo) return;
    pila_apilar(iter->pila, nodo);
    return apilar_hijos_izq(iter, nodo->izq);
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
    abb_iter_t *iter = malloc(sizeof(abb_iter_t));
    iter->pila = pila_crear();
    apilar_hijos_izq(iter, arbol->raiz);
    return iter;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter) {
    if (abb_iter_in_al_final(iter))
        return NULL;
    nodo_t *nodo = pila_ver_tope(iter->pila);
    return nodo->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter) {
    return pila_esta_vacia(iter->pila);
}

bool abb_iter_in_avanzar(abb_iter_t *iter) {
    if (abb_iter_in_al_final(iter))
        return false;
    nodo_t *nodo = pila_desapilar(iter->pila);
    if (nodo->der) {
        apilar_hijos_izq(iter, nodo->der);
    }
    return true;
}

void abb_iter_in_destruir(abb_iter_t* iter) {
    pila_destruir(iter->pila);
    free(iter);
}

void abb_iterar(nodo_t *nodo, bool visitar(const char *, void *, void *), void *extra) {
    if (!nodo) return;
    abb_iterar(nodo->izq, visitar, extra);
    visitar(nodo->clave, nodo->dato, extra);
    abb_iterar(nodo->der, visitar, extra);
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra) {
    abb_iterar(arbol->raiz, visitar, extra);
}
