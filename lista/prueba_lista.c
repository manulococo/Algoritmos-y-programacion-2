#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

static void prueba_lista_vacia() {
    printf("\nINICIO DE PRUEBAS CON LISTA VACIA\n");

    lista_t* lista = lista_crear();

    print_test("Se creo la lista", lista != NULL);
    print_test("La lista esta vacia", lista_esta_vacia(lista));
    print_test("Vemos si no hay elementos en la primer posicion", lista_ver_primero(lista) == NULL);
    print_test("Vemos si no hay elementos en la ultima posicion", lista_ver_ultimo(lista) == NULL);
    lista_destruir(lista, NULL);
}

static void prueba_invariante_de_lista() {
    printf("\nINICIO DE PRUEBAS DE INVARIANTE DE LISTA\n");

    lista_t* lista = lista_crear();
    int array[] = {1,5,3};

    print_test("Insertamos un elemento al principio", lista_insertar_primero(lista, &array[0]));
    print_test("Vemos el primer elemento", lista_ver_primero(lista) == &array[0]);
    print_test("Vemos el ultimo elemento", lista_ver_ultimo(lista) == &array[0]);
    print_test("Comprobamos que el largo de la lista sea de 1", lista_largo(lista) == 1);
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("Insertamos un elemento al final", lista_insertar_ultimo(lista, &array[1]));
    print_test("Vemos el ultimo elemento", lista_ver_ultimo(lista) == &array[1]);
    print_test("Insertamos un elemento al final", lista_insertar_ultimo(lista, &array[2]));
    print_test("Vemos el ultimo elemento", lista_ver_ultimo(lista) == &array[2]);
    print_test("Comprobamos que el largo de la lista sea de 3", lista_largo(lista) == 3);
    print_test("Vemos que el primer elemento siga siendo el mismo", lista_ver_primero(lista) == &array[0]);
    print_test("Borramos el primer elemento", lista_borrar_primero(lista) == &array[0]);
    print_test("Vemos el primer elemento", lista_ver_primero(lista) == &array[1]);
    print_test("Vemos el ultimo elemento no cambie", lista_ver_ultimo(lista) == &array[2]);
    print_test("Comprobamos que el largo de la lista sea de 2", lista_largo(lista) == 2);
    print_test("Borramos el primer elemento", lista_borrar_primero(lista) == &array[1]);
    print_test("Borramos el primer elemento", lista_borrar_primero(lista) == &array[2]);
    print_test("Ahora la lista esta vacia", lista_esta_vacia(lista));
    print_test("El largo de la lista es 0", lista_largo(lista) == 0);


    lista_destruir(lista, NULL);
}

static void prueba_de_volumen() {
    printf("\nINICIO DE PRUEBAS DE VOLUMEN\n");

    lista_t* lista = lista_crear();

    bool primero = true;
    bool ultimo = true;
    bool insertar_primero = true;
    bool insertar_ultimo = true;
    bool borrar_primero = true;
    bool longitud = true;
    int tam = 10000;
    int array[tam];
    int i;

    for (i = 0; i < tam; i++) {
        insertar_primero &= lista_insertar_primero(lista, &array[i]);
        primero &= lista_ver_primero(lista) == &array[i];
        ultimo &= lista_ver_ultimo(lista) == &array[0];
        longitud &= lista_largo(lista) == i + 1;
    }

    print_test("Insertamos 10000 elementos al inicio", insertar_primero);
    print_test("El primer elemento siempre es el que corresponde", primero);
    print_test("El ultimo elemento siempre es el mismo", ultimo);
    print_test("El largo de la lista siempre es el correcto", longitud);
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));

    for (i = tam - 1; i >= 0; i--) {
        primero &= lista_ver_primero(lista) == &array[i];
        ultimo &= lista_ver_ultimo(lista) == &array[0];
        longitud &= lista_largo(lista) == i + 1;
        borrar_primero &= lista_borrar_primero(lista) == &array[i];
    }

    print_test("Borramos los 10000 elementos", borrar_primero);
    print_test("El primer elemento siempre es el que corresponde", primero);
    print_test("El ultimo elemento siempre es el mismo", ultimo);
    print_test("La longitud es siempre la correcta", longitud);
    print_test("La lista esta vacia", lista_esta_vacia(lista));

    for (i = 0; i < tam; i++) {
        insertar_ultimo &= lista_insertar_ultimo(lista, &array[i]);
        primero &= lista_ver_primero(lista) == &array[0];
        ultimo &= lista_ver_ultimo(lista) == &array[i];
        longitud &= lista_largo(lista) == i + 1;
    }

    print_test("Insertamos 10000 elementos al final", insertar_ultimo);
    print_test("El primer elemento siempre es el mismo", primero);
    print_test("El ultimo elemento siempre es el que corresponde", ultimo);
    print_test("El largo de la lista siempre es el correcto", longitud);
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));

    for (i = 0; i < tam; i++) {
        primero &= lista_ver_primero(lista) == &array[i];
        ultimo &= lista_ver_ultimo(lista) == &array[tam - 1];
        longitud &= lista_largo(lista) == tam - i;
        borrar_primero &= lista_borrar_primero(lista) == &array[i];
    }

    print_test("Borramos los 10000 elementos", borrar_primero);
    print_test("El primer elemento siempre es el que corresponde", primero);
    print_test("El ultimo elemento siempre es el mismo", ultimo);
    print_test("La longitud es siempre la correcta", longitud);
    print_test("La lista esta vacia", lista_esta_vacia(lista));

    lista_destruir(lista, NULL);
}

static void prueba_agregar_elemento_NULL() {
    printf("\nINICIO DE PRUEBAS AGREGAR ELEMENTO NULL\n");

    lista_t* lista = lista_crear();

    print_test("Agregar NULL al inicio", lista_insertar_primero(lista, NULL));
    print_test("Agregar NULL al inicio", lista_insertar_primero(lista, NULL));
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("Vemos primer elemento sea NULL", lista_ver_primero(lista) == NULL);
    print_test("Agregamos NULL en la ultima posicion", lista_insertar_ultimo(lista, NULL));
    print_test("Vemos ultimo elemento se NULL", lista_ver_ultimo(lista) == NULL);
    print_test("vemos que el largo de la lista sea de 3", lista_largo(lista) == 3);
    print_test("Quitamos el primer elemento", lista_borrar_primero(lista) == NULL);
    print_test("Quitamos el primer elemento", lista_borrar_primero(lista) == NULL);
    print_test("vemos que el largo de la lista sea de 1", lista_largo(lista) == 1);

    lista_destruir(lista, NULL);
}

static void prueba_vaciar_lista() {
    printf("\nINICIO DE PRUEBAS LISTA SE COMPORTA COMO RECIEN CREADA\n");

    lista_t* lista = lista_crear();
    int array[] = {3,4,2};

    print_test("La lista esta vacia", lista_esta_vacia(lista));
    print_test("Insertamos un elemento al final", lista_insertar_ultimo(lista, &array[0]));
    print_test("Insertamos un elemento al final", lista_insertar_ultimo(lista, &array[1]));
    print_test("Insertamos un elemento al final", lista_insertar_ultimo(lista, &array[2]));
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("El largo de la lista es 3", lista_largo(lista) == 3);
    print_test("Quitamos el primer elemento", lista_borrar_primero(lista) == &array[0]);
    print_test("Quitamos el primer elemento", lista_borrar_primero(lista) == &array[1]);
    print_test("Quitamos el primer elemento", lista_borrar_primero(lista) == &array[2]);
    print_test("La lista esta vacia", lista_esta_vacia(lista));
    print_test("El largo de la lista es 0", lista_largo(lista) == 0);
    print_test("Insertamos un elemento al final", lista_insertar_ultimo(lista, &array[0]));
    print_test("vemos el primer elemento", lista_ver_primero(lista) == &array[0]);
    print_test("vemos el ultimo elemento", lista_ver_ultimo(lista) == &array[0]);
    print_test("El largo de la lista es 1", lista_largo(lista) == 1);
    print_test("Quitamos el primer elemento", lista_borrar_primero(lista) == &array[0]);
    print_test("La lista esta vacia", lista_esta_vacia(lista));
    print_test("El largo de la lista es 0", lista_largo(lista) == 0);

    lista_destruir(lista,NULL);
}

static void prueba_lista_recien_creada() {
    printf("\nINICIO DE PRUEBAS BORDE CON LISTA RECIEN CREADA\n");

    lista_t* lista = lista_crear();

    print_test("Ver primero en lista recien creada nos devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("Quitar un elemento en lista recien creada nos devuelve NULL", lista_borrar_primero(lista) == NULL);

    lista_destruir(lista, NULL);
}

static void prueba_quitar_elementos_lista_vacia() {
    printf("\nINICIO DE PRUEBAS QUITAR ELEMENTO EN LISTA VACIA\n");

    lista_t* lista = lista_crear();
    int a = 5;

    print_test("La lista esta vacia", lista_esta_vacia(lista));
    print_test("Insertar un elemento", lista_insertar_primero(lista, &a));
    print_test("Borramos un elemento", lista_borrar_primero(lista) == &a);
    print_test("Borrar un elemento en lista vacia devuelve NULL", lista_borrar_primero(lista) == NULL);
    print_test("Ver primero devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("Ver ultimo devuelve NULL", lista_ver_ultimo(lista) == NULL);

    lista_destruir(lista, NULL);
}

static void prueba_destruir_lista_vacia_con_NULL() {
    printf("\nINICIO DE PRUEBAS DESTRUIR LISTA VACIA CON NULL\n");

    lista_t* lista = lista_crear();

    print_test("La lista esta vacia", lista_esta_vacia(lista));
    lista_destruir(lista, NULL);
    print_test("La lista se destruyo", true);
}

static void prueba_destruir_lista_vacia_con_free() {
    printf("\nINICIO DE PRUEBAS DESTRUIR LISTA VACIA CON FREE()\n");

    lista_t* lista = lista_crear();

    print_test("La lista esta vacia", lista_esta_vacia(lista));
    lista_destruir(lista, free);
    print_test("La lista se destruyo", true);
}

static void prueba_destruir_lista_no_vacia_con_NULL() {
    printf("\nINICIO DE PRUEBAS DESTRUIR LISTA NO VACIA CON NULL\n");

    lista_t* lista = lista_crear();
    int array[] = {1,2,6};

    print_test("Insertar elemento", lista_insertar_primero(lista, &array[0]));
    print_test("Insertar elemento", lista_insertar_primero(lista, &array[1]));
    print_test("Insertar elemento", lista_insertar_primero(lista, &array[2]));

    lista_destruir(lista, NULL);
    print_test("La lista se destruyo", true);
}

static void prueba_destruir_lista_no_vacia_con_free(){
    printf("\nINICIO DE PRUEBAS DESTRUIR LISTA NO VACIA CON FREE()\n");

    int* a = malloc(sizeof(int));
    int* b = malloc(sizeof(int));
    int* c = malloc(sizeof(int));

    lista_t* lista = lista_crear();

    print_test("Insertar elemento", lista_insertar_primero(lista, a));
    print_test("Insertar elemento", lista_insertar_primero(lista, b));
    print_test("Insertar elemento", lista_insertar_primero(lista, c));

    lista_destruir(lista, free);
    print_test("La lista se destruyo", true);
}

static void pruebas_lista() {
    prueba_lista_vacia();
    prueba_invariante_de_lista();
    prueba_de_volumen();
    prueba_agregar_elemento_NULL();
    prueba_vaciar_lista();
    prueba_lista_recien_creada();
    prueba_quitar_elementos_lista_vacia();
    prueba_destruir_lista_vacia_con_NULL();
    prueba_destruir_lista_vacia_con_free();
    prueba_destruir_lista_no_vacia_con_NULL();
    prueba_destruir_lista_no_vacia_con_free();
}

static void prueba_iter_insertar_principio(void) {
    printf("\nINICIO DE PRUEBAS INSERTAR AL PRINCIPIO\n");
    int array[] = {1,2,6};
    lista_t *lista = lista_crear();
    lista_iter_t *iter = lista_iter_crear(lista);
    
    print_test("Insertar elemento al principio", lista_iter_insertar(iter, &array[0]) && lista_iter_ver_actual(iter) == lista_ver_primero(lista));
    print_test("Insertar elemento al principio", lista_iter_insertar(iter, &array[1]) && lista_iter_ver_actual(iter) == lista_ver_primero(lista));
    print_test("Insertar elemento al principio", lista_iter_insertar(iter, &array[2]) && lista_iter_ver_actual(iter) == lista_ver_primero(lista));
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
}

static void prueba_iter_insertar_medio(void) {
    printf("\nINICIO DE PRUEBAS INSERTAR AL MEDIO\n");
    int array[] = {1,2,6};
    lista_t *lista = lista_crear();
    lista_iter_t *iter = lista_iter_crear(lista);

    print_test("Insertar elemento al principio", lista_iter_insertar(iter, &array[0]) && lista_iter_ver_actual(iter) == lista_ver_primero(lista));
    print_test("Insertar elemento al principio", lista_iter_insertar(iter, &array[1]) && lista_iter_ver_actual(iter) == lista_ver_primero(lista));
    print_test("Avanzo a la siguiente posición", lista_iter_avanzar(iter) && lista_iter_ver_actual(iter) == lista_ver_ultimo(lista));
    print_test("Insertar elemento al medio", lista_iter_insertar(iter, &array[2]) && lista_iter_ver_actual(iter) == &array[2]);
    print_test("Avanzo a la siguiente posición", lista_iter_avanzar(iter) && lista_iter_ver_actual(iter) == lista_ver_ultimo(lista));
    
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
}

static void prueba_iter_insertar_final(void) {
    printf("\nINICIO DE PRUEBAS INSERTAR AL FINAL\n");
    int array[] = {1,2,6,8};
    lista_t *lista = lista_crear();
    lista_iter_t *iter = lista_iter_crear(lista);
    bool ok = true;
    for (size_t i = 0; i < 3; i++) {
        ok &= lista_iter_insertar(iter, &array[i]);
        ok &= lista_iter_avanzar(iter);
        ok &= lista_largo(lista) == i + 1;
        ok &= lista_ver_ultimo(lista) == &array[i];
    }
    print_test("Se agregaron 3 elementos", ok);
    print_test("Insertar elemento al final", lista_iter_insertar(iter, &array[3]) && lista_iter_ver_actual(iter) == lista_ver_ultimo(lista));
    
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
}

static void prueba_iter_eliminar_principio(void) {
    printf("\nINICIO DE PRUEBAS ELIMINAR AL PRINCIPIO\n");
    int array[] = {1,2,6};
    lista_t *lista = lista_crear();
    lista_iter_t *iter = lista_iter_crear(lista);
    bool ok = true;
    for (size_t i = 0; i < 3; i++) {
        ok &= lista_iter_insertar(iter, &array[i]);
        ok &= lista_largo(lista) == i + 1;
        ok &= lista_ver_primero(lista) == &array[i];
    }
    print_test("Se agregaron 3 elementos", ok);
    ok = true;
    for (size_t i = 0; i < 3; i++) {
        ok &= lista_iter_ver_actual(iter) == lista_ver_primero(lista);
        ok &= lista_ver_primero(lista) == lista_iter_borrar(iter);
        ok &= lista_largo(lista) == 3 - i - 1;
    }
    print_test("Se eliminaron 3 elementos al principio", ok);   
    print_test("Lista está vacía", lista_esta_vacia(lista));

    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
}

static void prueba_iter_eliminar_medio(void) {
    printf("\nINICIO DE PRUEBAS ELIMINAR AL MEDIO\n");
    int array[] = {1,2,6};
    lista_t *lista = lista_crear();
    lista_iter_t *iter = lista_iter_crear(lista);
    
    bool ok = true;
    for (size_t i = 0; i < 3; i++) {
        ok &= lista_iter_insertar(iter, &array[i]);
        ok &= lista_largo(lista) == i + 1;
        ok &= lista_ver_primero(lista) == &array[i];
    }
    print_test("Se agregaron 3 elementos", ok);  
    print_test("Se avanza una posicion", lista_iter_avanzar(iter) && lista_iter_ver_actual(iter) == &array[1]);
    print_test("Se elimina al medio", lista_iter_borrar(iter) == &array[1] && lista_iter_ver_actual(iter) == &array[0]);
    
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
}

static void prueba_iter_eliminar_final(void) {
    printf("\nINICIO DE PRUEBAS ELIMINAR AL FINAL\n");
    int array[] = {1,2,6};
    lista_t *lista = lista_crear();
    lista_iter_t *iter = lista_iter_crear(lista);
    
    bool ok = true;
    for (size_t i = 0; i < 3; i++) {
        ok &= lista_iter_insertar(iter, &array[i]);
        ok &= lista_largo(lista) == i + 1;
        ok &= lista_ver_primero(lista) == &array[i];
    }
    print_test("se agregaron 3 elementos", ok);
    for (size_t i = 0; i < 2; i++) {
        ok &= lista_iter_avanzar(iter);
    }
    print_test("El iterador se encuentra en la última posición de la lista", ok && lista_iter_ver_actual(iter) == lista_ver_ultimo(lista));
    print_test("Se eliminó el último elemento", lista_iter_borrar(iter) == &array[0] && lista_ver_ultimo(lista) == &array[1]);

    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
}

static void prueba_lista_iter_vacio(void) {
    lista_t *lista = lista_crear();
    lista_iter_t *iter = lista_iter_crear(lista);
    print_test("Prueba crear lista vacía", iter);
    print_test("Prueba iter esta al final", lista_iter_al_final(iter));
    print_test("Prueba borrar es NULL", !lista_iter_borrar(iter));
    print_test("Prueba la lista está al principio", lista_iter_ver_actual(iter) == lista_ver_primero(lista));
    print_test("Avanzar es false", !lista_iter_avanzar(iter));
    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
}


static void pruebas_iter_externo(void) {
    prueba_iter_insertar_principio();
    prueba_iter_insertar_medio(); 
    prueba_iter_insertar_final(); 
    prueba_iter_eliminar_principio();
    prueba_iter_eliminar_medio(); 
    prueba_iter_eliminar_final(); 
    prueba_lista_iter_vacio();


}

bool factorial(void *dato, void *extra) {
    *(int*)extra *= *(int*)dato;
    return true;
}

bool pares(void *dato, void *extra) {
    if (*(int*)dato % 2 == 0)
        lista_insertar_ultimo((lista_t *)extra, dato);
    return true;
}

static void prueba_iter_interno_funcionamiento(void) {
    printf("\nINICIO DE PRUEBAS DE FUNCIONAMIENTO DE ITERADOR INTERNO\n");
    lista_t *lista = lista_crear();
    int array[] = {1,2,3,4,5};
    for (size_t i = 0; i < 5; i++) {
        lista_insertar_ultimo(lista, &array[i]);
    }
    int extra = 1;
    lista_iterar(lista, factorial, &extra);
    print_test("El factorial de 5 es 120", extra == 120);

    lista_destruir(lista, NULL);
}

static void prueba_iter_interno_con_corte(void) {
    printf("\nINICIO DE PRUEBAS DE ITERADOR INTERNO CON CORTE\n");
    lista_t *lista = lista_crear();
    int array[] = {1,6,4,23,324,24};
    for (size_t i = 0; i < 6; i++) {
        lista_insertar_ultimo(lista, &array[i]);
    }
    lista_t *aux = lista_crear();
    lista_iterar(lista, pares, aux);
    lista_iter_t *iter = lista_iter_crear(aux);
    bool ok = true;
    ok &= *(int*)lista_iter_ver_actual(iter) == array[1];
    ok &= lista_iter_avanzar(iter);
    ok &= *(int*)lista_iter_ver_actual(iter) == array[2];
    ok &= lista_iter_avanzar(iter);
    ok &= *(int*)lista_iter_ver_actual(iter) == array[4];
    ok &= lista_iter_avanzar(iter);
    ok &= *(int*)lista_iter_ver_actual(iter) == array[5];

    print_test("Funcionamiento iterador con corte", ok); 

    lista_destruir(lista, NULL);
    lista_iter_destruir(iter);
    lista_destruir(aux, NULL);
}

static void pruebas_iter_interno(void) {
    prueba_iter_interno_funcionamiento();
    prueba_iter_interno_con_corte();
}


void pruebas_lista_estudiante(void) {
    pruebas_lista();
    pruebas_iter_externo();
    pruebas_iter_interno();
}


/*
 * Función main() que llama a la función de pruebas.
 */
 
#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.


int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif