#include "abb.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void prueba_crear_abb_vacio() {
    printf("\nINICIO PRUEBAS CREAR ABB VACIO\n");

    abb_t* abb = abb_crear(strcmp, NULL);

    print_test("Prueba crear abb vacio", abb);
    print_test("El abb esta vacio", abb_cantidad(abb) == 0);
    print_test("Obtener clave A, es NULL, no existe", !abb_obtener(abb,"A"));
    print_test("Pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

    abb_destruir(abb);
}

static void prueba_abb_insertar() {
    printf("\nINICIO PRUEBAS ABB INSERTAR\n");

    abb_t* abb = abb_crear(strcmp, NULL);
    int valores[] = {1,2,3,4,5};

    print_test("Insertar el elemento hola", abb_guardar(abb, "hola", &valores[0]));
    print_test("Obtener clave hola", abb_obtener(abb, "hola") == &valores[0]);
    print_test("Pertenece clave hola", abb_pertenece(abb, "hola"));

    print_test("Insertar el elemento como", abb_guardar(abb, "como", &valores[1]));
    print_test("Obtener clave como", abb_obtener(abb, "como") == &valores[1]);
    print_test("Pertenece clave como", abb_pertenece(abb, "como"));

    print_test("Insertar el elemento andas", abb_guardar(abb, "andas", &valores[2]));
    print_test("Obtener clave andas", abb_obtener(abb, "andas") == &valores[2]);
    print_test("Pertenece clave andas", abb_pertenece(abb, "andas"));

    print_test("Insertar el elemento todo", abb_guardar(abb, "todo", &valores[3]));
    print_test("Obtener clave todo", abb_obtener(abb, "todo") == &valores[3]);
    print_test("Pertenece clave todo", abb_pertenece(abb, "todo"));

    print_test("Insertar el elemento bien", abb_guardar(abb, "bien", &valores[4]));
    print_test("Obtener clave bien", abb_obtener(abb, "bien") == &valores[4]);
    print_test("Pertenece clave bien", abb_pertenece(abb, "bien"));

    abb_destruir(abb);
}

static void prueba_abb_reemplazar(){
    printf("\nINICIO PRUEBAS ABB REEMPLAZAR\n");

    abb_t* abb = abb_crear(strcmp, NULL);
    int valores[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    print_test("Insertar el elemento hola", abb_guardar(abb, "hola", &valores[0]));
    print_test("Obtener clave hola", abb_obtener(abb, "hola") == &valores[0]);
    print_test("Pertenece clave hola", abb_pertenece(abb, "hola"));

    print_test("Reemplazamos el elemento hola", abb_guardar(abb, "hola", &valores[1]));
    print_test("Obtener clave hola devuelve el nuevo elemento", abb_obtener(abb, "hola") == &valores[1]);
    print_test("Pertenece clave hola", abb_pertenece(abb, "hola"));

    print_test("Insertar el elemento como", abb_guardar(abb, "como", &valores[2]));
    print_test("Obtener clave como", abb_obtener(abb, "como") == &valores[2]);
    print_test("Pertenece clave como", abb_pertenece(abb, "como"));

    print_test("Reemplazamos el elemento como", abb_guardar(abb, "como", &valores[3]));
    print_test("Obtener clave como devuelve el nuevo elemento", abb_obtener(abb, "como") == &valores[3]);
    print_test("Pertenece clave como", abb_pertenece(abb, "como"));

    print_test("Insertar el elemento andas", abb_guardar(abb, "andas", &valores[4]));
    print_test("Obtener clave andas", abb_obtener(abb, "andas") == &valores[4]);
    print_test("Pertenece clave andas", abb_pertenece(abb, "andas"));

    print_test("Reemplazamos el elemento andas", abb_guardar(abb, "andas", &valores[5]));
    print_test("Obtener clave andas devuelve el nuevo elemento", abb_obtener(abb, "andas") == &valores[5]);
    print_test("Pertenece clave andas", abb_pertenece(abb, "andas"));

    print_test("Insertar el elemento todo", abb_guardar(abb, "todo", &valores[6]));
    print_test("Obtener clave todo", abb_obtener(abb, "todo") == &valores[6]);
    print_test("Pertenece clave todo", abb_pertenece(abb, "todo"));

    print_test("Reemplazamos el elemento todo", abb_guardar(abb, "todo", &valores[7]));
    print_test("Obtener clave todo devuelve el nuevo elemento", abb_obtener(abb, "todo") == &valores[7]);
    print_test("Pertenece clave todo", abb_pertenece(abb, "todo"));

    print_test("Insertar el elemento bien", abb_guardar(abb, "bien", &valores[8]));
    print_test("Obtener clave bien", abb_obtener(abb, "bien") == &valores[8]);
    print_test("Pertenece clave bien", abb_pertenece(abb, "bien"));

    print_test("Reemplazamos el elemento bien", abb_guardar(abb, "bien", &valores[9]));
    print_test("Obtener clave bien devuelve el nuevo elemento", abb_obtener(abb, "bien") == &valores[9]);
    print_test("Pertenece clave bien", abb_pertenece(abb, "bien"));

    abb_destruir(abb);
}

static void prueba_abb_reemplazar_con_destruir() {
    printf("\nINICIO PRUEBAS ABB REEMPLAZAR CON DESTRUIR\n");

    abb_t* abb = abb_crear(strcmp, free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    print_test("Abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Abb clave1 pertenece", abb_pertenece(abb, clave1));
    print_test("Abb obtener clave1", abb_obtener(abb, clave1) == valor1a);

    print_test("Abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Abb clave2 pertenece", abb_pertenece(abb, clave2));
    print_test("Abb obtener clave2", abb_obtener(abb, clave2) == valor2a);

    print_test("Abb cantidad es 2", abb_cantidad(abb) == 2);

    print_test("Abb reemplazar valor clave1", abb_guardar(abb, clave1, valor1b));
    print_test("Abb clave1 pertenece", abb_pertenece(abb, clave1));
    print_test("Abb obtener clave1", abb_obtener(abb, clave1) == valor1b);

    print_test("Abb reemplazar valor clave2", abb_guardar(abb, clave2, valor2b));
    print_test("Abb clave2 pertenece", abb_pertenece(abb, clave2));
    print_test("Abb obtener clave2", abb_obtener(abb, clave2) == valor2b);

    print_test("Abb cantidad es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

static void prueba_abb_borrar(){
    printf("\nINICIO PRUEBAS ABB BORRAR\n");

    abb_t* abb = abb_crear(strcmp, NULL);
    char* clave1 = "h";
    char* clave2 = "i";
    char* clave3 = "c";
    char* clave4 = "j";
    char* clave5 = "a";
    char* clave6 = "d";
    char* clave7 = "b";
    int valores[] = {1,2,3,4,5,6,7};

    print_test("Abb insertar clave1", abb_guardar(abb, clave1, &valores[0]));
    print_test("Abb insertar clave2", abb_guardar(abb, clave2, &valores[1]));
    print_test("Abb insertar clave3", abb_guardar(abb, clave3, &valores[2]));
    print_test("Abb insertar clave4", abb_guardar(abb, clave4, &valores[3]));
    print_test("Abb insertar clave5", abb_guardar(abb, clave5, &valores[4]));
    print_test("Abb insertar clave6", abb_guardar(abb, clave6, &valores[5]));
    print_test("Abb insertar clave7", abb_guardar(abb, clave7, &valores[6]));

    print_test("abb cantidad es 7", abb_cantidad(abb) == 7);

    print_test("clave4 pertenece", abb_pertenece(abb, clave4));
    print_test("obtener clave4", abb_obtener(abb, clave4) == &valores[3]);

    print_test("Borrar nodo sin hijo", abb_borrar(abb, clave4) == &valores[3]);
    print_test("clave4 ya no pertenece", !abb_pertenece(abb, clave4));

    print_test("Borrar nodo con un hijo", abb_borrar(abb, clave5) == &valores[4]);
    print_test("clave5 ya no pertenece", !abb_pertenece(abb, clave5));
    print_test("clave7 sigue perteneciendo", abb_pertenece(abb, clave7));

    print_test("abb cantidad es 5", abb_cantidad(abb) == 5);

    print_test("Borrar nodo clave2",abb_borrar(abb, clave2) == &valores[1]);
    print_test("clave2 ya no pertenece", !abb_pertenece(abb, clave2));

    print_test("abb cantidad es 4", abb_cantidad(abb) == 4);

    print_test("Borrar raiz con 1 hijo", abb_borrar(abb, clave1) == &valores[0]);
    print_test("clave1 ya no pertenece", !abb_pertenece(abb, clave1));
    print_test("clave7 sigue perteneciendo", abb_pertenece(abb, clave7));
    print_test("clave6 sigue perteneciendo", abb_pertenece(abb, clave6));

    print_test("abb cantidad es 3", abb_cantidad(abb) == 3);

    print_test("Borrar nodo con dos hijos, ademas es nodo raiz", abb_borrar(abb, clave3) == &valores[2]);
    print_test("clave3 ya no pertenece", !abb_pertenece(abb, clave3));
    print_test("clave7 sigue perteneciendo", abb_pertenece(abb, clave7));
    print_test("clave6 sigue perteneciendo", abb_pertenece(abb, clave6));

    print_test("abb cantidad es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

static void prueba_abb_clave_vacia() {
    printf("\nINICIO PRUEBA ABB CLAVE VACIA\n");

    abb_t* abb = abb_crear(strcmp, NULL);
    char *clave = "", *valor = "";

    print_test("abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("abb obtener clave vacia", abb_obtener(abb, clave) == valor);
    print_test("abb clave pertenece", abb_pertenece(abb,clave));
    print_test("abb borrar clave vacia", abb_borrar(abb, clave) == valor);
    print_test("La cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_valor_null() {
    printf("\nINICIO PRUEBA ABB VALOR NULL\n");

    abb_t* abb = abb_crear(strcmp, NULL);
    char *clave = "", *valor = NULL;

    print_test("abb insertar clave vacia con valor NULL", abb_guardar(abb, clave, valor));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("abb clave pertenece", abb_pertenece(abb,clave));
    print_test("abb borrar clave vacia es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("La cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_volumen(size_t largo, bool debug) {
    printf("\nINICIO PRUEBA ABB VOLUMEN\n");

    abb_t* abb = abb_crear(strcmp, NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    unsigned* valores[largo];

    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb borrar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
    abb = abb_crear(strcmp, free);

    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    free(claves);

    abb_destruir(abb);
}

static void prueba_iterar_abb_vacio() {
    abb_t* abb = abb_crear(strcmp, NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iter crear iterador abb vacio", iter);
    print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static ssize_t buscar(const char* clave, char* claves[], size_t largo) {
    for (size_t i = 0; i < largo; i++) {
        if (strcmp(clave, claves[i]) == 0) return (ssize_t) i;
    }
    return -1;
}

static void prueba_abb_iterar() {
    abb_t* abb = abb_crear(strcmp, NULL);

    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};

    /* Inserta 3 valores */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    const char *clave;
    ssize_t indice;

    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Primer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Segundo valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Tercer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    abb_iter_in_avanzar(iter);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    /* Vuelve a tratar de avanzar, por las dudas */
    print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static void prueba_hash_iterar_volumen(size_t largo) {
    abb_t* abb = abb_crear(strcmp, NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t valores[largo];

    /* Inserta 'largo' parejas en el hash */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        sprintf(claves[i], "%08d", i);
        valores[i] = i;
        ok = abb_guardar(abb, claves[i], &valores[i]);
        if (!ok) break;
    }

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;

    for (i = 0; i < largo; i++) {
        if ( abb_iter_in_al_final(iter) ) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if ( clave == NULL ) {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if ( valor == NULL ) {
            ok = false;
            break;
        }
        *valor = largo;
        abb_iter_in_avanzar(iter);
    }
    print_test("Prueba abb iteración en volumen", ok);
    print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == largo);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    ok = true;
    for (i = 0; i < largo; i++) {
        if ( valores[i] != largo ) {
            ok = false;
            break;
        }
    }
    print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);

    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}


void pruebas_abb_estudiante()
{
    /* Ejecuta todas las pruebas unitarias. */
    prueba_crear_abb_vacio();
    prueba_iterar_abb_vacio();
    prueba_abb_insertar();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_con_destruir();
    prueba_abb_borrar();
    prueba_abb_clave_vacia();
    prueba_abb_valor_null();
    prueba_abb_volumen(1000, true);
    prueba_abb_iterar();
    prueba_hash_iterar_volumen(1000);
}

#ifndef CORRECTOR

int main() {
    pruebas_abb_estudiante();
    return failure_count() > 0;
}

#endif