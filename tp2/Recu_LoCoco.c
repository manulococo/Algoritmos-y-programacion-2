#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool cierra(char a, char b) {
    if ((a == '{' && b == '}') || (a == '(' && b == ')') || (a == '[' && b == ']')) {
        return true;
    }
    else return false;
}

bool esta_balanceada(char *a) {
    if (strlen(a) % 2 == 1)
        return false;
    pila_t *pila = pila_crear();
    for (size_t i = 0; i < strlen(a); i++) {
        if (pila_esta_vacia(pila)) {
            pila_apilar(pila, &a[i]);
            continue;
        }     
        else if (cierra(*(char*)pila_ver_tope(pila), a[i])) {
            pila_desapilar(pila);
            continue;
        }
        pila_apilar(pila, &a[i]);
    }
    if (pila_esta_vacia(pila))
        pila_destruir(pila);
        return true;
    pila_destruir(pila);
    else return false;
}
size_t _cant_de_unos(int arreglo[], size_t inicio, size_t fin) {
    size_t medio = (inicio + fin)/2;
    if (inicio == fin)
        return arreglo[medio];
    return _cant_de_unos(arreglo, inicio, medio) + _cant_de_unos(arreglo, medio + 1, fin);
}

size_t cant_de_unos(int arreglo[], size_t n) {
    if (n == 0)
        return 0;
    return _cant_de_unos(arreglo, 0, n - 1);
}

int main() {
    char *a = "[({}{}[(){}])]";
    esta_balanceada(a)? printf("está balanceada\n"): printf("no está balanceada\n");
}


/*
Ejercicio 3:

a- Falso, siempre debe ser estable porque es necesario para que funcione correctamente. Porque por ejemplo
en el caso que se ordenan por 2 cifras, primero se ordenan por unidades y luego por decenas. Si por ejemplo
primero obtenemos 12, 15, 28, 39 y luego usamos un algoritmo no estable se podría llegar a tener 
15, 12, 28, 39. 

b- Falso, porque ya llama recursivamente todo el tiempo, no importa si está ordenado o no.
Al estar ordenado, nunca va a hacer el swap pero si va a hacer los llamados recursivos y eso no es O(1)

c- Falso, Counting sort tiene una complejidad O(n + k) y Radix sort tiene O(d*(n + k)). Por ende, jamás tendrá 
menos complejidad Counting sort. Además, Radix sort realiza d-veces counting sort

*/
