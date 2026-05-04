#include "heap.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mayor(const void *a, const void *b) {
    if (a > b) return 1;
    if (a < b) return -1;
    return 0;
}

static void prueba_crear_heap_vacio() {
    printf("\nINICIO PRUEBAS CREAR HEAP VACIO\n");

    heap_t *heap = heap_crear(mayor);

    print_test("Prueba crear heap vacio", heap);
    print_test("El heap esta vacio", heap_esta_vacio(heap));
    print_test("La cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Desencolar es NULL", !heap_desencolar(heap));
    print_test("Ver el máximo es NULL", !heap_ver_max(heap));

    heap_destruir(heap, NULL);
}

static void prueba_heap_insertar() {
    printf("\nINICIO PRUEBAS HEAP ENCOLAR\n");
    heap_t *heap = heap_crear(mayor);
    int valores[] = {1,2,3,4,5};

    print_test("Insertar el valor 1", heap_encolar(heap, &valores[0]));
    print_test("Ver el máximo es 1", heap_ver_max(heap) == &valores[0]);
    print_test("El heap no esta vacio", !heap_esta_vacio(heap));
    print_test("La cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Insertar el valor 2", heap_encolar(heap, &valores[1]));
    print_test("Insertar el valor 3", heap_encolar(heap, &valores[2]));
    print_test("Ver el máximo es 3", heap_ver_max(heap) == &valores[2]);
    print_test("La cantidad de elementos es 3", heap_cantidad(heap) == 3);
    print_test("Insertar el valor 4", heap_encolar(heap, &valores[3]));
    print_test("Ver el máximo es 4", heap_ver_max(heap) == &valores[3]);
    print_test("La cantidad de elementos es 4", heap_cantidad(heap) == 4);
    print_test("Insertar el valor 5", heap_encolar(heap, &valores[4]));
    print_test("Ver el máximo es 5", heap_ver_max(heap) == &valores[4]);
    print_test("La cantidad de elementos es 5", heap_cantidad(heap) == 5);
    
    heap_destruir(heap, NULL);
}

static void prueba_heap_desencolar() {
    printf("\nINICIO DE PRUEBAS HEAP DESENCOLAR\n");
    heap_t* heap = heap_crear(mayor);
    int valores[] = {3, 5, 6, 7, 8, 9, 10, 15};
    print_test("Insertar valor", heap_encolar(heap, &valores[0]));
    print_test("Insertar valor", heap_encolar(heap, &valores[1]));
    print_test("Insertar valor", heap_encolar(heap, &valores[2]));
    print_test("Insertar valor", heap_encolar(heap, &valores[3]));
    print_test("Insertar valor", heap_encolar(heap, &valores[4]));
    print_test("Insertar valor", heap_encolar(heap, &valores[5]));
    print_test("Insertar valor", heap_encolar(heap, &valores[6]));
    print_test("Insertar valor", heap_encolar(heap, &valores[7]));

    print_test("El heap no esta vacio", !heap_esta_vacio(heap));
    print_test("La cantidad de elementos es 8", heap_cantidad(heap) == 8);

    print_test("desencolamos", heap_desencolar(heap) == &valores[7]);
    print_test("desencolamos", heap_desencolar(heap) == &valores[6]);
    print_test("desencolamos", heap_desencolar(heap) == &valores[5]);
    print_test("desencolamos", heap_desencolar(heap) == &valores[4]);
    print_test("desencolamos", heap_desencolar(heap) == &valores[3]);
    print_test("desencolamos", heap_desencolar(heap) == &valores[2]);
    print_test("desencolamos", heap_desencolar(heap) == &valores[1]);
    print_test("desencolamos", heap_desencolar(heap) == &valores[0]);

    print_test("La cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("El heap esta vacio", heap_esta_vacio(heap));


    heap_destruir(heap, NULL);
}

static void prueba_agregar_elemento_vacio() {
    printf("\nINICIO PRUEBA ABB ELEMENTO VACIO\n");
    heap_t *heap = heap_crear(mayor);
    char *elem = "";
    print_test("Insertar elemento vacío", heap_encolar(heap, elem));
    print_test("El heap no esta vacio", !heap_esta_vacio(heap));
    print_test("Ver el máximo es elemento vacío", heap_ver_max(heap) == elem);
    print_test("La cantidad de elementos es 1", heap_cantidad(heap) == 1);
    
    heap_destruir(heap, NULL);
}

static void prueba_agregar_elemento_NULL() {
    printf("\nINICIO PRUEBAS HEAP AGREGAR ELEMENTO NULL\n");
    heap_t *heap = heap_crear(mayor);
    print_test("Insertar NULL", heap_encolar(heap, NULL));
    print_test("El heap no esta vacio", !heap_esta_vacio(heap));
    print_test("Ver el máximo es NULL", heap_ver_max(heap) == NULL);
    print_test("La cantidad de elementos es 1", heap_cantidad(heap) == 1);
    
    heap_destruir(heap, NULL);
}

static void prueba_heap_volumen(size_t largo, bool debug) {
    printf("\nINICIO PRUEBAS HEAP VOLUMEN\n");
    heap_t *heap = heap_crear(mayor);
    int valores[largo];
    bool ok = true;
    for (size_t i = 0; i < largo; i++) {
        valores[i] = rand() % (int)largo;
        ok = heap_encolar(heap, &valores[i]);
        if (!ok) break;
    }
    if (debug) print_test("Prueba heap almacenar muchos elementos", ok);
    if (debug) print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == largo);
    
    heap_destruir(heap, NULL);

    heap_t *heap_2 = heap_crear(mayor);
    int valores_2[largo];
    bool ok_2 = true;
    for (size_t i = 0; i < largo; i++) {
        valores_2[i] = (int)i;
        ok_2 = heap_encolar(heap_2, &valores_2[i]);
        if (!ok_2) break;
        ok_2 = heap_ver_max(heap_2) == &valores_2[i];
        if (!ok_2) break;
    }
    if (debug) print_test("Prueba heap almacenar muchos elementos", ok_2);
    if (debug) print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap_2) == largo);
    
    heap_destruir(heap_2, NULL);

    heap_t *heap_3 = heap_crear(mayor);
    int *valores_3[largo];
    for (size_t i = 0; i < largo; i++) {
        valores_3[i] = malloc(sizeof(int));
        *valores_3[i] = (int)i;
    }
    
    bool ok_3 = true;
    for (size_t i = 0; i < largo; i++) {
        ok_3 = heap_encolar(heap_3, valores_3[i]);
        if (!ok_3) break;
        ok_3 = heap_ver_max(heap_3) == valores_3[i];
        if (!ok_3) break;
    }
    if (debug) print_test("Prueba heap almacenar muchos elementos", ok_3);
    if (debug) print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap_3) == largo);

    heap_destruir(heap_3, free);

}

static void prueba_destruir_heap_vacia_con_NULL() {
    printf("\nINICIO DE PRUEBAS DESTRUIR HEAP VACIO CON NULL\n");
    heap_t* heap = heap_crear(mayor);

    print_test("El heap esta vacio", heap_esta_vacio(heap));
    heap_destruir(heap, NULL);
    print_test("El heap se destruyo", true);
}

static void prueba_destruir_heap_vacia_con_free() {
    printf("\nINICIO DE PRUEBAS DESTRUIR HEAP VACIO CON FREE\n");
    heap_t* heap = heap_crear(mayor);

    print_test("El heap esta vacio", heap_esta_vacio(heap));
    heap_destruir(heap, free);
    print_test("El heap se destruyo", true);
}

static void prueba_destruir_heap_no_vacia_con_NULL() {
    printf("\nINICIO DE PRUEBAS DESTRUIR HEAP NO VACIA CON NULL\n");

    heap_t* heap = heap_crear(mayor);
    int array[] = {1,2,6};

    print_test("Insertar elemento", heap_encolar(heap, &array[0]));
    print_test("Insertar elemento", heap_encolar(heap, &array[1]));
    print_test("Insertar elemento", heap_encolar(heap, &array[2]));

    heap_destruir(heap, NULL);
    print_test("el heap se destruyo", true);
}

static void prueba_destruir_heap_no_vacia_con_free() {
    printf("\nINICIO DE PRUEBAS DESTRUIR HEAP NO VACIA CON FREE()\n");

    int* a = malloc(sizeof(int));
    int* b = malloc(sizeof(int));
    int* c = malloc(sizeof(int));

    heap_t* heap = heap_crear(mayor);

    print_test("Insertar elemento", heap_encolar(heap, a));
    print_test("Insertar elemento", heap_encolar(heap, b));
    print_test("Insertar elemento", heap_encolar(heap, c));

    heap_destruir(heap, free);
    print_test("el heap se destruyo", true);
}


void pruebas_heap_estudiante()
{
    /* Ejecuta todas las pruebas unitarias. */
    prueba_crear_heap_vacio();
    prueba_heap_insertar();
    prueba_heap_desencolar();
    prueba_agregar_elemento_vacio();
    prueba_agregar_elemento_NULL();
    prueba_heap_volumen(1000, true);
    prueba_destruir_heap_vacia_con_NULL();
    prueba_destruir_heap_vacia_con_free();
    prueba_destruir_heap_no_vacia_con_NULL();
    prueba_destruir_heap_no_vacia_con_free();
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.


int main(void) {
    pruebas_heap_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif

