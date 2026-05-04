#include "cola.h"
#include "testing.h"
#include "pila.h"
#include <stdio.h>
#include <stdlib.h>

/*Pruebas para una cola de tamaño 0*/
static void prueba_cola_vacia(void) {
    
    /*Declaro variables a utilizar*/
    cola_t *cola = cola_crear();

    printf("\nCOMIENZAN LAS PRUEBAS DE COLA VACÍA\n");
    
    /*pruebo que al crear una cola se cree vacía*/
    print_test("Ver que la cola está vacía", cola_esta_vacia(cola));
    
    /*Pruebo que desencolar una cola vacía devuelve NULL*/
    print_test("Ver que desencolar una cola vacía es NULL", !cola_desencolar(cola));
    
    /*Pruebo que ver el primero de una cola vacía devuelve NULL*/
    print_test("Ver que el primero de una cola vacía es NULL", !cola_ver_primero(cola));

    /*Destruyo la cola*/
    cola_destruir(cola, NULL);

}

/*Pruebas para una cola de 1 elemento*/
static void prueba_cola_1_elemento(void) {
    /*Declaro variables a utilizar*/
    cola_t *cola = cola_crear();
    int a = 5;

    printf("\nCOMIENZAN LAS PRUEBAS DE COLA CON UN ELEMENTO\n");

    /*Encolo un elemento*/
    print_test("Encolar a", cola_encolar(cola, &a));
    print_test("Ver que la cola no está vacía", !cola_esta_vacia(cola));
    print_test("Ver que a es el primer elemento", cola_ver_primero(cola) == &a);
    
    /*Desencolo el elemento*/
    print_test("Desencolar a", cola_desencolar(cola) == &a);

    /*Pruebo que se comporte como una pila vacía*/
    print_test("Ver que la cola está vacía", cola_esta_vacia(cola));
    print_test("Ver que desencolar una cola vacía es NULL", !cola_desencolar(cola));
    print_test("Ver que el primero de una cola vacía es NULL", !cola_ver_primero(cola));

    /*Destruyo la cola*/
    cola_destruir(cola, NULL);

}

/*Pruebas para una cola de varios elementos*/
static void prueba_cola_varios_elementos(void) {

    /*Declaro variables a utilizar*/
    cola_t *cola = cola_crear();
    int a = 5, b = 6, c = 7;

    printf("\nCOMIENZAN LAS PRUEBAS DE COLA CON VARIOS ELEMENTOS\n");

    /*Encolo 3 elementos*/
    print_test("Encolar a", cola_encolar(cola, &a));
    print_test("Ver que a es el primer elemento", cola_ver_primero(cola) == &a);
    print_test("Encolar b", cola_encolar(cola, &b));
    print_test("Ver que a es el primer elemento", cola_ver_primero(cola) == &a);
    print_test("Encolar c", cola_encolar(cola, &c));

    /*Desencolo los 3 elementos y verifico el primer elemento de la cola*/
    print_test("Desencolar a", cola_desencolar(cola) == &a);
    print_test("Ver que b es el primer elemento", cola_ver_primero(cola) == &b);
    print_test("Desencolar b", cola_desencolar(cola) == &b);
    print_test("Ver que c es el primer elemento", cola_ver_primero(cola) == &c);
    print_test("Desencolar c", cola_desencolar(cola) == &c);
    
    /*Veo que la pila esté vacía*/
    print_test("Ver que la cola está vacía", cola_esta_vacia(cola));
    
    /*Destruyo la cola*/
    cola_destruir(cola, NULL);

}

/*Pruebas para una cola de muchos elementos*/
static void prueba_cola_volumen(void) {
    
    /*Declaro variables a utilizar*/
    cola_t *cola = cola_crear();
    size_t tam = 2000;
    int valores[tam];
    for (size_t i = 0; i < tam; i++) {
        valores[i] = (int)i + rand()%11; //genero números random del 1 al 10 y le sumo i
    }

    printf("\nCOMIENZAN LAS PRUEBAS DE VOLUMEN\n");

    bool ok = true;
    /*encolo 2000 veces*/
    for (size_t i = 0; i < tam; i++) {
        ok &= cola_encolar(cola, &valores[i]);
    }
    print_test("Se pudieron encolar todos los elementos", ok);

    ok = true;
    /*Desencolo 2000 veces*/
    for (size_t i = 0; i < tam; i++) {
        ok &= (cola_ver_primero(cola) == &valores[i]);
        ok &= (cola_desencolar(cola) == &valores[i]);
    }

    print_test("Se pudieron desencolar todos los elementos", ok);

    /*Pruebo que la cola esté vacía*/
    print_test("Ver que la cola está vacía", cola_esta_vacia(cola));    

    /*Destruyo la cola*/
    cola_destruir(cola, NULL);

}

/*Pruebas para una encolar null*/
static void prueba_cola_null(void) {
    /*Declaro variables a utilizar*/
    cola_t *cola = cola_crear();
    int a = 5, b = 6;
    int *c = NULL;
    char *d = NULL;

    printf("\nCOMIENZAN LAS PRUEBAS DE PUNTERO A NULL\n");

    /*Encolo 4 elementos, entre ellos 2 son NULL*/
    print_test("Encolo NULL", cola_encolar(cola, c));
    print_test("Ver que NULL es el primer elemento", cola_ver_primero(cola) == c);
    print_test("Encolo a", cola_encolar(cola, &a));
    print_test("Encolo b", cola_encolar(cola, &b));
    print_test("Encolo d", cola_encolar(cola, d));
    print_test("Ver que NULL es el primer elemento", cola_ver_primero(cola) == c);

    /*Desncolo los 4 elementos y voy verificando el primer elemento de la cola*/
    print_test("Desencolo NULL", cola_desencolar(cola) == c);
    print_test("Ver que a es el primer elemento", cola_ver_primero(cola) == &a);
    print_test("Desencolo a", cola_desencolar(cola) == &a);
    print_test("Ver que b es el primer elemento", cola_ver_primero(cola) == &b);
    print_test("Desencolo b", cola_desencolar(cola) == &b);
    print_test("Ver que NULL es el primer elemento", cola_ver_primero(cola) == d);
    print_test("Desencolo NULL", cola_desencolar(cola) == d);

    /*Veo que la cola esté vacía*/
    print_test("Ver que la cola está vacía", cola_esta_vacia(cola));

    /*Destruyo la cola*/
    cola_destruir(cola, NULL);

}

/*Es una función auxiliar que llena un vector de n elementos*/
void llenar_vector(int *x, int tam) {
    for (size_t i = 0; i < tam; i++) {
        x[i] = (int)i + rand()%11;
    }
}

/*Esta prueba es para probar cola_destruir con free, por eso no se desencolan*/
static void prueba_cola_vectores_dinamicos(void) {
    
    /*Declaro variables a utilizar*/
    cola_t *cola = cola_crear();
    size_t tam = 50;
    int *x[tam];
    int tams[tam];
    llenar_vector(tams, (int)tam);
    for (size_t i = 0; i < tam; i++) {
        x[i] = malloc((size_t)tams[i] * sizeof(int));
        llenar_vector(x[i], tams[i]);
    }

    printf("\nCOMIENZAN LAS PRUEBAS DE ENCOLAR VECTORES DINÁMICOS\n");
    
    bool ok = true;
    for (size_t i = 0; i < tam; i++) {
        ok &=cola_encolar(cola, x[i]);
    }
    /*Encolo todos los vectores*/
    print_test("Se pudieron encolar todos los elementos", ok);
    
    /*Destruyo la cola*/
    cola_destruir(cola, free);

}

/*Wrapper para poder utilizar pila_destruir*/
void _pila_destruir(void *pila) {
    pila_destruir(pila);
}

/*Esta prueba es para probar cola_destruir con pila_destruir, por eso no se desencolan*/

static void prueba_cola_pila(void) {
    /*Declaro las variables a utilizar*/
    cola_t *cola = cola_crear();
    pila_t *pila1 = pila_crear();
    pila_t *pila2 = pila_crear();
    pila_t *pila3 = pila_crear();
    pila_t *pila4 = pila_crear();

    printf("\nCOMIENZAN LAS PRUEBAS DE ENCOLAR PILAS\n");

    /*Encolo las 4 pilas*/
    print_test("Encolo pila 1", cola_encolar(cola, pila1));
    print_test("Encolo pila 2", cola_encolar(cola, pila2));
    print_test("Encolo pila 3", cola_encolar(cola, pila3));
    print_test("Encolo pila 4", cola_encolar(cola, pila4));

    /*Destruyo la cola*/
    cola_destruir(cola, _pila_destruir);

}


void pruebas_cola_estudiante(){
    prueba_cola_vacia();
    prueba_cola_1_elemento();
    prueba_cola_varios_elementos();
    prueba_cola_volumen();
    prueba_cola_null();
    prueba_cola_vectores_dinamicos();
    prueba_cola_pila();
}

size_t largo_cola(cola_t *cola) {
    cola_t *aux = cola;
    size_t largo = 0;
    while(!cola_esta_vacia(aux)) {
        cola_desencolar(aux);
        largo++;
    }
    return largo;
}    
/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    //pruebas_cola_estudiante();
    //return failure_count() > 0;  // Indica si falló alguna prueba.
    cola_t *cola = cola_crear();
    size_t n = 16;
    int arr[16]={0,1,2,3,4,5,6,7,8,9,21,12,23,213,12,3};
    for (size_t i = 0; i < n; i++) {
        cola_encolar(cola, &arr[i]);
    }
    if(cola_ver_primero(cola)==&arr[0])
        printf("ok\n");
    printf("largo cola= %ld\n", largo_cola(cola));
    cola_destruir(cola, NULL);    
}

#endif
