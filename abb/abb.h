#ifndef ABB_H
#define ABB_H

#include <stdlib.h>
#include <stdbool.h>


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct abb abb_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);

typedef void (*abb_destruir_dato_t) (void *);



/* ******************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

// Crea un abb
// post: devuelve un abb
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

// Guarda un nuevo elemento en el abb. O cambia el valor de algun elemento devuelve
// true si todo salio bien, false si algo salio mal
// pre: El abb fue creado
// post: Se agrego un nuevo elemento al abb
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

// Si el arbol no esta vacio y el elemento que queremos borrar exite, borra ese
// elemento del abb y devuelve su valor, en caso contrario devuelve NULL
// pre: El abb fue creado
// post: Se borro un elemento del abb y se devuelve su valor
void *abb_borrar(abb_t *arbol, const char *clave);

// Busca un elemento del abb y devuelve su valor. Si no existe el elemento
// devuelve NULL
// pre: El abb fue creado
// post: devuelve el valor del elemento.
void *abb_obtener(const abb_t *arbol, const char *clave);

// Se fija si un elemento existe en el abb, si existe devuelve true, si no existe
// devuelve false
// pre: EL abb fue creado
// post: devuelve true si existe el elemento
bool abb_pertenece(const abb_t *arbol, const char *clave);

// Devuelve la cantidad de elementos que hay en el abb
// pre: El abb fue creado
// post: Devuelve la cantidad de elementos del abb
size_t abb_cantidad(const abb_t *arbol);

// Destruye el abb. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: El abb fue creado. destruir_dato es una función capaz de destruir
// los datos del abb, o es NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void abb_destruir(abb_t *arbol);



/* ******************************************************************
 *                 PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

typedef struct abb_iter abb_iter_t;

// Crea un iterador del abb.
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

// Avanza iterador.
bool abb_iter_in_avanzar(abb_iter_t *iter);

// Devuelve clave actual, esa clave no se puede modificar ni liberar.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

// Comprueba si terminó la iteración.
bool abb_iter_in_al_final(const abb_iter_t *iter);

// Destruye iterador.
void abb_iter_in_destruir(abb_iter_t* iter);



/* ******************************************************************
 *                    PRIMITIVAS ITERADOR INTERNO
 * *****************************************************************/

// Le aplica a todos los elementos del abb la función visitar.
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);



/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

void pruebas_abb_estudiante(void);

#endif