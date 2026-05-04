#include "mamushka.h"

struct mamushka {
    size_t tam;
    color_t color;
    mamushka_t *mamushka_guardada;
};

mamushka_t* mamushka_crear(size_t tam, color_t color) {
    mamushka_t *mamushka = malloc(sizeof(mamushka_t));
    mamushka->tam = tam;
    mamushka->color = color;
    mamushka->mamushka_guardada = NULL;
    return mamushka;
}

color_t mamushka_obtener_color(mamushka_t* mamushka) {
    return mamushka->color;
}

bool mamushka_guardar(mamushka_t* contenedora, mamushka_t* a_guardar) {
    if(contenedora->tam <= a_guardar->tam)
        return false;
    while(mamushka_obtener_guardada())
    mamushka_guardar(contenedora->guardada, a->guardar);
    

}

mamushka_t* mamushka_obtener_guardada(mamushka_t*) {
    return mamushka->guardada;
}
void mamushka_destruir(mamushka_t*);