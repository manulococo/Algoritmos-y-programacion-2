#include "hash.h"
#define CAPACIDAD 37
#define STR 30
#define REDIM 2
#include <stdlib.h>
#include <string.h>

typedef enum estado {OCUPADO, VACIO, BORRADO} estado_t;

typedef struct campo {
    void *dato;
    char *clave;
    estado_t estado;
} campo_t;

struct hash {
    campo_t *tabla;
    size_t capacidad;
    size_t largo;
    hash_destruir_dato_t destruccion;
};

/* ******************************************************************
 *                      PRIMITIVAS DEL HASH
 * *****************************************************************/

hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
    hash_t *hash = malloc(sizeof(hash_t));
    if (!hash)
        return NULL;
    hash->tabla = malloc(sizeof(campo_t) * CAPACIDAD);
    hash->capacidad = CAPACIDAD;
    hash->largo = 0;
    hash->destruccion = destruir_dato;
    for (size_t i = 0; i < hash->capacidad; i++) {
        hash->tabla[i].estado = VACIO;
    }
    return hash;
}

//http://www.cse.yorku.ca/~oz/hash.html
//Algoritmo djb2
unsigned long hash1(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + (unsigned long)c; /* hash * 33 + c */
    return hash;
}

//http://www.cse.yorku.ca/~oz/hash.html
//Algoritmo sdbm 
unsigned long hash2(const char *str) {
        unsigned long hash = 0;
        int c;
        while ((c = *str++))
            hash = (unsigned long)c + (hash << 6) + (hash << 16) - hash;

        return hash;
}

//http://www.cse.yorku.ca/~oz/hash.html
//Algoritmo lose lose
unsigned long hash3(const char *str) {
	unsigned int hash = 0;
	int c;

	while ((c = *str++))
	    hash += (unsigned int)c;

	return hash;
}

float factor_carga(size_t capacidad, size_t largo) {
    return (float)largo / (float)capacidad;
}

bool _hash_guardar(hash_t *hash, const char *clave, void *dato, size_t pos) {
    if (hash->tabla[pos].estado == VACIO) {
        hash->largo++;
        hash->tabla[pos].clave = malloc(sizeof(char) * (strlen(clave) + 1));
    }
    if (hash->tabla[pos].estado == BORRADO)
        hash->largo++;
    strcpy(hash->tabla[pos].clave, clave);
    hash->tabla[pos].dato = dato;
    hash->tabla[pos].estado = OCUPADO;
    return true;
}

bool ajustar_tam_hash(hash_t *hash, size_t capacidad) {
    hash->capacidad = capacidad;
    campo_t *campo = NULL;
    campo = realloc(hash->tabla, sizeof(campo_t) * hash->capacidad);
    if (!campo) return false;
    hash->tabla = campo;
    for (size_t i = 0; i < hash->capacidad; i++) {
        hash->tabla[i].estado = VACIO;
    } 
    return true;
}

bool hash_redimensionar(hash_t *hash, size_t tam_nuevo) {    
    campo_t *campo; 
    campo = malloc(sizeof(campo_t) * hash->capacidad);
    if (!campo) return false;
    for (size_t i = 0; i < hash->capacidad; i++) {
        campo[i].estado = hash->tabla[i].estado;
        if (campo[i].estado == OCUPADO) {
            size_t largo = strlen(hash->tabla[i].clave); 
            campo[i].clave = malloc(sizeof(char) * (largo + 1));
            if (!campo[i].clave) return false;
            strcpy(campo[i].clave, hash->tabla[i].clave);
            campo[i].dato = hash->tabla[i].dato;
            free(hash->tabla[i].clave);
        }
        if (campo[i].estado == BORRADO)
            free(hash->tabla[i].clave);
    }
    size_t tam_viejo = hash->capacidad;
    ajustar_tam_hash(hash, tam_nuevo);
    hash->largo = 0;
    for (size_t i = 0; i < tam_viejo; i++) {
        if (campo[i].estado == OCUPADO) {
            hash_guardar(hash, campo[i].clave, campo[i].dato);
            free(campo[i].clave);
        }
    }
    free(campo);
    return true;
}

#define CARGA 0.7

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
    if (factor_carga(hash->capacidad, hash->largo) > CARGA) {
        hash_redimensionar(hash, hash->capacidad * REDIM);
    }
    size_t pos = hash2(clave) % hash->capacidad;
    
    while (hash->tabla[pos].estado != VACIO) {
        if (!strcmp(hash->tabla[pos].clave, clave)) {
            void *aux = hash_obtener(hash, hash->tabla[pos].clave);
            _hash_guardar(hash, clave, dato, pos);
            if (hash->destruccion) {
                hash->destruccion(aux);
            }
            return true;
        }
        pos++;
        if (pos == hash->capacidad)
            pos = 0;
    }
    return _hash_guardar(hash, clave, dato, pos);
}

#define MIN 10
#define MULT 4

void *hash_borrar(hash_t *hash, const char *clave) {
    if (hash->largo > MIN && hash->largo * MULT < hash->capacidad) {
        hash_redimensionar(hash, hash->capacidad / REDIM);
    }
    size_t pos = hash2(clave) % hash->capacidad;
    
    while (hash->tabla[pos].estado != VACIO) {
        if (hash->tabla[pos].estado == OCUPADO) {
            if (!strcmp(hash->tabla[pos].clave, clave)) {
                hash->tabla[pos].estado = BORRADO;
                hash->largo--;
                return hash->tabla[pos].dato;
            }
        }
        pos++;
        if (pos == hash->capacidad)
            pos = 0;
    }
    return NULL;
}

void *hash_obtener(const hash_t *hash, const char *clave) {
    size_t pos = hash2(clave) % hash->capacidad;
    while (hash->tabla[pos].estado != VACIO) {
        if (hash->tabla[pos].estado == OCUPADO && !strcmp(hash->tabla[pos].clave, clave))
            return hash->tabla[pos].dato;
        pos++;
        if (pos == hash->capacidad)
            pos = 0;
    }
    return NULL;
}

bool hash_pertenece(const hash_t *hash, const char *clave) {
    size_t pos = hash2(clave) % hash->capacidad;
    while (hash->tabla[pos].estado != VACIO) {
        if (hash->tabla[pos].estado == OCUPADO && !strcmp(hash->tabla[pos].clave, clave)) {
            return true;
        }
        pos++;
        if (pos == hash->capacidad)
            pos = 0;
    }
    return false;
}

size_t hash_cantidad(const hash_t *hash)  {
    return hash->largo;
}

void hash_destruir(hash_t *hash) {
    for (size_t i = 0; i < hash->capacidad; i++) {
        if (hash->tabla[i].estado == OCUPADO) {
            if (hash->destruccion) {
                hash->destruccion(hash->tabla[i].dato);
            }
        }
        if (hash->tabla[i].estado != VACIO)
            free(hash->tabla[i].clave);   
    }
    free(hash->tabla);
    free(hash);
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/



struct hash_iter {
    campo_t* tabla;
    size_t cantidad_de_claves;
    size_t claves_recorridas;
    size_t capacidad;
    size_t posicion_actual;
    hash_destruir_dato_t destruccion;
};



hash_iter_t *hash_iter_crear(const hash_t *hash) {
    hash_iter_t* iter = malloc(sizeof(hash_iter_t));
    if(iter == NULL) return NULL;
    iter->tabla = hash->tabla;
    iter->capacidad = hash->capacidad;
    iter->cantidad_de_claves = hash->largo;
    iter->posicion_actual = 0;
    iter->claves_recorridas = 0;
    iter->destruccion = hash->destruccion;

    if (iter->cantidad_de_claves != 0) {
        while (iter->tabla[iter->posicion_actual].estado != OCUPADO) {
            iter->posicion_actual++;
        }
        iter->claves_recorridas++;
    }

    return iter;
}



bool hash_iter_avanzar(hash_iter_t *iter) {
    if (iter->cantidad_de_claves == 0 || hash_iter_al_final(iter)) {
        return false;
    }
    size_t pos_inicial = iter->posicion_actual + 1;
    for (size_t i = pos_inicial; i < iter->capacidad; i++) {
        iter->posicion_actual = i;
        if (iter->tabla[iter->posicion_actual].estado == OCUPADO) {
            break;
        }
    }
    iter->claves_recorridas++;
    return true;
}



const char *hash_iter_ver_actual(const hash_iter_t *iter) {
    if (hash_iter_al_final(iter)) return NULL;
    return iter->tabla[iter->posicion_actual].clave;
}



bool hash_iter_al_final(const hash_iter_t *iter) {
    if (iter->cantidad_de_claves == 0) return true;
    return iter->claves_recorridas > iter->cantidad_de_claves;
}



void hash_iter_destruir(hash_iter_t *iter){
    free(iter);
}
