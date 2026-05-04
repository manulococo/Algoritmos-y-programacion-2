#ifndef MAMUSHKA_H
#define MAMUSHKA_H


struct mamushka;
typedef struct mamushka mamushka_t;

mamushka_t* mamushka_crear(size_t tam, color_t color);
color_t mamushka_obtener_color(mamushka_t* mamushka);
bool mamushka_guardar(mamushka_t* contenedora, mamushka_t* a_guardar);
mamushka_t* mamushka_obtener_guardada(mamushka_t *);
void mamushka_destruir(mamushka_t *);


#endif