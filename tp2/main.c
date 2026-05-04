#define _POSIX_C_SOURCE 200809L
#define CAP_INIC 15
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "hash.h"
#include "post.h"
#include "algogram.h"
#include <ctype.h>



/* ******************************************************************
 *                       FUNCIONES AUXILIARES
 * *****************************************************************/



void _post_destruir(void* post) {
    post_destruir(post);
}

void _heap_destruir(void* heap) {
    heap_destruir(heap, _post_destruir);
}

// funcion que compara que post tiene mejor afinidad con el usuario
int _comparacion_afinidad(const post_t* a, const post_t* b) {
    int afinidad_a = post_mostrar_afinidad(a);
    int afinidad_b = post_mostrar_afinidad(b);
    size_t id_a = post_mostrar_id(a);
    size_t id_b = post_mostrar_id(b);

    if (afinidad_a > afinidad_b) return -1;
    else if(afinidad_a < afinidad_b) return 1;
    if (id_a < id_b) return 1;
    return -1;
}

int comparacion_afinidad(const void* a, const void* b) {
    return _comparacion_afinidad(a, b);
}

// Funcion que guarda los usuarios del documento de texto ingresado en dos hashes, uno sera utilizado para el
// feed del usuario y en el otro se guardara la posicion del usuario en el documento de texto
void guardar_usuarios(char* usuarios, hash_t* hash_usuarios, hash_t* hash_feed) {
    FILE* archivo_usuario = fopen(usuarios, "r");
    char* linea = NULL;
    size_t tam = 0;
    int posicion = 0;

    while (getline(&linea, &tam, archivo_usuario) != EOF) {
        int* aux = malloc(sizeof(int));
        *aux = posicion;

        heap_t* heap_post = heap_crear(comparacion_afinidad);
        hash_guardar(hash_usuarios, linea, aux);
        hash_guardar(hash_feed, linea, heap_post);
        posicion++;
    }
    free(linea);
    fclose(archivo_usuario);
}



/* ******************************************************************
 *                              MAIN
 * *****************************************************************/



int main(int argc, char* vector[]) {
    char* usuario = NULL;
    char* comando = NULL;
    size_t tam = 0;
    size_t publicaciones = 0;
    size_t capacidad = CAP_INIC;
    cola_t* cola_desencolados = cola_crear();
    hash_t* hash_usuarios = hash_crear(free);
    hash_t* hash_feed = hash_crear(_heap_destruir);
    hash_t* hash_desencolados = hash_crear(_post_destruir);
    post_t **posts = malloc(capacidad * sizeof(post_t*));
    guardar_usuarios(vector[1], hash_usuarios, hash_feed);


    while (getline(&comando, &tam, stdin) != EOF) {
        // Comando de login
        if (strcmp(comando, "login\n") == 0){
            usuario = algogram_login(usuario, hash_usuarios, tam);
        }

        // comando de logout
        else if (strcmp(comando, "logout\n") == 0) {
            usuario = algogram_logout(usuario);
        }

        // comando de publicar
        else if (strcmp(comando, "publicar\n") == 0) {
            if (publicaciones == capacidad) {
                post_t **aux = realloc(posts, capacidad * sizeof(post_t*) * 2);
                posts = aux;
                capacidad*=2;
            }
            publicaciones = algogram_publicar(usuario, hash_feed, hash_usuarios, publicaciones, posts);
        }

        //comando de ver_siguiente_feed
        else if (strcmp(comando, "ver_siguiente_feed\n") == 0) {
            algogram_ver_siguiente_feed(usuario, hash_feed, posts, cola_desencolados);
        }

        // comando de dar like a un post
        else if (strcmp(comando, "likear_post\n") == 0) {
            algogram_likear_post(usuario, posts, publicaciones);
        }

        // comando de mostrar likes
        else if (strcmp(comando, "mostrar_likes\n") == 0) {
            algogram_mostrar_likes(posts, publicaciones);
        }
    }

    // Se libera la memoria usada durante la ejecucion
    free(usuario);
    free(posts);
    free(comando);
    hash_destruir(hash_usuarios);
    hash_destruir(hash_feed);
    hash_destruir(hash_desencolados);
    cola_destruir(cola_desencolados, _post_destruir);
    return 0;
}