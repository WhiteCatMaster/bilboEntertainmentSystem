typedef struct 
{
    char* nombre;
    float precio;
    char* fecha;
    char* descripcion;
} Evento;

typedef struct 
{
    char* nombre;
    char* direccion;
    Evento *eventos;
    int neventos;
} Guateque;

void imprimirEventos(Guateque g);
void imprimirGuateques(Guateque *g, int numero);