#define _POSIX_C_SOURCE 200809L

#include "abb.h"
#include "pila.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

/* ******************************************************************
 *                             NODO
 * *****************************************************************/



typedef struct nodo {
	struct nodo* izq;
	struct nodo* der;
	char* clave;
	void* dato;
} nodo_t;


struct abb {
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir_dato;
	size_t largo;
	nodo_t* raiz;
};


nodo_t* nodo_crear(const char* clave, void* dato){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL) return NULL;

	char* clave_aux = strdup(clave);
	if (clave_aux == NULL) {
		free(nodo);
		return NULL;
	}
	nodo->izq = NULL;
	nodo->der = NULL;
	nodo->dato = dato;
	nodo->clave = clave_aux;
	return nodo;
}



void nodo_destruir(nodo_t* nodo) {
	free(nodo->clave);
	free(nodo);
}



/* ******************************************************************
 *                       FUNCIONES AUXILIARES
 * *****************************************************************/





nodo_t* buscar_reemplazante(nodo_t* nodo_actual){
	if(nodo_actual->der == NULL) {
		return nodo_actual;
	}

	return buscar_reemplazante(nodo_actual->der);
}



nodo_t** buscar_nodo(nodo_t* nodo_actual, const char* clave, abb_t* arbol, nodo_t* padre, bool hijo_der) {
	if (!arbol->raiz) return &(arbol->raiz);

	if (!nodo_actual && hijo_der) return &(padre->der);
	else if (!nodo_actual && !hijo_der) return &(padre->izq);

	if (!padre && arbol->cmp(clave, nodo_actual->clave) == 0) return &(arbol->raiz);

	if (arbol->cmp(clave, nodo_actual->clave) < 0) {
		return buscar_nodo(nodo_actual->izq, clave, arbol, nodo_actual, false);
	} else if (arbol->cmp(clave, nodo_actual->clave) > 0) {
		return buscar_nodo(nodo_actual->der, clave, arbol, nodo_actual, true);
	}

	if (hijo_der) return &(padre->der);
	return &(padre->izq);

}



int cantidad_de_hijos(nodo_t* nodo) {
	int cantidad_de_hijos = 0;

	if (nodo->izq == NULL && nodo->der == NULL) {
		cantidad_de_hijos = 0;
	} else if ((nodo->izq && nodo->der == NULL) || (nodo->izq == NULL && nodo->der)) {
		cantidad_de_hijos = 1;
	} else {
		cantidad_de_hijos = 2;
	}

	return cantidad_de_hijos;
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
	nodo_t** nodo = buscar_nodo(arbol->raiz, clave, arbol, NULL, false);

	// Reemplaza el dato del nodo
	if (*nodo) {
		if(arbol->destruir_dato) arbol->destruir_dato((*nodo)->dato);
		(*nodo)->dato = dato;
	} else {
		nodo_t* nuevo_nodo = nodo_crear(clave, dato);
		if (!nuevo_nodo) return false;
		*nodo = nuevo_nodo;
		arbol->largo++;
	}
	return true;
}



void *abb_borrar(abb_t *arbol, const char *clave){
	nodo_t** nodo = buscar_nodo(arbol->raiz, clave, arbol, NULL, false);
	if (*nodo == NULL) return NULL;

	void* dato = (*nodo)->dato;

	if (cantidad_de_hijos(*nodo) == 0) {
		nodo_destruir(*nodo);
		*nodo = NULL;
		arbol->largo--;
	} else if (cantidad_de_hijos(*nodo) == 1) {
		nodo_t* nodo_aux = *nodo;
		if ((*nodo)->izq) {
			*nodo = (*nodo)->izq;
			arbol->largo--;
			nodo_destruir(nodo_aux);
		} else {
			*nodo = (*nodo)->der;
			arbol->largo--;
			nodo_destruir(nodo_aux);
		}
	} else {
		nodo_t* nodo_reemplazante = buscar_reemplazante((*nodo)->izq);
		char* clave_reemplazante = strdup(nodo_reemplazante->clave);
		void* dato_reemplazante = abb_borrar(arbol, nodo_reemplazante->clave);
		free((*nodo)->clave);
		(*nodo)->clave = clave_reemplazante;
		(*nodo)->dato = dato_reemplazante;
	}
	return dato;
}



void *abb_obtener(const abb_t *arbol, const char *clave){

	nodo_t** nodo = buscar_nodo(arbol->raiz, clave, (abb_t*)arbol, NULL, false);
	return *nodo ? (*nodo)->dato : NULL;
}



bool abb_pertenece(const abb_t *arbol, const char *clave){
	nodo_t** nodo = buscar_nodo(arbol->raiz, clave, (abb_t*)arbol, NULL, false);
	return *nodo ? true : false;

}



size_t abb_cantidad(const abb_t *arbol){
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
	nodo_destruir(nodo);
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
	apilar_hijos_izq(iter, nodo->izq);
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



int abb_iterar(nodo_t *nodo, bool visitar(const char *, void *, void *), void *extra) {
	if (!nodo) return 0;
	if (abb_iterar(nodo->izq, visitar, extra) == 1) return 1;
	if (!visitar(nodo->clave, nodo->dato, extra)) return 1;
	return abb_iterar(nodo->der, visitar, extra);
}



void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra) {
	abb_iterar(arbol->raiz, visitar, extra);
}