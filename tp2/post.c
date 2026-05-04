#define _POSIX_C_SOURCE 200809L
#include "post.h"
#include "abb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct post {
    char* texto;
    char* publicador;
    size_t id;
    size_t likes;
    int afinidad;
    abb_t *likers;
};



/* ******************************************************************
 *                        PRIMITIVAS POST
 * *****************************************************************/



post_t* post_crear (char* texto, char* publicador, size_t id) {
    post_t* post = malloc(sizeof(post_t));
    if (!post) return NULL;
    char* aux_publicador = strdup(publicador);
    if(!aux_publicador) return NULL;
    char* aux_texto = strdup(texto);
    if(!aux_texto) return NULL;
    post->publicador = aux_publicador;
    post->texto = aux_texto;
    post->id = id;
    post->likes = 0;
    post->likers = abb_crear(strcmp, NULL);
    return post;
}

bool post_likear(post_t *post, char* usuario) {
    if (!usuario || !post)
        return false;
    if (abb_pertenece(post->likers, usuario))
        return true;
    int extra = 1;
    if (!abb_guardar(post->likers, usuario, &extra))
        return false;
    post->likes++;
    return true;
}

size_t post_mostrar_likes (const post_t* post) {
    return post->likes;
}

size_t post_mostrar_id (const post_t* post) {
    return post->id;
}

char* post_mostrar_publicador(const post_t* post) {
    return post->publicador;
}

char* post_mostrar_texto(const post_t* post) {
    return post->texto;
}

bool imprimir_likers(const char *clave, void *dato, void *extra){
    printf("\t%s\n", clave);
    return true;
}

void post_cambiar_afinidad(post_t* post, int afinidad) {
    post->afinidad = afinidad;
}

int post_mostrar_afinidad(const post_t* post){
    return post->afinidad;
}

void post_destruir(post_t* post) {
    abb_destruir(post->likers);
    free(post->texto);
    free(post->publicador);
    free(post);
}

static bool agregar_likes(const char *clave, void *dato, void *extra){
    return lista_insertar_ultimo((lista_t*)extra, (void *)clave);
}

lista_t *post_mostrar_likers(const post_t *post) {
    if (!post->likes || !post)
        return NULL;
    lista_t *lista = lista_crear();
    abb_in_order(post->likers, agregar_likes, lista);    //agrega los likes a una lista
    return lista;
}