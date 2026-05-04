#ifndef POST_H
#define POST_H
#include <stdbool.h>
#include <stdlib.h>
#include "lista.h"
#include "abb.h"

typedef struct post post_t;

// Crea un post, recibe como parametro el texto que contendra el post,
// el nombre del publicador y el id que tendra el post
// post: crea un post
post_t* post_crear(char* texto, char* publicador, size_t id);

// le da un like al post y se guarda el nombre de quien le dio like
// pre: el post fue creado
// post: suma un like al post y guarda la persona que le dio like. devuelve true si
// todo sale bien
bool post_likear(post_t* post, char* liker);

// devuelve la cantidad de likes que tiene el post
// pre: el post fue creado
// post: devuelve la cantidad de likes
size_t post_mostrar_likes(const post_t* post);

// devuelve el id del post
// pre: el post fue creado
// post: devuelve el id del post
size_t post_mostrar_id(const post_t* post);

// cambia la afinidad del post con el usuario del feed
// pre: el post fue creado
// post: cambia el valor de afinidad del post
void post_cambiar_afinidad(post_t* post, int afinidad);

// devuelve la afinidad del post con el usuario del feed
// pre: el post fue creado
// post: devuelve la afinidad del post
int post_mostrar_afinidad(const post_t* post);

// devuelve el nombre de quien publico el post
// pre: el post fue creado
// post: devuelve el publicador del post
char* post_mostrar_publicador(const post_t* post);

// devuelve el texto del post
// pre: el post fue creado
// post: devuelve el texto del post
char* post_mostrar_texto(const post_t* post);

// imprime alfabeticamente por pantalla los usuarios que le dieron like al post
// pre: el post fue creado
// post: devuelve las personas que le dieron like al post
lista_t *post_mostrar_likers(const post_t* post);

// destruye el post
// pre: el post fue creado
// post: destruye el post
void post_destruir(post_t* post);

#endif