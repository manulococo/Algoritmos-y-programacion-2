#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "hash.h"
#include "post.h"
#include "cola.h"
#include <ctype.h>



/* ******************************************************************
 *                       FUNCIONES AUXILIARES
 * *****************************************************************/



int calculo_afinidad(int* a, int* b) {
    int afinidad = *a - *b;
    if (afinidad < 0) afinidad = afinidad*-1;
    return afinidad;
}

bool es_numero(const char *a) {
    for (size_t i = 0; a[i]!= '\0'; i++) {
        if (!isdigit(a[i]))
        return false;
    }
    return true;
}

bool imprimir_lista(void *dato, void *extra) {
    printf("\t%s", (char *)dato);
    return true;
}



/* ******************************************************************
 *                       PRIMITIVAS ALGOGRAM
 * *****************************************************************/



char* algogram_login(char* usuario, hash_t* hash_usuarios, size_t tam){
    if (usuario) {
        printf("Error: Ya habia un usuario loggeado\n");
        return usuario;
    }
    ssize_t carac_leidos = getline(&usuario, &tam, stdin);
    if (carac_leidos < 0)
        return NULL;
    if (hash_pertenece(hash_usuarios, usuario)) {
        printf("Hola %s", usuario);
    } else {
        printf("Error: usuario no existente\n");
    }
    return usuario;
}

char* algogram_logout(char* usuario) {
    if (usuario) {
        free(usuario);
        usuario = NULL;
        printf("Adios\n");
    } else {
        printf("Error: no habia usuario loggeado\n");
    }
    return usuario;
}

size_t algogram_publicar(char* usuario, hash_t* hash_feed, hash_t* hash_usuarios, size_t id, post_t **posts) {
    if (!usuario) {
        printf("Error: no habia usuario loggeado\n");
        return id;
    }

    char* comando = NULL;
    size_t tam = 0;
    ssize_t carac_leidos = getline(&comando, &tam, stdin);
    if (carac_leidos < 0)
        return -1;

    hash_iter_t* iter = hash_iter_crear(hash_usuarios);

    while (!hash_iter_al_final(iter)) {
        char* clave = (char*)hash_iter_ver_actual(iter);
        if (strcmp(clave, usuario) == 0) {
            hash_iter_avanzar(iter);
            continue;
        }

        post_t* post_nuevo = post_crear(comando, usuario, id);

        int* a = hash_obtener(hash_usuarios, usuario);
        int* b = hash_obtener(hash_usuarios, clave);
        int afinidad = calculo_afinidad(a, b);
        post_cambiar_afinidad(post_nuevo, afinidad);

        heap_t* heap = hash_obtener(hash_feed, clave);
        heap_encolar(heap, post_nuevo);
        posts[id] = post_nuevo;
        hash_iter_avanzar(iter);
    }
    id++;
    free(comando);
    hash_iter_destruir(iter);
    printf("Post publicado\n");

    return id;
}

void algogram_ver_siguiente_feed(char* usuario, hash_t* hash_feed, post_t **posts, cola_t* cola_desencolados) {

    if(!usuario) {
        printf("Usuario no loggeado o no hay mas posts para ver\n");
        return;
    }
    heap_t* heap = hash_obtener(hash_feed, usuario);
    if(!heap || heap_cantidad(heap) == 0) {
        printf("Usuario no loggeado o no hay mas posts para ver\n");
        return;
    }

    post_t* post = heap_desencolar(heap);
    size_t id = post_mostrar_id(post);
    size_t likes = post_mostrar_likes(posts[id]);
    char* publicador = post_mostrar_publicador(post);
    publicador[strlen(publicador) - 1] = ' ';
    char* texto = post_mostrar_texto(post);
    printf("Post ID %ld\n%sdijo: %sLikes: %ld\n", id, publicador, texto, likes);

    cola_encolar(cola_desencolados, post);

}

void algogram_likear_post(char *usuario, post_t **posts, size_t publicaciones) {
    char *post_id = NULL;
    size_t tam = 0;
    ssize_t carac_leidos = getline(&post_id, &tam, stdin);
    if (carac_leidos < 0)
        return;
    int id = atoi(post_id);

    if (id + 1 > publicaciones) {
        printf("Error: Usuario no loggeado o Post inexistente\n");
        free(post_id);
        return;
    }
    post_t *post = posts[id];
    if (post_likear(post, usuario))
        printf("Post likeado\n");
    else
        printf("Error: Usuario no loggeado o Post inexistente\n");
    free(post_id);
}

void algogram_mostrar_likes(post_t **posts, size_t publicaciones) {
    char *post_id = NULL;
    size_t tam = 0;
    ssize_t carac_leidos = getline(&post_id, &tam, stdin);
    if (carac_leidos < 0)
        return;
    int id = atoi(post_id);
    if (id + 1 > publicaciones) {
        printf("Error: Post inexistente o sin likes\n");
        free(post_id);
        return;
    }
    post_t *post = posts[id];

    lista_t *lista_likers = post_mostrar_likers(post);
    if (!lista_likers) {
        printf("Error: Post inexistente o sin likes\n");
        free(post_id);
        return;
    }
    printf("El post tiene %ld likes:\n", post_mostrar_likes(post));
    int extra = 0;
    lista_iterar(lista_likers, imprimir_lista, &extra);
    lista_destruir(lista_likers, NULL);
    free(post_id);
}

