#include "../gui/libreria/libreriaMain/mainlibreria.h"
#include "../gui/cine/cineMain/main.h"
#include "../BBDD/cineDB.h"

int selector(int n)
{
    if (n == 1)
    {
        mainCine();
    }
    else if (n == 2)
    {
        mainlibreria();
    }
    else 
    {
        printf("no valido");
    }
}

int main()
{
    int seleccion = 2; // aqui va cambiando el valor 
    selector(seleccion);
}