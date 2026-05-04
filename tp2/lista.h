#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct lista lista_t;

typedef struct lista_iter lista_iter_t;



/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero si la lista esta vacia, falso si la lista no esta vacia.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un elemento al inicio de la lista. Devuelve false en caso de error.
// Pre: La lista fue creada.
// Post: Se agrego un nuevo elemento al inicio de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un elemento al final de la lista. Devuelve falso en caso de error.
// Pre: La lista fue creada.
// Post: Se agrego un nuevo elemento al inicio de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Si la lista no esta vacia borra el primer elemento y devuelve su valor.
// Si esta vacia devuelve NULL.
// Pre: La lista fue creada.
// Post: Se devuelve el primer elemento de la lista, y se borra el primer elemento.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el primer elemento de la lista
// Si la lista no esta vacia. Devuelve el primer elemento de la lista.
// Si la lista esta vacia devuelve NULL.
// Pre: La lista fue creada
// Post: Si la lista no estaba vacia, devuelve el primer elemento
void *lista_ver_primero(const lista_t *lista);

// Obtiene el ultimo elemento de la lista
// Si la lista no esta vacia. Devuelve el ultimo elemento de la lista.
// Si la lista esta vacia devuelve NULL.
// Pre: La lista fue creada
// Post: Si la lista no estaba vacia, devuelve el ultimo elemento
void *lista_ver_ultimo(const lista_t* lista);

// Devuelve el largo de la lista.
// Pre: La lista fue creada.
// Post: devuelve el largo de la lista.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

// crea un iterador.
// Post: devuelve un iterador que apunta al primer elemento de la lista.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza al siguiente elemento de la lista.
// Pre: el iterador fue creado.
// Post: el iterador apunta al siguiente elemento, o devuelve false si no
// pudo avanzar.
bool lista_iter_avanzar(lista_iter_t *iter);

// Obtiene a que elemento apunta iter.
// Pre: el iterador fue creado.
// Post: Se devuelve el dato al que apunta el iterador.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve true si el iterador está al final de la lista, false en 
// caso contrario
// Pre: el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
// Post: se destruye el dato de la lista.
void lista_iter_destruir(lista_iter_t *iter);

// Agrega un dato en la posicion del iterador. False en caso de error
// Pre: el iterador fue creado.
// Post: se agrega un nuevo elemento entre el anterior del iterador y donde
// apunta el iterador. El iterador queda apuntando al nuevo dato.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Destruye el dato al que apunta el iterador.
// Pre: el iterador fue creado.
// Post: el iterador fue destruido
void *lista_iter_borrar(lista_iter_t *iter);

/* ******************************************************************
 *                         ITERADOR INTERNO
 * *****************************************************************/
// Itera la lista y aplica la función visitar a cada elemento de la lista.
// Pre: la lista fue creada.
// Post: se reccorrió toda la lista, aplicando visitar a cada uno.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

void pruebas_lista_estudiante(void);

#endif // LISTA_H