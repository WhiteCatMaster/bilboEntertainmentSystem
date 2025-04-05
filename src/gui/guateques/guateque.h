typedef struct 
{
    char* nombre;
    float precio;
    char* fecha;
    char* descripcion;
    int id;
    int idg;
} Evento;

typedef struct 
{
    char* nombre;
    char* direccion;
    Evento *eventos;
    int neventos;
    int id;
} Guateque;

void imprimirEventos(Guateque g);
void imprimirGuateques(Guateque *g, int numero);