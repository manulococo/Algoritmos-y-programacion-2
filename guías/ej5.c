#include <stdlib.h>
#define MAX_STR 50

typedef struct obra {
    int anio;
    char nombre[MAX_STR];
} obra_t;

obra_t obras[] = {
    
};

size_t hallar_k(obra_t *obras, size_t n) {
    int min = obras[0].anio;
    int max = obras[0].anio;
    for (size_t i = 0; i < n; i++) {
        if(obras[i].anio > max)
            max = obras[i].anio;
        if(obras[i].anio < min)
            min = obras[i].anio;    
    }
    
    return max - min;
}

