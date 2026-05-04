#include "pila.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>

/*Pruebas para una pila de tamaño 0*/
static void prueba_pila_vacia(void) {
    
    /*Declaro variables a utilizar*/
    pila_t *pila = pila_crear();

    printf("\nCOMIENZAN LAS PRUEBAS DE PILA VACÍA\n");
    
    /*pruebo que al crear una pila se cree vacía*/
    print_test("Ver que la pila está vacía", pila_esta_vacia(pila));
    
    /*Pruebo que desapilar una pila vacía devuelve NULL*/
    print_test("Ver que desapilar pila vacía es NULL", !pila_desapilar(pila));
    
    /*Pruebo que ver el tope de una pila vacía devuelve NULL*/
    print_test("Ver que tope de una pila vacía es NULL", !pila_ver_tope(pila));

    /*Destruyo la pila*/
    pila_destruir(pila);

}

/*Pruebas de la pila al apilar y desapilar un solo elemento*/
static void prueba_pila_1_elemento(void) {
    
    /*Declaro variables a utilizar*/
    pila_t *pila = pila_crear();
    int a = 5;

    printf("\nCOMIENZAN LAS PRUEBAS DE APILAR Y DESAPILAR UN ELEMENTO\n");
    
    /*Pruebo que al apilar un elemento, ese elemento sea el tope 
    y que la pila ya no esté vacía*/
    print_test("Apilar a", pila_apilar(pila, &a));
    print_test("Ver que tope de pila es a", pila_ver_tope(pila) == &a);
    print_test("Probar que la pila no está vacía", !pila_esta_vacia(pila));
    
    /*Pruebo que al desapilar me devuelva el valor del tope y 
    que la pila esté vacía*/
    print_test("Desapilar a", pila_desapilar(pila) == &a);

    /*Pruebo que se comporte como una pila vacía*/
    print_test("Ver que la pila está vacía", pila_esta_vacia(pila));
    print_test("Ver que desapilar pila vacía es NULL", !pila_desapilar(pila));
    print_test("Ver que tope de una pila vacía es NULL", !pila_ver_tope(pila));

    /*Destruyo la pila*/
    pila_destruir(pila);    
}

static void prueba_pila_varios_elementos(void) {
    /*Declaro variables a utilizar*/
    pila_t *pila = pila_crear();
    int a = 5, b = 8, c = 134;

    printf("\nCOMIENZAN LAS PRUEBAS DE APILAR Y DESAPILAR VARIOS ELEMENTOS\n");

    /*Pruebo apilando 3 elementos y viendo los topes cada vez que apilo*/
    print_test("Apilar a", pila_apilar(pila, &a));
    print_test("Ver que tope de pila es a", pila_ver_tope(pila) == &a);

    print_test("Apilar b", pila_apilar(pila, &b));
    print_test("Ver que tope de pila es b", pila_ver_tope(pila) == &b);
    
    print_test("Apilar c", pila_apilar(pila, &c));
    print_test("Ver que tope de pila es c", pila_ver_tope(pila) == &c);

    /*Pruebo desapilando 3 elementos y viendo los topes cada vez que desapilo*/
    print_test("Desapilar c", pila_desapilar(pila) == &c);
    print_test("Ver que tope de pila es b", pila_ver_tope(pila) == &b);
    
    print_test("Desapilar b", pila_desapilar(pila) == &b);
    print_test("Ver que tope de pila es a", pila_ver_tope(pila) == &a);

    print_test("Desapilar a", pila_desapilar(pila) == &a);
    print_test("Ver que la pila está vacía", pila_esta_vacia(pila));

    /*Destruyo la pila*/
    pila_destruir(pila);
}

/* Pruebas de la pila al trabajar con un volumen grande de elementos */
static void prueba_pila_volumen(void) {
    
    /*Declaro variables a utilizar*/
    pila_t *pila = pila_crear();
    size_t tam = 2000;
    int valores[tam];
    for (size_t i = 0; i < tam; i++) {
        valores[i] = (int)i + rand()%11; //genero números random del 1 al 10 le sumo i
    }
    
    printf("\nCOMIENZAN LAS PRUEBAS DE VOLUMEN\n");
    
    bool ok = true;
    /*apilo 2000 veces*/
    for (size_t i = 0; i < tam; i++) {
        ok &= pila_apilar(pila, &valores[i]);
        ok &= (pila_ver_tope(pila) == &valores[i]);
    }
    print_test("Se pudieron apilar todos los elementos", ok);
    
    ok = true;
    /*Desapilo 2000 veces*/
    for (size_t i = 0; i < tam; i++) {
        if(i == tam - 1)    //esta condicón es para que ver tope no ingrese a una dirección prohibida
            break;
        ok &= (pila_desapilar(pila) == &valores[tam - 1 - i]);
        ok &= (pila_ver_tope(pila) == &valores[tam - 2 - i]);
        
    }
    ok &= (pila_desapilar(pila) == &valores[0]);    //desapilo el último elemento
    ok &= (!pila_ver_tope(pila));   //veo que sea NULL el nuevo tope porque la pila está vacía

    print_test("Se pudieron desapilar todos los elementos", ok);

    /*Pruebo que la pila esté vacía*/
    print_test("Ver que la pila está vacía", pila_esta_vacia(pila));    
    
    /*Destruyo la pila*/
    pila_destruir(pila);   
}

static void prueba_pila_null(void) {
    
    /*Declaro variables a utilizar*/
    pila_t *pila = pila_crear();
    int *p;
    p = NULL;
    int a = 6;

    printf("\nCOMIENZAN LAS PRUEBAS DE PUNTERO A NULL\n");

    print_test("Apilo a", pila_apilar(pila, &a));
    print_test("Ver que tope de pila es a", pila_ver_tope(pila) == &a);
    print_test("Apilo NULL", pila_apilar(pila, p));
    print_test("Ver que tope de pila es NULL", pila_ver_tope(pila) == p);
    print_test("Ver que la pila no está vacía", !pila_esta_vacia(pila));
    print_test("Desapilar NULL", pila_desapilar(pila) == p);
    print_test("Ver que tope de pila es a", pila_ver_tope(pila) == &a);

    /*Destruyo la pila*/
    pila_destruir(pila);   
}


void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_pila_1_elemento();
    prueba_pila_varios_elementos();
    prueba_pila_volumen();
    prueba_pila_null();

}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
