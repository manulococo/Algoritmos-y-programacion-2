#define _POSIX_C_SOURCE 200809L
#define CAP_INIC 15
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "hash.h"
#include "post.h"
#include "cola.h"
#include <ctype.h>

// Se recibe un usuario por parametro. Si ya hay un usuario se in formar por
// pantalla. Si no hay usuario se pide el ingreso del nombre del usuario. Y la
// funcion se fija si en el hash existe ese usuario. Si existe se loguea con exito
// sino se informa en pantalla
char* algogram_login(char* usuario, hash_t* hash_usuarios, size_t tam);



// Se recibe al usuario por parametro y lo desloguea. Si no habia usuario se informa
// por pantalla
char* algogram_logout(char* usuario);



// Si hay un usuario logueado. crea un post y lo publica en el feed de cada usuario
// segun la afinidad de cada usuario con el publicador del post
size_t algogram_publicar(char* usuario, hash_t* hash_feed, hash_t* hash_usuarios, size_t id, post_t **posts);



// si el usuario esta logueado y hay posts en el feed del usuario. Muestra el post que
// primero en el feed
void algogram_ver_siguiente_feed(char* usuario, hash_t* hash_feed, post_t **posts, cola_t* cola_desencolados);



// Se pide el ingreso del id del post a likear. Si el id es mayor a la cantidad de
// post publicados se informa por pantalla que el post no existe. Si existe se likea
// el post y se guarda el usuario que le dio like
void algogram_likear_post(char *usuario, post_t **posts, size_t publicaciones);



// Se pide el ingreso del id del post a mostrar los likes. Si el id es mayor a la
// cantidad de post publicados se informa por pantalla que el post no existe.
// Si existe y tiene likes muestra la lista de manera alfabetica de las personas
// que dieron likes
void algogram_mostrar_likes(post_t **posts, size_t publicaciones);