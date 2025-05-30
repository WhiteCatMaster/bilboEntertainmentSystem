/* --- Usuario.cpp --- */

/* ------------------------------------------
author: undefined
date: 27/5/2025
------------------------------------------ */

#include "Usuario.h"
int Usuario::id = 0;

Usuario::Usuario(string _nombre, int _edad) {
    nombre = _nombre;
    edad = _edad;
    id = id + 1;
}
Usuario::Usuario(){
    nombre = "";
    edad = 1;
    id +=1 ;
}

Usuario::~Usuario() {
    // Destructor
}


int Usuario::getId() {
    return id;
}
void Usuario::setId(int& value) {
    id = value;
}
string Usuario::getNombre() {
    return nombre;
}
void Usuario::setNombre(string& value) {
    nombre = value;
}
int Usuario::getEdad() {
    return edad;
}
void Usuario::setEdad(int& value) {
    edad = value;
}
