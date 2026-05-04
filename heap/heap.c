#include "heap.h"
#include <stdlib.h>

#define TAM_INIC 15
#define CAMBIO_CAPACIDAD 2
#define CONDICION_DISMINUCION 2

struct heap {
    void **datos;
    size_t cantidad;
    size_t tam;
    cmp_func_t cmp;
};

/* ******************************************************************
 *                       FUNCIONES AUXILIARES
 * *****************************************************************/



bool redimensionar_heap(heap_t *heap, size_t capacidad_actualizada){
    void* datos_nuevo = realloc(heap->datos, sizeof(void*) * capacidad_actualizada);
    if (datos_nuevo == NULL) {
        return false;
    }
    heap->datos = datos_nuevo;
    heap->tam = capacidad_actualizada;
    return true;
}



size_t pos_padre(size_t hijo) {
    return (hijo - 1) / 2;
}



void swap(void **datos, size_t padre, size_t hijo) {
    void *aux = datos[padre];
    datos[padre] = datos[hijo];
    datos[hijo] = aux;
}



void upheap(void **datos, size_t hijo, cmp_func_t cmp) {
    if (hijo <= 0) return;
    size_t padre = pos_padre(hijo);
    if (cmp(datos[padre], datos[hijo]) < 0) {
        swap(datos, padre, hijo);
        upheap(datos, padre, cmp);
    }
}



void downheap(void* arreglo[], size_t cantidad,size_t padre, cmp_func_t cmp) {
    size_t h_izq = 2 * padre + 1;
    size_t h_der = 2 * padre + 2;
    size_t h_max = padre;

    if (padre == cantidad) return;

    if (h_der < cantidad && h_izq < cantidad) {
        if (cmp(arreglo[h_izq],arreglo[h_der]) > 0) {
            h_max = h_izq;
        } else{
            h_max = h_der;
        }
    } else if (h_der < cantidad && h_izq >= cantidad) {
        h_max = h_der;
    } else if (h_izq < cantidad && h_der >= cantidad) {
        h_max = h_izq;
    }

    if (h_max != padre && cmp(arreglo[padre], arreglo[h_max]) < 0) {
        swap (arreglo, padre, h_max);
        downheap (arreglo, cantidad, h_max, cmp);
    }
}



void heapify(cmp_func_t cmp, void* arreglo[], size_t cantidad) {
    for (int i = (int)cantidad - 1; i >= 0; i--) {
        downheap(arreglo, cantidad, (size_t)i, cmp);
    }
}



/* ******************************************************************
 *                    PRIMITIVAS DEL HEAP
 * *****************************************************************/



heap_t *heap_crear(cmp_func_t cmp) {
    heap_t *heap = malloc(sizeof(heap_t));
    if (!heap) return NULL;
    heap->tam = TAM_INIC;
    heap->cantidad = 0;
    heap->datos = malloc(heap->tam * sizeof(void *));
    if (!heap->datos) {
        free(heap);
        return NULL;
    }
    heap->cmp = cmp;
    return heap;
}



heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
    heap_t *heap = heap_crear(cmp);
    if (n > heap->tam) {
        void **aux = NULL;
        aux = realloc(heap->datos, n * sizeof(void *));
        if (!aux){
            free(heap->datos);
            return NULL;
        }
        heap->datos = aux;
    }
    for (size_t i = 0; i < n; i++) {
        heap->datos[i] = arreglo[i];
    }
    
    heapify(cmp, heap->datos, n);

    heap->cantidad = n;

    return heap;
}



void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){
    if (destruir_elemento != NULL) {
        for (size_t i = 0; i < heap->cantidad; i++) {
            destruir_elemento(heap->datos[i]);
        }
    }
    free(heap->datos);
    free(heap);
}



size_t heap_cantidad(const heap_t *heap) {
    return heap->cantidad;
}



bool heap_esta_vacio(const heap_t *heap) {
    return !heap->cantidad;
}



bool heap_encolar(heap_t *heap, void *elem) {
    if (heap->cantidad == heap->tam) {
        bool redimension = redimensionar_heap(heap, heap->tam * CAMBIO_CAPACIDAD);
        if (!redimension){
            free(heap->datos);
            return false;
        }
    }

    heap->datos[heap->cantidad] = elem;
    heap->cantidad++;
    upheap(heap->datos, heap->cantidad - 1, heap->cmp);
    return true;
}



void *heap_ver_max(const heap_t *heap) {
    if (heap_esta_vacio(heap))
        return NULL;
    return heap->datos[0];
}



void* heap_desencolar(heap_t* heap) {
    if (heap_esta_vacio(heap)) return NULL;
    void* dato = heap->datos[0];

    if(heap->tam == heap->cantidad * CONDICION_DISMINUCION && heap->tam / CAMBIO_CAPACIDAD >= TAM_INIC){
        redimensionar_heap(heap, heap->tam / CAMBIO_CAPACIDAD);
    }

    if (heap->cantidad == 1) {
        heap->cantidad--;
        return dato;
    }

    swap(heap->datos, 0, heap->cantidad - 1);
    heap->cantidad--;
    downheap(heap->datos,heap->cantidad, 0, heap->cmp);
    return dato;
}



void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
    heapify(cmp, elementos, cant);

    for (int i = (int)cant - 1; i >= 0; i--) {
        swap(elementos, 0, (size_t)i);
        downheap(elementos, (size_t)i, 0, cmp);
    }
}
