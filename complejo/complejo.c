#include "complejo.h"

#include <math.h>

struct complejo {
    double real;
    double img;
};

complejo_t* complejo_crear(double real, double img) {
    complejo_t *complejo = malloc(sizeof(complejo_t));
    complejo->img = img;
    complejo->real = real;
    return complejo;
}

void complejo_multiplicar(complejo_t* c1, complejo_t* c2) {
    c1->real = c1->real * c2->real - c1->img * c2->img;
    c1->img  = c1->img * c2->real + c1->real * c2->img; 
}

void complejo_sumar(complejo_t* c1, complejo_t* c2) {
    c1->real += c2->real;
    c1->img  += c2->img;
}

double complejo_obtener_imaginaria(const complejo_t* complejo) {
    return complejo->img;
}

double complejo_obtener_real(const complejo_t* complejo) {
    return complejo->real;
}

double complejo_obtener_modulo(const complejo_t* complejo) {
    return sqrt(pow(complejo->real, 2) + pow(complejo->img, 2));
}

double complejo_obtener_angulo(const complejo_t* complejo) {
    return atan2(complejo->img, complejo->real);
}

void complejo_destruir(complejo_t* complejo) {
    free(complejo);
}
