/* --- Usuario.h --- */

/* ------------------------------------------
Author: undefined
Date: 27/5/2025
------------------------------------------ */

#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <stdlib.h>
using namespace std;

class Usuario {
public:
    Usuario(string, int);
    Usuario();
    ~Usuario();

    
    int getId();
    void setId(int& value);
    string getNombre();
    void setNombre(string& value);
    int getEdad();
    void setEdad(int& value);

private:
    static int id;
    string nombre;
    int edad;

};

#endif // USUARIO_H
